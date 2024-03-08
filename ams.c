/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include "define.h"
#include "ams.h"

/**
 * Read the ams file named filename to complete the struct with the file information
 * information = song name, tick in a minute, total tick, tab with tick
 * if the file can't be read or is empty, return struct with empty title ("") and '0' on all other content
 *
 * Documentation about the file reading:
 * doc src = https://zestedesavoir.com/tutoriels/755/le-langage-c-1/1043_aggregats-memoire-et-fichiers/4279_structures/
 * doc src = https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-manipulez-des-fichiers-a-laide-de-fonctions
 * @param fileName
 * @return the struct song completed
 */
s_song readAMS(char* fileName){
	
	s_song mySong;
    FILE * file = NULL;
    file = fopen(fileName, "r");
    if (file == NULL){
        mySong.tpm = 0;
        mySong.nTicks = 0;
        mySong.title[0] = '\0';
        memset(mySong.tickTab, 0, sizeof (mySong.tickTab)); // Initialize an empty table (https://www.delftstack.com/fr/howto/c/c-initialize-array-to-0/)
        /*memset(variable de pointage vers le bloc de mémoire à remplir, valeur a définir, nombre d’octets à mettre à la valeur.)*/
        return mySong;
    }

    char buffer[MAX_SIZE_LINE];

    /* Get the title */
    fgets(mySong.title, MAX_SIZE_TITLE, file);
    int len = strlen(mySong.title);
    mySong.title[len-1] = '\0';

    /* Get the tempo */
    /* using fscanf is more simple to get a number (see openclassroom doc) */
    fscanf(file, "%d\n", &mySong.tpm);
    //mySong.tpm *= 2;

    /* Get the number of ticks and the tickTab */
    int cmpt = 0; // to get total number in line
    char d[] = "|";
    int cmpt_ch = 0;
    memset(mySong.tickTab, 0, sizeof (mySong.tickTab)); // Initialize an empty table


    while (fgets(buffer, MAX_SIZE_LINE, file)){
        cmpt ++;
        char * ca = strtok(buffer, d);
        cmpt_ch = 0;
        int chap = 0;
        while (ca != NULL){
            /*ca[0] to get the first element*/
            if (ca[0] == '^' || ca[0] == 'x'){
                if(ca[0] == '^'){
                    /* -2 because they are 2 line over the table*/
                    mySong.tickTab[cmpt - 2].accent = 1;
                }
                mySong.tickTab[cmpt - 2].note[cmpt_ch] = chap;
                cmpt_ch++;
            }
            ca = strtok(NULL, d);
            chap ++;
        }
    }
    /* -1 because our cmpt start at 0*/
    mySong.nTicks = cmpt - 1;

	return mySong;

}


/**
 * Test the read ams file and print the data present in the song struct
 * @return
 */
int test_ams(char * filename) {
    // Read ams file information
    s_song song = readAMS(filename);

    // Print the collected information
    printf("Titre de la chanson : %s\n", song.title);
    printf("Nombre de tick par minute : %d\n", song.tpm);
    printf("Nombre de Ticks : %d\n", song.nTicks);
    printf("Tableau de tick : \n");
    for (int i = 0; i < song.nTicks; i++) {
        printf(" %d\t %d\t %d\t %d\t %d\n",
               song.tickTab[i].accent,
               song.tickTab[i].note[0],
               song.tickTab[i].note[1],
               song.tickTab[i].note[2],
               song.tickTab[i].note[3]);
    }
    return 0;
}

/**
 * creation of an electronic partition (<chanson>.ams) from a simplify partition (<chanson>.txt)
 * @param txtFileName
 * @param amsFileName :
 */
