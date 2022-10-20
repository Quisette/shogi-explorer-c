#include <stdio.h>
#include "utilities.h"
#include "shogilib.h"
#include "stacklib.h"
#include <string.h>
#include <regex.h>

extern Attr_t pieceAttr[14];
extern Board_t bannmenn;
extern UserInput_t input;
extern Stack_t kifuStack;

int main(int argc, char **argv)
{
    FILE *fptr;
    char testSfen[100] = "9/9/9/9/4+B4/9/9/9/9 b - 1";
    char initSfen[100] = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1";
    char nextSfen[150];
    char outputSfen[150] = "";
    initialize();
    // printf("%d",argc);
    if(argc >= 3 ){
        if((strcmp( argv[1],"-r") == 0)){
            fptr = fopen(argv[2],"r");
            fgets(nextSfen,150,fptr);
            push(nextSfen,&kifuStack);
            if(!SFENParse(nextSfen))
            renderBoard();
        }
        else{
            printf("file opening failed. turn to initial board. \n");
        push(initSfen,&kifuStack);
        if(!SFENParse(initSfen))
        renderBoard();
        }
    }else{
        push(initSfen,&kifuStack);
        if(!SFENParse(initSfen))
        renderBoard();
        
    }
    
    int inputcode;
    while ((inputcode = userInput()) != -1)
    {
        
        if(inputcode == 1){
            revert();
            outputSfen[0] = '\0';
            exportToSFEN(outputSfen);
            push(outputSfen, &kifuStack);
            printf("%s\n", peek(&kifuStack));
        
        }
        else if (validMove(input.init, input.final))
        {
            
            outputSfen[0] = '\0';

            if(getPieceBycoord(input.init)->promoted == true){
                makeMove(input.init, input.final, 1);
            }else if(canPromote()){
                int promote;
                printf("<<成りますか？>>\n");
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
