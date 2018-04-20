#include <wiringPi.h>
#include <stdio.h>

#define LED   1

int LedControl(int gpioPin)
{
    if(gpioPin == NULL){
        printf("not intpu gpioPin !");
        gpioPin = LED;
    }

    int i;
    pinMode(gpioPin, OUTPUT);
    for(i = 0; i < 5; i++)
    {
        digitalWrite(gpioPin, HIGH);
        delay(1000);
        digitalWrite(gpioPin, LOW);
        delay(1000);
    }
}


int main(int argc, char** argv)
{
    int gno;
    if(argc < 2)
    {
        printf("usage : %s GPIO_NO\n", argv[0]);
        return -1;
    }
    gno = atoi(argv[1]);
    wiringPiSetup();
    LedControl(gno);

    return 0;
}