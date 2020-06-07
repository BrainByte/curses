#ifndef MAIN
#define MAIN

#define NORMAL_COLOUR   1
#define FIELD_COLOUR    2
#include "types.h"

Field fields[100];

void setField( int y, int x, int size );
char* input( int y, int x, char *mesg, int fieldSize, int waitForResponse );
void dumpFields( Field* fields );
#endif
