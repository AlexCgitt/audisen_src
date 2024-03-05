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
	// The content
    char tempo = (char)mySong.tpm;
    char tick = (char)mySong.nTicks;
    char coma[1] = ",";
    char hach[1] = "#";
    char star[1] = "*";
    char end[] = "<CR><LF>\0";

    char *content = "";
    content = strcat(content, mySong.title);
    content= strcat(content, coma);
    content = strcat(content, &tempo);
    content = strcat(content, coma);
    content = strcat(content, &tick);
    int checksum = 0;

    for(int i=0; i<strlen(content)-1; i++){
        checksum += content[i] ^ content[i+1];
    }
    char check = (char) checksum;

    frame = strcat(frame, hach);
    frame = strcat(frame, content);
    frame = strcat(frame, star);
    frame = strcat(frame, &check);
    frame = strcat(frame, end);

    printf("%s", frame);

}

/**
 * Create a tick frame shaped like #<mode>,<accent>,<note1>,<note2>,<note3>,<note4>*<checksum>*<CR><LF>
 * @param myTick
 * @param frame
 */
void createTickFrame(s_tick myTick, char* frame){
    char zero[] = "0";
    char accent = myTick.accent;
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

int main() {
    s_song mySong = readAMS("bohemian_rhapsody.ams");
    char frame[] = "";

    createInitFrame(mySong, frame);
}