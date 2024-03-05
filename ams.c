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

    /* recupération tpm */
    /* more simple to get a number (see openclassroom doc) */
    fscanf(file, "%d\n", &mySong.tpm);
    mySong.tpm *= 2;

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
 *
 * @param txtFileName
 * @param amsFileName :
 */
void createAMS(char* txtFileName, char* amsFileName){


}