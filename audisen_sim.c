/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include <stdio.h>
#include "ams.h"
#include "frame.h"
#include "amp.h"
#include "define.h"
#include "autotests.h"

void createFRM_readPlaylist(char* ma_playliste, char* new_playlist_frm){

    // start with frm open in write mode
    FILE * frm = NULL;
    frm = fopen(new_playlist_frm, "w");
    if (frm == NULL){
        printf("erreur lors de l'ouverture du fichier");
        exit(0);
    }

    //recuperation of amp file
    FILE * play = NULL;
    play = initAMP(ma_playliste);

    //recuperation of ams title file
    char chaine[MAX_SIZE_TITLE];
    readAMP(play, chaine);
    printf("%s", chaine);

    // recuperation of my song struct
    //s_song Mysong;
    Mysong = readAMS(chaine);
    //printf("%d", Mysong.tpm);

    //recuperation of init frame
    /*char content[INIT_FRAME_MAX_SIZE];
    createInitFrame(Mysong, content);*/


}


int main(){
    printf("Demarrage du projet AUDISEN\n");


    //test_amp();

    //test_ams();

    //test_frame();

    //testFrame();

    //testReadAMP();

    //testFrame();

    createAMS("bohemian_rhapsody.txt", "test.ams");

    return 0;
}
