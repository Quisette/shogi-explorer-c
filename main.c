#include<stdio.h>
#include"utilities.h"
#include"shogilib.h"
#include<string.h>
#include<regex.h>

extern struct PieceAttr pieceAttr[14];
extern struct Board bannmenn;
extern struct UserInput input;
int main(int argc, char** argv){
    char testSfen[100] = "lnsgkgsnl/1r5b1/ppppppp1p/7p1/9/2P6/PP1PPPPPP/1B5R1/LNSGKGSNL b - 3 ";
    char nextSfen[150] = "ln3g1nl/3sg1k2/p2psp1p1/4p1p1p/1p1P5/4PP2P/PP+rS2PP1/4G1SK1/L4G1NL b RB2Pbn 45 ";
    initialize();
  
    if(!SFENParse(testSfen)) renderBoard();
    puts("-----------------------");
    if(!SFENParse(nextSfen)) renderBoard();
    // scrollKifu();
    userInput();
    // printf("%d%d\n",coordTransfer('X',input.init.X),coordTransfer('Y',input.init.Y));
    printf("%c\n",getPieceBycoord(input.init.X, input.init.Y).type);
    return 0;
}


