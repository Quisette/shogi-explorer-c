#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shogilib.h"
#include <wchar.h>
#include <string.h>
#include <regex.h>
// initialize the project;
void initialize()
{
    struct PiecePrototype piecePrototype[14];
    piecePrototype[FU].sfen[0] = 'p';
    piecePrototype[KYO].sfen[0] = 'l';
    piecePrototype[KEI].sfen[0] = 'n';
    piecePrototype[GIN].sfen[0] = 's';
    piecePrototype[KIN].sfen[0] = 'g';
    piecePrototype[KAKU].sfen[0] = 'b';
    piecePrototype[HI].sfen[0] = 'r';
    piecePrototype[GYOKU].sfen[0] = 'k';
    // piecePrototype[FU].kif[0] = L"歩";
    // piecePrototype[KYO].kif[0] = L"香";
    // piecePrototype[KEI].kif[0] = L"桂";
    // piecePrototype[GIN].kif[0] = L"銀";
    // piecePrototype[KIN].kif[0] = L"金";
    // piecePrototype[KAKU].kif[0] = L"角";
    // piecePrototype[HI].kif[0] = L"飛";
    // piecePrototype[GYOKU].kif[0] = L"玉";
    // piecePrototype[TO].kif[1] = L"と";
    // piecePrototype[NKYO].kif[1] = L"杏";
    // piecePrototype[NKEI].kif[1] = L"圭";
    // piecePrototype[NGIN].kif[1] = L"全";
    // piecePrototype[UMA].kif[1] = L"馬";
    // piecePrototype[RYU].kif[1] = L"竜";
    // piecePrototype[GYOKU].kif[1] = L"玉";
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
char Regex(char *textToCheck, const char *regexStr)
{
    regex_t compiledRegex;
    int reti;
    int actualReturnValue = -1;
    char messageBuffer[100];

    /* CompiREG_NOMATCHle regular expression */
    reti = regcomp(&compiledRegex, regexStr, REG_EXTENDED | REG_ICASE);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        return -2;
    }

    /* Execute compiled regular expression */
    reti = regexec(&compiledRegex, textToCheck, 0, NULL, 0);
    if (!reti)
    {
        // puts("Match");
        actualReturnValue = 0;
    }
    else if (reti == REG_NOMATCH)
    {
        // puts("No match");
        actualReturnValue = 1;
    }
    else
    {
        regerror(reti, &compiledRegex, messageBuffer, sizeof(messageBuffer));
        fprintf(stderr, "Regex match failed: %s\n", messageBuffer);
        actualReturnValue = -3;
    }

    /* Free memory allocated to the pattern buffer by regcomp() */
    regfree(&compiledRegex);
    return actualReturnValue;
}