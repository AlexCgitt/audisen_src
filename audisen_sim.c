/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include <stdio.h>
#include "ams.h"
#include "frame.h"
#include "amp.h"
#include "define.h"
#include "autotests.h"

void remove_r(char *str) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != '\r') dst++;
    }
    *dst = '\0';
}

void createFRM_readPlaylist(char* ma_playliste, char* new_playlist_frm) {

    // start with frm open in write mode
    FILE *frm = NULL;
    frm = fopen(new_playlist_frm, "w");
    if (frm == NULL) {
        printf("erreur lors de l'ouverture du fichier");
        exit(0);
    }

    //variable
    FILE *play = NULL;
    char chaine[MAX_SIZE_TITLE];
    char content[INIT_FRAME_MAX_SIZE];
    char contentick[TICK_FRAME_SIZE];
    s_song Mysong;


    //recuperation of amp file
    play = initAMP(ma_playliste);

    while (!feof(play)) {

        //recuperation of ams title file
        readAMP(play, chaine);
        //printf("%s", chaine);

        // recuperation of my song struct
        Mysong = readAMS(chaine);
        //printf("%d", Mysong.tpm);
        if (strlen(Mysong.title) != 0) {
            Mysong.title[strlen(Mysong.title)-1] = '\0';
            //recuperation of init frame
            createInitFrame(Mysong, content);
            remove_r(content);
            fprintf(frm, "%s", content);
            for (int i = 0; i < Mysong.nTicks; i++) {
                createTickFrame(Mysong.tickTab[i], contentick);
                remove_r(contentick);
                fprintf(frm, "%s", contentick);
            }

        }
    }
}


int main(){
    printf("Demarrage du projet AUDISEN\n");


    //test_amp();

    //test_ams();

    //test_frame();

    //testFrame();

    //testReadAMP();

   //createFRM_readPlaylist("ma_playlist.amp", "new.frm");


    createAMS("Tetris.txt", "Tetris.ams");
    createFRM_readPlaylist("ma_playlist.amp", "new.frm");

    //testCreateAMS();
    //test_ams();
    //test_ams();


    return 0;
}
