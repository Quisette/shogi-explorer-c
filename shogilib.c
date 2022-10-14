#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shogilib.h"
#include <wchar.h>
#include <string.h>
#include <regex.h>
struct PiecePrototype piecePrototype[14];
struct Board bannmenn;
// initialize the project;
void initialize()
{
    piecePrototype[FU].sfen[0] = 'p';
    piecePrototype[KYO].sfen[0] = 'l';
    piecePrototype[KEI].sfen[0] = 'n';
    piecePrototype[GIN].sfen[0] = 's';
    piecePrototype[KIN].sfen[0] = 'g';
    piecePrototype[KAKU].sfen[0] = 'b';
    piecePrototype[HI].sfen[0] = 'r';
    piecePrototype[GYOKU].sfen[0] = 'k';
    piecePrototype[FU].kif[0] = "歩";
    piecePrototype[KYO].kif[0] = "香";
    piecePrototype[KEI].kif[0] = "桂";
    piecePrototype[GIN].kif[0] = "銀";
    piecePrototype[KIN].kif[0] = "金";
    piecePrototype[KAKU].kif[0] = "角";
    piecePrototype[HI].kif[0] = "飛";
    piecePrototype[GYOKU].kif[0] = "玉";
    piecePrototype[FU].kif[1] = "と";
    piecePrototype[KYO].kif[1] = "杏";
    piecePrototype[KEI].kif[1] = "圭";
    piecePrototype[GIN].kif[1] = "全";
    piecePrototype[KAKU].kif[1] = "馬";
    piecePrototype[HI].kif[1] = "竜";
    piecePrototype[GYOKU].kif[1] = "玉";

}
// reads KIF file into the program.
void readKIF(FILE *file)
{
}
// shows the current sfen (map of current bannmenn)
char *toSFEN(struct Board board)
{
}
bool SFENParse(char *sfen)
{
    const char sfenRegex[300] = SFEN_REGEX;
    struct SfenData sfenData;
    const char delim[2] = " ";
    char *token;

    if (Regex(sfen, sfen) == 0)
    {
        token = strtok(sfen, delim);
        sfenData.bannmenn = token;
        token = strtok(NULL, delim);
        sfenData.turn = *token;
        token = strtok(NULL, delim);
        sfenData.mochiKomaList = token;
        token = strtok(NULL, delim);
        sfenData.moveNumber = atoi(token);

        printf("bannmenn: %s\n", sfenData.bannmenn);
        printf("turn:  %c\n", sfenData.turn);
        printf("mochiKoma:  %s\n", sfenData.mochiKomaList);
        printf("move: %d\n", sfenData.moveNumber);
    }

    return 0;
}
// shows the board based on current database
void renderBoard()
{
}
// let the user browse through shogi moves
void scrollKifu()
{
}
// let user enter the move to interact with the shogi board
void userInputKifu()
{
}
// back to the origin from user inputs
void returnToOrigin()
{
}
