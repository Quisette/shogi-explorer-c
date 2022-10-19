#include <stdio.h>
#include "utilities.h"
#include "shogilib.h"
#include "stacklib.h"
#include <string.h>
#include <regex.h>

extern Attr_t pieceAttr[14];
extern Board_t bannmenn;
extern UserInput_t input;
Stack_t kifuStack;

int main(int argc, char **argv)
{
    
    char testSfen[100] = "9/9/9/9/4+B4/9/9/9/9 b - 1";
    char initSfen[100] = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1";
    char nextSfen[150] = "ln3g1nl/3sg1k2/p2psp1p1/4p1p1p/1p1P5/4PP2P/PP+rS2PP1/4G1SK1/L4G1NL b RB2Pbn 45 ";
    char outputSfen[150];
    initialize();
    if(!SFENParse(initSfen))
        renderBoard();
    
    while (userInput() == 0)
    {

        if (validMove(input.init, input.final))
        {
            outputSfen[0] = '\0';
            if(canPromote()){
                int promote;
                bool promotebool;
                printf("成りますか\n");
                scanf("%d", &promote);
                if(promote >= 1){
                    makeMove(input.init, input.final, 1);
                }else 
                    makeMove(input.init, input.final, 0);
                getc(stdin);
            }
            else{
                makeMove(input.init, input.final, 0);
            }
               
            renderBoard();
            puts("SFEN: ");
            exportToSFEN(outputSfen);
            push(outputSfen, &kifuStack);
            printf("%s\n", peek(&kifuStack));
        }
        else
            printf("Invalid move.\n");
    }
    generateKifu(&kifuStack);
    return 0;
}
