#ifndef __ANALOGTEST_H__
#define __ANALOGTEST_H__

#ifdef ANALOGTEST_LOCAL
#define ANALOGTEST_DEF
#else
#define ANALOGTESET_DEF         extern
#endif

ANALOGTESET_DEF int get_value(int pin);


#endif