void createAMS(char* txtFileName, char* amsFileName){
    /* Open the files */
    FILE * from = NULL;
    FILE * to = NULL;

    from = fopen(txtFileName, "r");
    if (from == NULL){
        printf("Error file not found ! \n");
        exit(0);
    }
    to = fopen(amsFileName, "w");
    if (to == NULL){
        printf("Error file not found ! \n");
        exit(0);
    }

    char buffer[MAX_SIZE_LINE];

    /* Get the title from the txt file to the ams file*/
    fgets(buffer, MAX_SIZE_TITLE, from);
    fputs(buffer, to);

    /* Get the tempo of the music*/
    fgets(buffer, MAX_SIZE_LINE, from);
    fputs(buffer, to);
    fputs("\r\n", to);

    /* Line break*/
    fgets(buffer, MAX_SIZE_LINE, from);

    /* Create the numbered  line in the top of the ams table */
    char numbers[MAX_SIZE_LINE];
    sprintf(numbers,"    ");
    for (int i=1;i<=60;i++){
        sprintf(numbers+strlen(numbers), "%02d ",i);
    }
    sprintf(numbers+strlen(numbers),"\r\n"); // Essential at the end of line
    fputs(numbers,to);


    /* Help for notes:
        A = 10
        B = 12
        C = 1
        D = 3
        E = 4
        F = 6
        G = 8
    */

    int tab_notes[7] = {10,12,1,3,4,6,8}; // Values of note
    int tab_oct[5] = {0, 12, 24, 36, 48}; // Value for the octave

    /* case to put in the table*/
    char nligne[6] = "000|";
    char buf_cpy[MAX_SIZE_LINE];

    // Initialise an empty table
    int tab_lignes[MAX_SIZE_LINE][60];
    for(int i=0; i<MAX_SIZE_LINE; i++){
        for(int j=0; j<60; j++){
            tab_lignes[i][j] = 0;
        }
    }

    /* Fill the table with the notes*/
    int ligne = 0;

    while(fgets(buffer, MAX_SIZE_LINE, from)){

        ligne ++;
        int j = 0;
        printf("Ligne numero %d:\n", ligne);

        //Delete the space of the buffer
        for(int i=0; i< strlen(buffer); i++){
            if(buffer[i] != ' ' && buffer[i] != '\t'){
                buf_cpy[j] = buffer[i];
                j++;
            }
        }

        /* Debug for mac
        int l = strlen(buffer);
        buffer[l-1] = '\0';
        buffer[l-2] = '\n';
        */

        /* Get the information about the note*/
        char * info_note = strtok(buf_cpy, ",");

        while (info_note != NULL){

            int len = strlen(info_note);
            int code_note = info_note[0]; // Get the note
            int code_oct = info_note[1] - '0';  // Get the octave

            int note = tab_notes[code_note - 'A'];
            int oct = tab_oct[code_oct-1];
            int box = note + oct; // Index in the table

            printf("%d - %d - %c\n", note, oct,info_note[2]);

            if(info_note[2] == '#'){
                box += 1;
            }

            tab_lignes[ligne-1][box-1] = 1;
            //printf("Le coordonees de la note %d, %d\n\n", ligne-1, box-1);


            /* Manage the repetition of the note*/
            int repet = 0;
            switch(info_note[len-1]){
                case 'R' :
                    repet = 8;
                    break;
                case 'B':
                    repet = 4;
                    break;
                case 'N':
                    repet = 2;
                    break;
                case 'C':
                    repet = 1;
                    break;
            }

            if(repet>1){
                for(int i=0; i<repet;i++){
                    tab_lignes[ligne + i][box-1] = 2;
                }
            }
            info_note = strtok (NULL, "," );

        }
    }

    /* Fill the table in the ams file*/
    for(int i=0; i<ligne; i++){
        /* Put the line number at the beginning of the line*/
        sprintf(nligne, "%03d|", i+1);
        fputs(nligne, to);

        for(int j=0; j<60; j++){
            if(tab_lignes[i][j] == 1){
                fputs("^ |", to);
            }
            else if (tab_lignes[i][j] == 2){
                fputs("x |", to);
            }else{
                fputs("  |", to);
            }
        }
        if(i<ligne-1)
            fputs("\r\n\0", to);
    }

    // Close files
    fclose(to);
    fclose(from);
}