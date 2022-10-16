#include <stdio.h>
#include <stdlib.h>
#include"utilities.h"
#include <math.h>
#include <stdbool.h>

#ifndef SHOGI_LIB
#define SHOGI_LIB
#define SFEN_REGEX  "[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9} [wb] [-plnsgkrbPLNSGKRB1-9]+ [1-9]+"
#define INPUT_REGEX "[1-9]{1,2}\\s[1-9]{1,2}"
#define INPUT_REGEX_FULL "[1-9]{1,2}\\s[1-9]{1,2}\\s[a-z]{2,5}"

// type of pieces

enum PieceType
{
    FU,
    KYO,
    KEI,
    GIN,
    KIN,
    KAKU,
    HI,
    GYOKU,
};

// shows the owner of the piece
enum PieceOwner
{
    SENTE = 0,
    GOTE = 1
};
struct PieceAttr
{
    char sfen[2];
    char*  displayChar[2];
    char **moveList;
    char **promotedMoveList;
};
struct PieceOnBoard
{
    // indicates if there is a piece. if the position is empty, this bool should be turned down.
    //  when active is false, the program should not read other value of this object.
    // shows the type of the current piece
    char type;
    // shows the owner of piece
    // shows if this piece is promoted
    bool promoted;
};
struct Komadai
{
    int komaList[8];
    /*
    komaList stores the number of each pieces, numbered by PieceType.
    EX: komaList[3] stores the number of GIN pieces
    */
};
struct Board
{
    //
    struct PieceOnBoard pieces[9][9];
    // Komadais for each player
    struct Komadai senteKomadai, goteKomadai;
    int moveNumber;
    bool turn;
};
struct SfenData
{
    
    char *matrix[9];
    char turn; // turn
    char *mochiKomaList;
    int moveNumber;
};
struct Location{
    int X;
    int Y;
};
struct UserInput{
    char* type;
    struct Location init;
    struct Location final;
};

// initialize the project;
void initialize();
// reads KIF file into the program.
void readKIF(FILE *file);
// shows the current sfen (map of current bannmenn)
char *exportToSFEN(struct Board board);
// shows the board based on current database+
void renderBoard();
// let the user browse through shogi moves
void scrollKifu();
// let user enter the move to interact with the shogi board
void userInput();
// back to the origin from user inputs
void returnToOrigin();
bool SFENParse(char *sfen);
void SFENLoad(struct SfenData data);
int getPieceNumber(char c );
char coordTransfer(char axis, char input);
// struct Location coordTransfer(struct Location loc);
struct PieceOnBoard *getPieceBycoord(struct Location loc);
char* getPieceName(struct PieceOnBoard piece);
void makeMove(struct Location init, struct Location final, bool promote);
char owner(char pieceType);
struct Location *moveDiff(struct Location init, struct Location final);
bool kinMove(struct Location loc, bool owner);
bool validMove(struct Location init, struct Location final, struct PieceOnBoard piece);
#endif // SHOGI_LIB
