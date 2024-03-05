/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#ifndef AUDISEN2024_AMS_H
#define AUDISEN2024_AMS_H

#include "define.h"

struct song initSong();
struct song readAMS(char* fileName);
void createAMS(char* txtFileName, char* amsFileName);
int test_ams();


#endif //AUDISEN2024