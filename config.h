#ifndef CONFIG
#define CONFIG
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libxml/xmlmemory.h"
#include "libxml/parser.h"
#include "types.h"

Field* parseConfig(xmlDocPtr doc, xmlNodePtr cur );

Field* parseDoc( char *docname );

Field* loadDoc( char *docName );

static Field createField( xmlChar* xPos, xmlChar* yPos, xmlChar* size, xmlChar* message, enum CtlType type );
#endif