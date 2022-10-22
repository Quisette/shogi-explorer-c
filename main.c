#include <stdio.h>
#include "utilities.h"
#include "shogilib.h"
#include "stacklib.h"
#include"linkedlist/linkedlist.h"
#include <string.h>
#include <regex.h>

extern Attr_t pieceAttr[14];
extern Board_t bannmenn;
extern UserInput_t input;
extern Stack_t kifuStack;
extern List_t *kifuList;
int main(int argc, char **argv)
{
    FILE *fptr;
    char testSfen[100] = "9/9/9/9/4+B4/9/9/9/9 b - 1";
    char initSfen[100] = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1";
    char nextSfen[150];
    char usedSfen[150] = "";
    initialize();
    initializeStack(&kifuStack);
    // printf("%d",argc);
    if (argc >= 3)
    {
        if ((strcmp(argv[1], "--readsfen") == 0))
        {
            fptr = fopen(argv[2], "r");
            fgets(nextSfen, 150, fptr);
            push(nextSfen,&kifuStack);
            strcpy(usedSfen, nextSfen);
            if (!SFENParse(nextSfen))
                renderBoard();
        }
        else if (strcmp(argv[1], "--loadsfenstack") == 0)
        {
            fptr = fopen(argv[2], "r");
            readKifu(fptr);
            if (!SFENParse(kifuList->head->data))
                renderBoard();
            else puts("SFEN parsing failed\n");
        }
        else
        {
            printf("file opening failed. turn to initial board. \n");
            push(initSfen, &kifuStack);
            strcpy(usedSfen, initSfen);

            if (!SFENParse(initSfen))
                renderBoard();
        }
    }
    else
    {
        push(initSfen,&kifuStack);
        strcpy(usedSfen, initSfen);

        if (!SFENParse(initSfen))
            renderBoard();
    }

    int inputcode;
    while ((inputcode = userInput()) != -1)
    {
        if (inputcode == 1)
        {
            usedSfen[0] = '\0';
            revert();
            strcpy(usedSfen, peek(&kifuStack));
            // push(usedSfen, &kifuStack);
        }
        else if (inputcode == 2)
            puts("stack viewing complete.");
        else if (inputcode == 3){
            puts("SFEN: ");
            usedSfen[0] = '\0';
            exportToSFEN(usedSfen);
            puts(usedSfen);
        }
        else if (validMove(input.init, input.final))
        {

            usedSfen[0] = '\0';

            if (getPieceBycoord(input.init)->promoted == true)
            {

                makeMove(input.init, input.final, 1);
            }
            else if (canPromote())
            {
                int promote;
                char buffer[7];

                printf("<<成りますか？>>(naru, narazu)\n>>");
                while (scanf("%s", buffer))
                {
                    if (strcmp(buffer, "naru") == 0)
                    {
                        makeMove(input.init, input.final, 1);
                        break;
                    }
                    else if (strcmp(buffer, "narazu") == 0)
                    {
                        makeMove(input.init, input.final, 0);
                        break;
                    }
                    else
                        printf("Your promotion argument is not OK.\n>>");
                }
                getc(stdin);

            }
            else
            {
                makeMove(input.init, input.final, 0);
            }

            renderBoard();
            exportToSFEN(usedSfen);
            push(usedSfen, &kifuStack);
            // puts(usedSfen);
        }

        else
            printf("Invalid move.\n");
    }
    reverse(&kifuStack);
    generateKifu(&kifuStack);
    return 0;
}
