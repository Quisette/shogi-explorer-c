#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef SHOGI_LIB
#define SHOGI_LIB

// type of pieces 
enum PieceType{ FU,KYO,KEI,GIN,KIN,KAKU,HI,GYOKU };
// shows the owner of the piece
enum PieceOwner{SENTE, GOTE};

struct Piece{
    //indicates if there is a piece. if the position is empty, this bool should be turned down.
    // when active is false, the program should not read other value of this object.
    bool active;
    //shows the type of the current piece  
    char type;
    //shows the owner of piece
    bool owner;
    //shows if this piece is promoted
    bool promoted;     
};
struct Board{
   Piece board[8][8]; 
};
struct Komadai{
    int komaList[8];
    /*
    komaList stores the number of each pieces, numbered by PieceType. 
    EX: komaList[3] stores the number of GIN pieces 
    */
};
// reads KIF file into the program.
void readKIF( FILE *File);
// shows the board based on current database
void renderBoard();
// let the user browse through shogi moves
void scrollKifu();
// let user enter the move to interact with the shogi board 
void userInputKifu();
// back to the origin from user inputs
void returnToOrigin();

#endif //SHOGI_LIB