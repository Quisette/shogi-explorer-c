#include <regex.h>
#include <stdio.h>
#include <string.h>

// #include "linkedlist/linkedlist.h"
#include "shogilib.h"
#include "stacklib.h"
#include "utilities.h"

extern Attr pieceAttr[14];
extern Board bannmenn;
extern UserInput input;
extern Stack kifuStack;
extern LinkedList kifuList;
int main(int argc, char **argv) {
    FILE *fptr;
    char initSfen[100] = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1";
    char sfenBuffer[150] = "";
    initialize();
    initializeStack(&kifuStack);

    if (argc >= 3) {
        if ((strcmp(argv[1], "--readsfen") == 0)) {
            fptr = fopen(argv[2], "r");
            fgets(sfenBuffer, 150, fptr);
            push(sfenBuffer, &kifuStack);
            if (!SFENParse(sfenBuffer))
                renderBoard();
        } else if (strcmp(argv[1], "--replay") == 0) {
            fptr = fopen(argv[2], "r");
            readKifu(fptr);
            if (!SFENParse((char*)(**(kifuList.head)).data))
                renderBoard();
            else
                puts("SFEN parsing failed\n");

            Node currentState = *(*kifuList.head);
            char arg;
            // printf("\n>>");
            system("/bin/stty raw");
            while (arg = getc(stdin)) {
                system ("/bin/stty cooked");
                
                if (arg == 'f'){
                    puts("");
                    scrollKifu(1, &currentState);
                    printf(">>");
                    system("/bin/stty raw");
                }
                else if (arg == 'b'){
                    puts("");
                    scrollKifu(0, &currentState);
                    printf(">>");
                    system("/bin/stty raw");
                }
                else if (arg == 'q'){
                    
                    system ("/bin/stty cooked");
                    break;
                
                }else{
                    printf("\ninvalid input.\n");//faulty on front \n
                    printf(">>");
                    system("/bin/stty raw");

                }
               
                
            }
            
            return 0;
        } else {
            printf("file opening failed. turn to initial board. \n");
            pushBack(&kifuList, createNode(initSfen) );
            if (!SFENParse(initSfen))
                renderBoard();
        }
    } else {
        pushBack(&kifuList, createNode(initSfen) );
        if (!SFENParse(initSfen))
            renderBoard();
    }

    int inputcode;
    while ((inputcode = userInput()) != -1) {
        if (inputcode == 1) {
            revert();
        } else if (inputcode == 2)
            puts("stack viewing complete.");
        else if (inputcode == 3) {
            puts("SFEN: ");
            sfenBuffer[0] = '\0';
            exportToSFEN(sfenBuffer);
            puts(sfenBuffer);
        } else if (validMove(input.init, input.final)) {
            sfenBuffer[0] = '\0';

            if (getPieceBycoord(input.init)->promoted == true || forcePromote()) {
                makeMove(input.init, input.final, 1);

            } else if (canPromote()) {
                int promote;
                char buffer[10];

                printf("<<成りますか？>>(naru, narazu)\n>>");
                while (fgets(buffer, 10, stdin)) {
                    if (strcmp(buffer, "naru\n") == 0) {
                        makeMove(input.init, input.final, 1);
                        break;
                    } else if (strcmp(buffer, "narazu\n") == 0) {
                        makeMove(input.init, input.final, 0);
                        break;
                    } else
                        printf("Your promotion argument is not OK.\n>>");
                }

            } else {
                makeMove(input.init, input.final, 0);
            }

            renderBoard();
            exportToSFEN(sfenBuffer);
            pushBack(&kifuList,createNode(sfenBuffer));
            // push(sfenBuffer, &kifuStack);
        }

        else
            printf("Invalid move.\n");
    }
    generateKifu(kifuList);
    // reverse(&kifuStack);
    // generateKifu(&kifuStack);
    return 0;
}
