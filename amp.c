/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include "define.h"
#include "amp.h"
#include <ctype.h>

/**
 * Open an amp file
 * For more information
 * https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-manipulez-des-fichiers-a-laide-de-fonctions
 * @param filename : the path to the filename
 * @return pf
 */

FILE* initAMP(char* filename){
    FILE * pf = NULL;
    pf = fopen(filename, "r");

    if (pf == NULL){
        printf("Erreur\n");
    }
    return pf;
}

/**
 * Transform the capital letter of a string in lower letter
 * https://koor.fr/C/cctype/tolower.wp
 * @param dest : destination
 * @param src : source
 * @return
 */
char * strtolower(char * dest, const char * src ) {
    char * result = dest;
    while((*dest++ = tolower( *src++ )));
    return result;
}

/**
 * Read the amp file to the end and put the song name in a formatted way
 * space, apostrophe and special character with an '_'
 * to understand strncat see : https://www.youtube.com/watch?v=40yPiMCgixY
 * @param pf : the open file
 * @param song_filename
 */

void readAMP(FILE* pf, char * song_filename){
    char chaine[MAX_SIZE_TITLE] = "";

    if (pf != NULL){
        fgets(chaine, MAX_SIZE_TITLE, pf);
    }

    char without_caract[MAX_SIZE_TITLE] = "";

    for (int i = 0; i < MAX_SIZE_TITLE; i++) {
        if (isalpha(chaine[i])) {
            strncat(without_caract, &chaine[i], 1);
        } else {
            if (without_caract[0] != '\0' && without_caract[strlen(without_caract) - 1] != '_') {
                strncat(without_caract, "_", 1);
            }
        }
    }

    without_caract[strlen(without_caract)-1] = '\0';
    without_caract[strcspn(without_caract, "\n")] = '\0'; // Put a \0 at the end of the line
    strtolower(song_filename, without_caract);
    //printf("%s", song_filename);
    strcat(song_filename,".ams");
}





/**
 * Close the file pf if it exists
 * @param pf : the file we want to close
 */
void closeAMP(FILE* pf){
    if (pf){
        fclose(pf);
    }else{
        printf("The file doesn't exist.");
    }
}


/**
 * Test the read ams function
 * @param filename : the name of the amp file
 * @return
 */
int test_amp(char * filename) {
    FILE* fichier = initAMP(filename);
    if (fichier != NULL) {
        char nom_chanson[MAX_SONGNAME_SIZE];
        readAMP(fichier, nom_chanson);
        closeAMP(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
    return 0;
}
