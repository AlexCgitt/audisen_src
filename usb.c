/**
 * @authors Cavaro Alexandre Riou Margot Groupe 2 Caen
 */

#include "define.h"
#include "frame.h"
#include "ftd2xx.h"
#include "usb.h"


FT_HANDLE initUSB(){
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    ftStatus = FT_Open(0,&ftHandle);
    if (ftStatus == FT_OK) {
        printf("statut open is ok\n");
    }
    else {
        printf("ERROR open handle\n");
    }

    /* Initialize the baud */
    ftStatus = FT_SetBaudRate(ftHandle, 9600);
    if (ftStatus == FT_OK) {
        printf("statut baud is ok\n");
    } else {
        printf("ERROR baud\n");
    }

    /* Initialize the data */
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    if (ftStatus == FT_OK) {
        printf("statut data is ok\n");
    }else {
        printf("ERROR def data\n");
    }

    /* Initialize the flow control */
    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0); // A voir si les null passent bien en paramettre de fonction
    if (ftStatus == FT_OK) {
        printf("statut flow control is ok\n");
    } else {
        printf("ERROR flow control\n");
    }

    /* Initialize the timeouts */
    ftStatus = FT_SetTimeouts(ftHandle, 1000, 1000);
    if (ftStatus == FT_OK) {
        printf("statut timeouts is ok\n");
    }else {
        printf("ERROR timeout\n");
    }

    return ftHandle;

}
void closeUSB(FT_HANDLE ftHandle){
        FT_Close(ftHandle);
}


void writeUSB(char* frame, FT_HANDLE ftHandle){
    FT_STATUS ftStatus;
    DWORD BytesWritten;


    ftStatus = FT_Write(ftHandle, frame, strlen(frame), &BytesWritten);
    if (ftStatus == FT_OK) {
        // FT_Write OK
        //printf("l'ecriture c'est ok");
    }
    else {
        // FT_Write Failed
        printf("ERROR ecriture");

    }
}


