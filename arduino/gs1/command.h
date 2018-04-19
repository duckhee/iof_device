#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "analogtest.h"


#ifdef COMMAND_LOCAL
#define COMMAND_DEF
#else
#define COMMAND_DEF           extern
#endif

COMMAND_DEF int command_analogcmd(void);
COMMAND_DEF int command_analogmenu(int datapin);


#endif
