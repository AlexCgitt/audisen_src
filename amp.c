/**
 * @authors CAVARO Alexandre RIOU Margot 2 Caen
 */

#include "define.h"
#include "amp.h"


FILE* initAMP(char* filename){
    FILE * pf = NULL;
   
    return pf;
}



void readAMP(FILE* pf, char * song_filename){

}

void closeAMP(FILE* pf){
    if (pf){
        fclose(pf);
    }else{
        printf("The file doesn't exist.");
    }
}