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

    if (pf != NULL){
        printf("Erreur\n");
    }
    return pf;
}

/**
 * consiste à lire une ligne du fichier pointé par pf et renvoie chaine de caractère
 * on remplace espace " " par "_" et on ne doit pas avoir deux "__"
 * dès que le ficher est lu (est terminé), renvoie NULL (plus de titre à lire)
 * @param pf
 * @param song_filename
 */

void readAMP(FILE* pf, char * song_filename){


}

char del_space(char* song){
    char without_caract;
    for (int i=0; i<MAX_SONGNAME_SIZE; i++){
        if(song[i] == ' ' | song[i] == '\''){
            without_caract += '_';
        }else{
            without_caract += song[i];
        }
    }
    return without_caract;
}

char * strtolower( char * dest, const char * src ) {
    char * result = dest;
    while( *dest++ = tolower( *src++ ) );
    return result;
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