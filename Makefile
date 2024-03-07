#MakeFile squelette à modifier par les étudiants
# CAVARO Alexandre RIOU Margot 2 Caen

TARGET = audisen_usb.exe # pour la partie USB
#TARGET = audisen_sim.out


all: $(TARGET)

run: all
	@./$(TARGET)

#Etudiants : creez les cibles de votre makefile ICI, et completez
frame.o: frame.c frame.h define.h
	gcc -Wall -c frame.c -o frame.o

amp.o: amp.c amp.h define.h
	gcc -Wall -c amp.c -o amp.o

ams.o: ams.c ams.h define.h
	gcc -Wall -c ams.c -o ams.o

usb.o:usb.c usb.h define.h
	gcc -Wall -c usb.c -o usb.o

autotests.o:autotests.c autotests.h
	gcc -Wall -c autotests.c -o autotests.o

audisen_usb.out: audisen_usb.c
	gcc audisen_usb.c -o audisen_usb.out

audisen_sim.out: audisen_sim.c frame.o ams.o amp.o autotests.o
	gcc audisen_sim.c frame.o ams.o amp.o autotests.o -o audisen_sim.out



#CIBLE a garder pour la partie USB
# Commande de compilation pour Windows mingw a copier en console PowerShell
#  mingw32-make -f Makefile clear audisen_usb.exe
audisen_usb.exe: audisen_usb.c ftd2xx.h amp.o ams.o frame.o usb.o ftd2xx.lib
	gcc audisen_usb.c amp.o ams.o frame.o usb.o ftd2xx.lib -o audisen_usb.exe

clean:
	rm *.o *.out *.exe

clear:
	del *.o *.exe


