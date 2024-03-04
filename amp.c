/**
 * @authors CAVARO Alexandre RIOU Margot 2 Caen
 */

#include "define.h"
#include "amp.h"

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
    pf = fopen("playlist.amp", "r+");
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

    char buffer[100];
    if (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        printf("Contenu du fichier : %s", buffer);
    }




}

void closeAMP(FILE* pf){
    if (pf){
        fclose(pf);
    }else{
        printf("The file doesn't exist.");
    }
}