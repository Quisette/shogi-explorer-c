#include<stdio.h>
#include"shogilib.h"
#include<string.h>
#include<ctype.h>
#include<regex.h>
extern struct PiecePrototype piecePrototype[14];
int main(){
    char testSfen[100] = "lnsgkgsnl/1r5b1/ppppppp1p/7p1/9/2P6/PP1PPPPPP/1B5R1/LNSGKGSNL b - 3 ";
    initialize();
   
    printf("\n%d\n", SFENParse(testSfen));


    // wchar_t *test = L"歩";
    // wprintf(L"%ls\n", test);
    return 0;
}


