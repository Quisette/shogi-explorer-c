#include<stdio.h>
#include"utilities.h"
#include"shogilib.h"
#include<string.h>
#include<regex.h>

extern struct PiecePrototype piecePrototype[14];
int main(int argc, char** argv){
    char testSfen[100] = "lnsgkgsnl/1r5b1/ppppppp1p/7p1/9/2P6/PP1PPPPPP/1B5R1/LNSGKGSNL b - 3 ";
    initialize();
    printColor(BLUE,piecePrototype[4].kif[0]);
    printColor(RED,piecePrototype[5].kif[0]);

    printf("\n%d\n", SFENParse(testSfen));

    // printf("%s",coloredtext("36","歩"));
    // wchar_t *test = L"歩";
    // wprintf(L"%ls\n", test);
    return 0;
}


