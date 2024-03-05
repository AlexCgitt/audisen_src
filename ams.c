/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include "define.h"
#include "ams.h"

/**
 * readAMS() read the file name filename and return a struct of s_song type with all the information about song.
 * information = tick in a minute, total tick, music title, tick title
 * in the ams file, we have all the information (title i the first line, tpm in the second line
 * to know nTicks, we make total line - 4
 * TICK TAB A VOIR
 * we need to use fgets
 * if the file can't be read, return struct with empty title ("") and '0' on all other content
 * doc src = https://zestedesavoir.com/tutoriels/755/le-langage-c-1/1043_aggregats-memoire-et-fichiers/4279_structures/
 * initialise un tableau à 0 en c src = https://www.delftstack.com/fr/howto/c/c-initialize-array-to-0/
 * @param fileName
 * @return
 */

s_song readAMS(char* fileName){
	
	s_song mySong;
    FILE * file = NULL; /* potentiellement a mettre en commentaire mais important pour l'initialisation */
    file = fopen(fileName, "r");
    if (file == NULL){
        mySong.tpm = 0;
        mySong.nTicks = 0;
        mySong.title[0] = '\0';
        memset(mySong.tickTab, 0, sizeof (mySong.tickTab));
        /*memset(variable de pointage vers le bloc de mémoire à remplir, valeur a définir, nombre d’octets à mettre à la valeur.)*/
        return mySong;
    }


    /* to stop a line
    char buffer[MAX_SIZE_LINE];
     on va potentiellement utiliser ça
     */

    /* pour utiliser fgets : read the doc  : https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-manipulez-des-fichiers-a-laide-de-fonctions */
    /*we gonna recup the first information with fgets and after we're going to use the while */

    /* recuperation of the title */
    fgets(mySong.title, MAX_SIZE_TITLE, file);

    /* recupération tpm */
    fscanf(file, "%d\n", &mySong.tpm);


    /* pour lire ligne par ligne, on va faire une boucle while on va s'en servir juste pour le tableau

    int cmpt = 0; // use to count our line
    while (fgets()){
        if {

        }
    }
     */





	return mySong;


}



//test

int main() {
    char fileName[] = "bohemian_rhapsody.ams";

    // Lire les informations du fichier AMS
    s_song song = readAMS(fileName);

    // Affichage des informations récupérées
    printf("Titre de la chanson : %s\n", song.title);
    printf("Nombre de tick par minute : %d\n", song.tpm);
    /*printf("Ticks :\n");
    for (int i = 0; i < song.nTicks; i++) {
        printf("Tick %d : accent=%d, notes=%d %d %d\n", i+1,
               song.tickTab[i].accent,
               song.tickTab[i].note[0],
               song.tickTab[i].note[1],
               song.tickTab[i].note[2]);
    }*/

    return 0;
}

/**
 *
 * @param txtFileName
 * @param amsFileName :
 */
void createAMS(char* txtFileName, char* amsFileName){


}