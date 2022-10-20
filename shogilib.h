#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "stacklib.h"
#include <math.h>
#include <stdbool.h>

#ifndef SHOGI_LIB
#define SHOGI_LIB
#define SFEN_REGEX "[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9}\\/[+plnsgkrbPLNSGKRB1-9]{1,9} [wb] [-plnsgkrbPLNSGKRB1-9]+ [1-9]+"
#define INPUT_REGEX "[0-9]{1,2}\\s[1-9]{1,2}"
#define INPUT_REGEX_FULL "[0-9]{1,2}\\s[1-9]{1,2}\\s[a-z]{2,7}"
typedef struct Attr Attr_t;
typedef struct Komadai Komadai_t;
typedef struct UserInput UserInput_t;
typedef struct Location Location_t;
typedef struct Piece  Piece_t;
typedef struct Board Board_t;
typedef struct SfenData SfenData_t;




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
struct Attr
{
    char sfen;
    char *displayChar[2];
    char *name[2];
};
struct Piece
{
    // indicates if there is a piece. if the position is empty, this bool should be turned down.
    //  when active is false, the program should not read other value of this object.
    // shows the type of the current piece
    char type;
    // shows if this piece is promoted
    bool promoted;
};
struct Komadai
{
    u_int8_t komaList[8];
    /*
    komaList stores the number of each pieces, numbered by PieceType.
    EX: komaList[3] stores the number of GIN pieces
    */
};
struct Board
{
    //
    Piece_t pieces[9][9];
    // Komadais for each player
    Komadai_t senteKomadai, goteKomadai;
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
struct Location
{
    int X;
    int Y;
};
struct UserInput
{
    char type[10];
    Location_t init;
    Location_t final;
};

// initialize the project;
void initialize();
// reads KIF file into the program.
void readKifu(FILE *file);
// shows the current sfen (map of current bannmenn)
void exportToSFEN(char* str);
// shows the board based on current database+
void renderBoard();
// let the user browse through shogi moves
void scrollKifu(bool function);
// let user enter the move to interact with the shogi board
int userInput();
// back to the origin from user inputs
void returnToOrigin();
bool SFENParse(char *sfen);
void SFENLoad(SfenData_t data);
int getPieceNumber(char c);
char coordTransfer(char axis, char input);
// struct Location coordTransfer(struct Location loc);
Piece_t *getPieceBycoord(Location_t loc);
char *getPieceName(Piece_t piece);
void makeMove(Location_t init, Location_t final, bool promote);
char owner(char pieceType);
Location_t *moveDiff(Location_t init, Location_t final);
bool kinMove(Location_t loc, bool owner);
bool validMove(Location_t init, Location_t final);
bool gyokuMove(Location_t loc);
int getPieceNumByName(char* str);
bool kinDetection(char type, Location_t diff);
bool kakuMove(Location_t diff, Location_t init);
bool hisyaMove(Location_t diff, Location_t init);
void generateKifu(Stack_t *stack);
bool canPromote();
bool revert();
void initializeBoard();
#endif // SHOGI_LIB
