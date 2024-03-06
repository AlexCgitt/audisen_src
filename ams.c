/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include "define.h"
#include "ams.h"

/**
 * readAMS() read the file name filename and return a struct of s_song type with all the information about song.
 * information = tick in a minute, total tick, music title, tick title
 * in the ams file, we have all the information (title in the first line, tpm in the second line, nTick in the third line, and tickTab
 * we need to use fgets
 * for the title we just need to use a fgets (see the open classroom doc) to get a line with a string
 * for the tpm it's better to use a fscanf (see the open classroom doc) to recup nmb in a line
 * for the nTick, we make a while till the end of the file - 4
 * for the tick table, utilisation of strtok (see https://www.youtube.com/watch?v=nrO_pXGZc3Y on ytb)
 * utilisation of compt to get .accent and .note
 * if the file can't be read, return struct with empty title ("") and '0' on all other content
 * doc src = https://zestedesavoir.com/tutoriels/755/le-langage-c-1/1043_aggregats-memoire-et-fichiers/4279_structures/
 * doc src = https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-manipulez-des-fichiers-a-laide-de-fonctions
 * initialise un tableau à 0 en c src = https://www.delftstack.com/fr/howto/c/c-initialize-array-to-0/
 * @param fileName
 * @return
 */

s_song readAMS(char* fileName){
	
	s_song mySong;
    FILE * file = NULL;
    file = fopen(fileName, "r");
    if (file == NULL){
        mySong.tpm = 0;
        mySong.nTicks = 0;
        mySong.title[0] = '\0';
        memset(mySong.tickTab, 0, sizeof (mySong.tickTab)); // Initialize an empty table
        /*memset(variable de pointage vers le bloc de mémoire à remplir, valeur a définir, nombre d’octets à mettre à la valeur.)*/
        return mySong;
    }

    char buffer[MAX_SIZE_LINE];

    /* recuperation of the title */
    fgets(mySong.title, MAX_SIZE_TITLE, file);
    mySong.title[strlen(mySong.title)-1] = '\0';
    /* recupération tpm */
    /* more simple to get a number (see openclassroom doc) */
    fscanf(file, "%d\n", &mySong.tpm);
    //mySong.tpm *= 2;

    /*recupertion of nTicks and tickTab */
    /*cmpt to recup total number in line */
    int cmpt = 0;
    char d[] = "|";
    int cmpt_ch = 0;


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
    /* -1 because our  cmpt start at 0*/
    mySong.nTicks = cmpt - 1;

	return mySong;

}



//test

int test_ams() {
    char fileName[] = "bohemian_rhapsody.ams";


    // Lire les informations du fichier AMS
    s_song song = readAMS(fileName);

    // Affichage des informations récupérées

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
 * to make this create
 * @param txtFileName
 * @param amsFileName :
 */
void createAMS(char* txtFileName, char* amsFileName){

    s_song NewSong;
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

    /* get the title from the txt file to the ams file */
    fgets(buffer, MAX_SIZE_LINE, from);
    fputs(buffer, to);

    /* get the tempo of the music */
    fgets(buffer, MAX_SIZE_LINE, from);
    fputs(buffer, to);

    /* line break */
    fgets(buffer, MAX_SIZE_LINE, from);

    /* line with from 01 to */
    char ligne_nombre[190] = "   01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 ";
    fputs(ligne_nombre, to);

    /* line of octave and  notes */
    // TODO voir pour le nombre de lignes
    /* notes:
        A = 10
        B = 12
        C = 1
        D = 3
        E = 4
        F = 6
        G = 8
    */

    int tab_notes[7] = {10,12,1,3,4,6,8};

    while(fgets(buffer, MAX_SIZE_LINE, from)){
        //lit 1 caractère => association à une note
        //2e carcatère => indique l'octave
        //3e verif diez ? si oui +1 à la val note
        // ===> recup valeur case de tableau de 60
    }




/*
pour resoudre le pb d'affichage
fgets(buffer, ___, pf)
buffer[l-2] = \n
buffer[l-1] = \0
*/







}