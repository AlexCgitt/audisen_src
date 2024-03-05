/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"
#include "ams.h"


/**
 * Create an init frame shaped like #<content>*<checksum><CR><LF>
 * @param mySong
 * @param frame
 */
void createInitFrame(s_song mySong, char* frame){
    char caractere[] = ",#*";

    int content[TICK_FRAME_SIZE];
    int index = 0;
    for(int i= 0; i< strlen(mySong.title); i++){
        content[i] = mySong.title[i];
        index = i-1;
    }
    content[index] = caractere[0];
    content[index+2] = caractere[0];
    content[index+1] = mySong.tpm;
    content[index+3] = '16';


    int checksum = content[0];

    printf("- %c -\n", content[0]);
    for(int i=1; i<TICK_FRAME_SIZE; i++){
        checksum ^= content[i] ;
        printf("- %c -\n", content[i]);
        frame[i] = content[i-1];
    }

    printf("Le checksum =>\n");
    printf("%d\n", checksum);

    frame[0] = caractere[1];
    frame[-3] = caractere[2];
    frame[-2] = checksum;
    frame[-1] = (int)"\r\n\0";

    printf("%s", frame);

}

/**
 * Create a tick frame shaped like #<mode>,<accent>,<note1>,<note2>,<note3>,<note4>*<checksum>*<CR><LF>
 * @param myTick
 * @param frame
 */
void createTickFrame(s_tick myTick, char* frame){
    char zero[] = "0";
    char accent = (char)myTick.accent;
    char coma[1] = ",";
    char hach[1] = "#";
    char star[1] = "*";
    char end[] = "<CR><LF>\0";

    char* content = "";
    content = strcat(content, (const char *) &zero);
    content  = strcat(content, (const char *) &coma);
    content = strcat(content, &accent);
    for(int i = 0; i< sizeof(myTick.note); i++){
        char note = (char) myTick.note[i];
        content = strcat(content, (const char *) &coma);
        content = strcat(content, &note);
    }

    int checksum = 0;
    for(int i=0; i<strlen(content)-1; i++){
        checksum += content[i] ^ content[i+1];
    }

    char check = (char) checksum;
    frame = strcat(frame, hach);
    frame = strcat(frame, content);
    frame = strcat(frame, star);
    frame = strcat(frame, &check);
    frame = strcat(frame, star);
    frame = strcat(frame, end);

    printf("%s",frame);
}


void test_frame(){

    s_song mySong = readAMS("bohemian_rhapsody.ams");
    char frame[INIT_FRAME_MAX_SIZE];

    createInitFrame(mySong, frame);
}