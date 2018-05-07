#include <wiringPi.h>
#include <stdio.h>

int fndControl(int num)
{
    int i;
    int gpioPins[4] = {4, 1, 16, 15};
    int number[10][4] = {
                        {0, 0, 0, 0},
                        {0, 0, 0, 1},
                        {0, 0, 1, 0},
                        {0, 0, 1, 1},
                        {0, 1, 0, 0},
                        {0, 1, 0, 1},
                        {0, 1, 1, 0},
                        {0, 1, 1, 1},
                        {1, 0, 0, 0},
                        {1, 0, 0, 1}
    };

    for(i = 0; i < 4; i++)
    {
        digitalWrite(gpioPins[i], number[num][i]? HIGH : LOW);
    }
    delay(1000);
    for(i = 0; i < 4; i++)
    {
        digitalWrite(number[num][i], LOW);
    }
    getchar();

    return 0;
}

int main(int argc, char** argv)
{
    int no;
    if(argc < 2)
    {
        printf("Usage : %s NO\n", argv[0]);
        return -1;
    }
    no = atoi(argv[1]);
    wiringPiSetup();
    fndControl(no);

    return 0;
}
