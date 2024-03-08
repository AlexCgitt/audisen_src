/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include <stdio.h>
#include "usb.h"
#include "ams.h"
#include "frame.h"
#include "amp.h"
#include "define.h"

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


int main(){
    printf("Demarrage du projet AUDISEN USB\n");
    FT_HANDLE ftHand;
    ftHand = initUSB();

    FILE *frm = NULL;
    frm = fopen("nouveau.frm", "w");
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


    //Get the amp file
    play = initAMP("ma_playlist.amp");

    while (!feof(play)) {

        //Get the title of the ams file
        readAMP(play, chaine);
        //printf("%s", chaine);

        // Get my song struct
        Mysong = readAMS(chaine);
        //printf("%d", Mysong.tpm);

        if (strlen(Mysong.title) != 0) {
            Mysong.title[strlen(Mysong.title)-1] = '\0';

            //Create the init frame
            createInitFrame(Mysong, content);
            writeUSB(content,ftHand);
            remove_r(content);
            fputs(content, frm);

            // Create the tick frame
            for (int i = 0; i < Mysong.nTicks; i++) {
                createTickFrame(Mysong.tickTab[i], contentick);
                printf("frame : %s",contentick);
                writeUSB(contentick, ftHand);
                remove_r(contentick);
                fputs(contentick, frm);
            }
        }
    }




    return 0;
}