/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include <stdio.h>
#include "ams.h"
#include "frame.h"
#include "amp.h"
#include "define.h"
#include "autotests.h"

/**
 * Remove \r in a string
 * @param str
 */
void remove_r(char *str) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != '\r') dst++;
    }
    *dst = '\0';
}

/**
 * Create a frm file with all the frame songs
 * @param ma_playliste
 * @param new_playlist_frm
 */
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

            //Create init frame
            createInitFrame(Mysong, content);
            remove_r(content);
            fprintf(frm, "%s", content);

            // Create ticks frame
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


    testReadAMP();
    printf("\n\n");
    testFrame();
    printf("\n\n");
    testReadAMS();
    printf("\n\n");

    // Test work well on Margot's mac but not on Alexandre's computer
    createAMS("bohemian_rhapsody.txt", "test.ams");
    testCreateAMS();
    test_ams("test.ams");
    printf("\n\n");

    return 0;
}
