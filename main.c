#include<stdio.h>
#include"utilities.h"
#include"shogilib.h"
#include<string.h>
#include<regex.h>

extern struct PieceAttr pieceAttr[14];
int main(int argc, char** argv){
    char testSfen[100] = "lnsgkgsnl/1r5b1/ppppppp1p/7p1/9/2P6/PP1PPPPPP/1B5R1/LNSGKGSNL b - 3 ";
    char nextSfen[300] = "ln3g1nl/3sg1k2/p2psp1p1/4p1p1p/1p1P5/4PP2P/PP+rS2PP1/4G1SK1/L4G1NL b RB2Pbn 45 ";
    initialize();
  
    if(!SFENParse(testSfen)) renderBoard();
    puts("-----------------------");
    if(!SFENParse(nextSfen)) renderBoard();



    // printf("%s",coloredtext("36","歩"));
    // wchar_t *test = L"歩";
    // wprintf(L"%ls\n", test);
    return 0;
}


