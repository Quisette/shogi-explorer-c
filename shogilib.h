#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linkedlist/linkedlist.h"
#include "stacklib.h"
#include "utilities.h"
#ifndef SHOGI_LIB
#define SHOGI_LIB
#define SFEN_REGEX "[+plnsgkrbPLNSGKRB1-9]{1,18}\\/[+plnsgkrbPLNSGKRB1-9]{1,18}\\/[+plnsgkrbPLNSGKRB1-9]{1,18}\\/[+plnsgkrbPLNSGKRB1-9]{1,18}\\/[+plnsgkrbPLNSGKRB1-9]{1,18}\\/[+plnsgkrbPLNSGKRB1-9]{1,18}\\/[+plnsgkrbPLNSGKRB1-9]{1,18}\\/[+plnsgkrbPLNSGKRB1-9]{1,18}\\/[+plnsgkrbPLNSGKRB1-9]{1,18} [wb] [-plnsgkrbPLNSGKRB1-9]+ [1-9]+"
#define INPUT_REGEX "[0-9]{1,2}\\s[1-9]{1,2}"
#define INPUT_REGEX_FULL "[0-9]{1,2}\\s[1-9]{1,2}\\s[a-z]{2,7}"
typedef struct Attr Attr_t;
typedef struct Komadai Komadai_t;
typedef struct UserInput UserInput_t;
typedef struct Location Location_t;
typedef struct Piece Piece_t;
typedef struct Board Board_t;
typedef struct SfenData SfenData_t;

// Enumation of type of pieces
enum PieceType {
    FU,
    KYO,
    KEI,
    GIN,
    KIN,
    KAKU,
    HI,
    GYOKU,
};

// Owner of the piece
enum PieceOwner {
    SENTE = 0,
    GOTE = 1
};
// Attributes (basic data) of the piece types
struct Attr {
    char sfen;
    char *displayChar[2];
    char *name[2];
};
// A single piece on the board.
struct Piece {
    char type;
    bool promoted;
};
// Place to indicate the number of captured pieces
struct Komadai {
    u_int8_t komaList[8];
    /*
    komaList stores the number of each pieces, numbered by PieceType.
    EX: komaList[3] stores the number of GIN pieces
    */
};
// Data needed in a game 
struct Board {
    //
    Piece_t pieces[9][9];
    // Komadais for each player
    Komadai_t senteKomadai, goteKomadai;
    int moveNumber;
    bool turn;
};
// Stores the data of segmented sfen data 
struct SfenData {
    char *matrix[9];
    char turn;  // turn
    char *mochiKomaList;
    int moveNumber;
};
// Location (or vector) of a piece
struct Location {
    int X;
    int Y;
};
// structure of a user input
struct UserInput {
    char type[10];
    Location_t init;
    Location_t final;
};

// initialize the project;
void initialize();
// reads KIF file into the program.
void readKifu(FILE *file);
// shows the current sfen (map of current bannmenn)
void exportToSFEN(char *str);
// shows the board based on current database+
void renderBoard();
// let the user browse through shogi moves
void scrollKifu(bool function, Node_t *current);
// let user enter the move to interact with the shogi board
int userInput();
// back to the origin from user inputs
void returnToOrigin();
// Parse the raw sfen string into the board based on given string.
bool SFENParse(char *sfen);
// Load the processed sfen data into the board memory.
void SFENLoad(SfenData_t data);
// get piece number based on character(Piece.type).
int getPieceNumber(char c);
// transfer the input coordinate into the array coordinate
char coordTransfer(char axis, char input);
// Get the piece based on the input coordinate.
Piece_t *getPieceBycoord(Location_t loc);
// Get the kanji of the piece  
char *getPieceName(Piece_t piece);
// Move the piece from initial position to final prosition (with promotion).
void makeMove(Location_t init, Location_t final, bool promote);
// Gets the owner based on Piece.type
char owner(char pieceType);
// Validate if kinshou and other promoted pieces with equivalent move rule moves correctly. 
bool kinMove(Location_t loc, bool owner);
// Validate if the pieces moves correctly. 
bool validMove(Location_t init, Location_t final);
// Validate if oushou and gyokushou moves correctly. 
bool gyokuMove(Location_t loc);
// get piece enumeraion number based on string of romaji.
int getPieceNumByName(char *str);
// detects the move rule based on 
bool kinDetection(char type, Location_t diff);
// Validate if kakugyou moves correctly. 
bool kakuMove(Location_t diff, Location_t init);
// Validate if hisya moves correctly. 
bool hisyaMove(Location_t diff, Location_t init);
// Generate kifu based on played game on quit.
void generateKifu(Stack_t *stack);
// Shows if the piece can promote.
bool canPromote();
// reverts the move made by user. 
bool revert();
// initializes the basic data used.
void initializeBoard();
#endif  // SHOGI_LIB
