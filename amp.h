/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#ifndef AUDISEN2024_AMP_H
#define AUDISEN2024_AMP_H

#include "define.h"


FILE* initAMP(char* filename);

void readAMP(FILE* pf, char * song_filename);

void closeAMP(FILE* pf);

int test_amp();

#endif //AUDISEN2024_AMP_H