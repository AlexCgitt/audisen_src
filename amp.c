/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include "define.h"
#include "amp.h"
#include <ctype.h>

/**
 * pour ce renseigner plus en détail, ne pas hésiter à aller regarder
 * https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-manipulez-des-fichiers-a-laide-de-fonctions
 * @param filename
 * @return pf
 * la fonction doit tenter d'ouvrir le fichier filename:"playlist.amp"
 * si le fichier s'ouvre en lecture on renvoie un pointeur vers ce fichier sinon on renvoie NULL.
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
    while(*dest++ = tolower( *src++ ));
    return result;
}

/**
 * consiste à lire une ligne du fichier pointé par pf et renvoie chaine de caractère
 * on remplace espace " " par "_" et on ne doit pas avoir deux "__"
 * dès que le ficher est lu (est terminé), renvoie NULL (plus de titre à lire)
 * @param pf
 * @param song_filename
 */
void readAMP(FILE* pf, char * song_filename){
    char chaine[MAX_SONGNAME_SIZE] = "";

    if (pf != NULL){
        fgets(chaine, MAX_SONGNAME_SIZE, pf);
    }

    char without_caract[MAX_SONGNAME_SIZE] = "";
    char under[1] = "_";

    for (int i=0; i<MAX_SONGNAME_SIZE; i++){
        if(chaine[i] == ' ' | chaine[i] == '\'' | chaine[i] == '-'){
            strncat(without_caract, (const char *) &under, 1);
        }else{
            strncat(without_caract, &chaine[i], 1);
        }
    }
    strtolower(song_filename, without_caract);
    printf("%s", song_filename);
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
 *  to test amp.c
 * @return string
 */

int main() {
    FILE* fichier = initAMP("ma_playlist.amp");
    if (fichier != NULL) {
        char nom_chanson[MAX_SONGNAME_SIZE];
        readAMP(fichier, nom_chanson);
        closeAMP(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
    return 0;
}
