#define COMMAND_LOCAL

#include "command.h"

COMMAND_DEF int command_analogcmd(void);
COMMAND_DEF int command_analogmenu(int datapin);


COMMAND_DEF int command_analogmenu(int datapin)
{
  int key;
  

 while((key=xxx_main_menu()) != 0)
 {
  switch(key)
  {
   case '1':
    printf("No.1\n");
    get_value(datapin);
    break;


   case '2':
    printf("No.2\n");

    break;
   case '3':
    printf("No.3\n");

    break;
   case '4':
    printf("No.4\n");
    break;

   case '5':
    printf("No.5\n");

    break;
   case '6':
    printf("No.6\n");

    break;
   case '7':
    printf("No.7\n");

    break;
   case '8':
    printf("No.8\n");

    break;

   case '9':
    printf("No.9\n");

    break;

   case '0':
    printf("No.0\n");
  
    break;

   case 'a':
    printf("No.a\n");



    break;


   case 'b':
    printf("No.b\n");

    break;

   case 'c':
    printf("No.c\n");



    break;

   case 'd':
    printf("No.d\n");



    break;

   case 'e':
    printf("No.e\n");



    break;

   case 'f':
    printf("No.f\n");



    break;

   case 'g':
    printf("No.g\n");



    break;

   case 'h':
    printf("No.h\n");


    break;

   case 'i':
    printf("No.i\n");

    break;

   case 'j':
    printf("No.j\n");
    
    break;

   case 'k':
    printf("No.k\n");
    
    break;

   case 'q':
    return 0;


  }
 }
 return 0;
}
}
COMMAND_DEF int command_analogcmd(void)
{
  int key;
  Serial.println("\n");
  Serial.print("-------------------------------------------------\n");
  Serial.println("              ANALOG MENU                        ");
  Serial.println("1.analog test                                    ");
  Serial.println("-------------------------------------------------\n");
}

