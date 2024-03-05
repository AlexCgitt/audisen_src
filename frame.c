/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"
#include "ams.h"
#include "amp.h"


/**
 * Create an init frame shaped like #<content>*<checksum><CR><LF>
 * @param mySong
 * @param frame
 */
void createInitFrame(s_song mySong, char* frame){
    char content[INIT_FRAME_MAX_SIZE];
    char title[]="";

    //strtolower(title, mySong.title);

    sprintf(content,"%s,%d,%d", mySong.title, mySong.tpm, mySong.nTicks);


    int checksum = 0;

    for(int i=0; i<strlen(content); i++){
        checksum ^= content[i] ;
    }

    printf("Le checksum =>\n");
    printf("%02x\n", checksum);

    sprintf(frame, "#%s*%02x\r\n\0", content, checksum);

    printf("%s\n", frame);

}

/**
 * Create a tick frame shaped like #<mode>,<accent>,<note1>,<note2>,<note3>,<note4>*<checksum><CR><LF>
 * @param myTick
 * @param frame
 */
void createTickFrame(s_tick myTick, char* frame){
    char content[TICK_FRAME_SIZE];

    sprintf(content,"0,%d,%d,%d,%d,%d", myTick.accent, myTick.note[0], myTick.note[1], myTick.note[2], myTick.note[3]);

    int checksum = 0;

    for(int i=1; i< strlen(content); i++){
        checksum ^= content[i] ;
    }

    printf("Le checksum =>\n");
    printf("%d\n", checksum);

    sprintf(frame, "#%s*%02x\r\n\0", content, checksum);

    printf("%s", frame);

}


void test_frame(){
    printf("debut du test frame\n");

    s_song mySong = readAMS("bohemian_rhapsody.ams");
    s_tick myTick;
    char frame[MAX_SIZE_TITLE];

    myTick.accent = 1;
    myTick.note[0]=11;
    myTick.note[1]=23;
    myTick.note[2]=27;
    myTick.note[3]=34;

    createTickFrame(myTick, frame);
}