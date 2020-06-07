#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "curses.h"
#include "config.h"

int main(void)
{
    ctlTypeNames[0] = "LABEL";
    ctlTypeNames[1] = "INPUT";
    ctlTypeNames[2] = "LIST";
    ctlTypeNames[3] = "END";

    int maxlines;
    int maxcols;

    initscr();
    cbreak();
    noecho();

    clear();

    start_color();

    init_pair( NORMAL_COLOUR, COLOR_WHITE, COLOR_BLACK );
    init_pair( FIELD_COLOUR, COLOR_CYAN, COLOR_BLUE );

    maxlines = LINES - 1;
    maxcols  = COLS - 1;

    Field *currField = NULL;
    Field *fields    = loadDoc( "/data/c-code/curses/config.xml" );

    dumpFields( fields );

    enum CtlType endType = INPUT;

    while ( endType != END )
    {
        Field *field = fields;

        endType = field->type;

        if ( endType != END )
        {
            if ( field->type == LABEL )
            {
                mvaddstr( field->yPos, field->xPos, field->message );

                field->value = "";
            }
            else if ( field->type == INPUT )
            {
                if ( currField == NULL )
                    currField = field;

                field->value = input( field->yPos, field->xPos, field->message, field->size, 0 );
            }

            fields++;
        }
    }

    currField->value = input( currField->yPos, currField->xPos, currField->message, currField->size, 1 );

    dumpFields( fields );

    mvaddstr( maxlines, 0, "Press any key to quit" );

    refresh();

    getch();
    endwin();

    exit(0 );
}

char* input( int y, int x, char *mesg, int fieldSize, int waitForResponse )
{
    static char response[80] = {'\0'};

    mvprintw ( y, x, "%s", mesg );

    int  xOffset   = strlen ( mesg ) + 2;
    int  xIndex    = 0;
    char inputChar = 0;
    int  inputSize = 0;

    setField ( y, x + xOffset, fieldSize );

    if ( waitForResponse )
    {
        while ( inputChar != '\n' )
        {
            inputChar = getch();
            inputSize = strlen ( response );

            if ( inputChar == 8 )
            {
                if ( xIndex > 0 )
                {
                    xIndex--;
                    response[xIndex] = '\0';
                    mvaddch ( y, xOffset + xIndex, ' ' );

                    move ( y, xOffset + xIndex );
                }
            }
            else if ( inputSize < fieldSize )
            {
                mvaddch ( y, xOffset + xIndex, inputChar );

                response[xIndex] = inputChar;

                xIndex++;
            }
        }

        response[xIndex] = '\0';

        mvprintw ( LINES - 2, 0, "You Entered: %s", response );
    }

    return response;
}

void setField( int y, int x, int size )
{
    x -= 2;

    attron( COLOR_PAIR( FIELD_COLOUR ) );

    for ( int i=0; i<size; i++ )
    {
        mvaddch( y, x + i, ' ' );
    }

    move( y, x );

    attron( COLOR_PAIR( NORMAL_COLOUR ) );
}

void dumpFields( Field* fields )
{
    enum CtlType endType = INPUT;

    while ( endType != END )
    {
        Field *field = fields;

        endType = field->type;

        if ( endType != END )
        {
            printf( "Type : %s - X : %d - Y : %d - : Size : %d - MSG : %s - VAL : %s\n", ctlTypeNames[ field->type ],
                    field->xPos,
                    field->yPos,
                    field->size,
                    field->message,
                    field->value );

            fields++;
        }
    }
}