GCC = gcc

OBJ = $(GCC) -o



all: led fnd light


led : 
	$(OBJ) led wiringPiLed.c -l wiringPi

fnd :
	$(OBJ) fnd wiringPifnd.c -l wiringPi

light :
	$(OBJ) light wiringPiLight.c -l wiringPi





clean :
	rm -rf led fnd light
