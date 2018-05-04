#include <wiringPi.h>
#include <stdio.h>

#define SW     5
#define LED    1


int switchControl()
{
    int i;

    pinMode(SW, INPUT);
    pinMode(LED, OUTPUT);

    for(i = 0; i < 10000000; i++)
    {
        if(digitalRead(SW) == LOW ){
            printf("switch off");
            digitalWrite(LED, HIGH);
            delay(1000);
            digitalWrite(LED, LOW);
        }
    }

    return 0;
}

int main(int argc, char** argv)
{
    wiringPiSetup();

    switchControl();

    return 0;
}