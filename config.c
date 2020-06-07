#include "config.h"

Field* parseConfig ( xmlDocPtr doc, xmlNodePtr cur )
{
    static Field fields[10];

    int fieldCount = 0;
    xmlChar *key;
    cur = cur->xmlChildrenNode;

    while ( cur != NULL)
    {
        if ( ( !xmlStrcmp ( cur->name, (const xmlChar *) "input" ) ) )
        {
            key = xmlNodeListGetString ( doc, cur->xmlChildrenNode, 1 );

            xmlChar *xPosStr = xmlGetProp( cur, "x" );
            xmlChar *yPosStr = xmlGetProp( cur, "y" );
            xmlChar *sizeStr = xmlGetProp( cur, "size" );

            Field field = createField( xPosStr, yPosStr, sizeStr, key, INPUT );

            xmlFree( xPosStr );
            xmlFree( yPosStr );
            xmlFree( sizeStr );

            fields[ fieldCount ] = field;

            fieldCount++;

            xmlFree ( key );
        }
        else if ( ( !xmlStrcmp ( cur->name, (const xmlChar *) "label" ) ) )
        {
            key = xmlNodeListGetString ( doc, cur->xmlChildrenNode, 1 );

            xmlChar *xPosStr = xmlGetProp( cur, "x" );
            xmlChar *yPosStr = xmlGetProp( cur, "y" );

            Field field = createField( xPosStr, yPosStr, 0, key, LABEL );

            xmlFree( xPosStr );
            xmlFree( yPosStr );

            fields[ fieldCount ] = field;

            fieldCount++;

            xmlFree ( key );
        }

        cur = cur->next;

        Field endField = { 0, 0, END, 0, "END" };

        fields[ fieldCount ] = endField;
    }

    return fields;
}

Field* parseDoc ( char *docname )
{
    Field* fields = NULL;
    xmlDocPtr doc;
    xmlNodePtr cur;

    doc = xmlParseFile ( docname );

    if ( doc != NULL)
    {
        cur = xmlDocGetRootElement ( doc );

        if ( cur != NULL)
        {
            if ( ! xmlStrcmp ( cur->name, (const xmlChar *) "config" ))
            {
                cur = cur->xmlChildrenNode;

                while ( cur != NULL)
                {
                    if ( ( !xmlStrcmp ( cur->name, (const xmlChar *) "screen" ) ) )
                    {
                        fields = parseConfig ( doc, cur );
                    }

                    cur = cur->next;
                }

                xmlFreeDoc ( doc );
            }
            else
            {
                fprintf (stderr, "document of the wrong type, root node != config" );
                xmlFreeDoc ( doc );
            }
        }
        else
        {
            fprintf (stderr, "empty document\n" );

            xmlFreeDoc ( doc );
        }
    }

    return fields;
}

Field* loadDoc ( char *docName )
{
    Field *fields = parseDoc ( docName );

    return fields;
}

static Field createField( xmlChar* xPos, xmlChar* yPos, xmlChar* size, xmlChar* message, enum CtlType type )
{
    Field field;
    char *messageStr  = malloc( MAX_FIELD_SIZE );
    char *valueStr    = "";
    char *originalMsg = (char *)message;

    memset( messageStr, 0, MAX_FIELD_SIZE );
    strncpy( messageStr, (char *)originalMsg, strlen( originalMsg ) );

    if ( xPos != NULL )
    {
        field.xPos = atoi( xPos );
        field.yPos = atoi( yPos );
    }

    if ( size != NULL )
        field.size = atoi( size );
    else
        field.size = -1;

    field.type    = type;
    field.message = &messageStr[0];
    field.value   = valueStr;

    return field;
}