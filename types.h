#ifndef TYPES_H
#define TYPES_H

#define MAX_FIELD_SIZE 50

enum CtlType { LABEL, INPUT, LIST, END };
char* ctlTypeNames[4];

typedef struct {
    int xPos;
    int yPos;
    enum CtlType type;
    int size;
    char *message;
    char *value;
} Field;

#endif
