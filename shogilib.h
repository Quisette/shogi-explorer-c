#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef SHOGI_LIB
#define SHOGI_LIB

// type of pieces 
enum PieceType{ FU,KYO,KEI,GIN,KIN,KAKU,HI,GYOKU };
enum PieceSFEN{p,l,n,s,g,b,r,k};
// shows the owner of the piece
enum PieceOwner{SENTE = 0, GOTE = 1};
struct PiecePrototype{
    char toSfen;
    char toKIF;
    char** PossibleMovement;
};
struct PieceOnBoard{
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
    //
   PieceOnBoard board[9][9]; 
   // Komadais for each player
   Komadai senteKomadai, goteKomadai;
};
struct Komadai{
    int komaList[8];
    /*
    komaList stores the number of each pieces, numbered by PieceType. 
    EX: komaList[3] stores the number of GIN pieces 
    */
};

// reads KIF file into the program.
void readKIF( FILE *file);
// shows the current sfen (map of current bannmenn)
char* toSFEN(Board);
// shows the board based on current database
void renderBoard();
// let the user browse through shogi moves
void scrollKifu();
// let user enter the move to interact with the shogi board 
void userInputKifu();
// back to the origin from user inputs
void returnToOrigin();

#endif //SHOGI_LIB