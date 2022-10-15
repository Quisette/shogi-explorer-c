#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shogilib.h"
#include <wchar.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
struct PieceAttr pieceAttr[14];
struct Board bannmenn;
// initialize the project;
void initialize()
{
    pieceAttr[FU].sfen[0] = 'p';
    pieceAttr[KYO].sfen[0] = 'l';
    pieceAttr[KEI].sfen[0] = 'n';
    pieceAttr[GIN].sfen[0] = 's';
    pieceAttr[KIN].sfen[0] = 'g';
    pieceAttr[KAKU].sfen[0] = 'b';
    pieceAttr[HI].sfen[0] = 'r';
    pieceAttr[GYOKU].sfen[0] = 'k';
    pieceAttr[FU].displayChar[0] = "歩";
    pieceAttr[KYO].displayChar[0] = "香";
    pieceAttr[KEI].displayChar[0] = "桂";
    pieceAttr[GIN].displayChar[0] = "銀";
    pieceAttr[KIN].displayChar[0] = "金";
    pieceAttr[KAKU].displayChar[0] = "角";
    pieceAttr[HI].displayChar[0] = "飛";
    pieceAttr[GYOKU].displayChar[0] = "玉";
    pieceAttr[FU].displayChar[1] = "と";
    pieceAttr[KYO].displayChar[1] = "杏";
    pieceAttr[KEI].displayChar[1] = "圭";
    pieceAttr[GIN].displayChar[1] = "全";
    pieceAttr[KAKU].displayChar[1] = "馬";
    pieceAttr[HI].displayChar[1] = "竜";
}
// reads KIF file into the program.
void readKIF(FILE *file)
{
}
// shows the current sfen (map of current bannmenn)
char *exportToSFEN(struct Board board)
{
}
bool SFENParse(char *sfen)
{
    struct SfenData sfenData;
    const char delim[2] = " ";
    char *token;
    char *rawSfenBoard;
    if (Regex(sfen, SFEN_REGEX) == 0)
    {
        token = strtok(sfen, delim);
        rawSfenBoard = token;
        token = strtok(NULL, delim);
        sfenData.turn = *token;
        token = strtok(NULL, delim);
        sfenData.mochiKomaList = token;
        token = strtok(NULL, delim);
        sfenData.moveNumber = atoi(token);
        // puts("");
        // printf("bannmenn: %s\n", rawSfenBoard);
        // printf("turn:  %c\n", sfenData.turn);
        // printf("mochiKoma:  %s\n", sfenData.mochiKomaList);
        // printf("move: %d\n", sfenData.moveNumber);
        // puts("");

        token = strtok(rawSfenBoard, "/");
        for (int i = 0; i < 9; i++)
        {
            sfenData.matrix[i] = token;
            // printf("%s\n", sfenData.matrix[i]);
            token = strtok(NULL, "/");
        }
    }
    else
        return 1;
    SFENLoad(sfenData);
    return 0;
}
// shows the board based on current database
void SFENLoad(struct SfenData data)
{
    puts("");
    for (int i = 0; i < 9; i++)
    {
        int currentIndex = 0;
        // printf("%d ", (int)strlen(data.matrix[i]));
        for (int it_char = 0; it_char < strlen(data.matrix[i]); it_char++)
        {                                    // each row
            // printf("%c", data.matrix[i][it_char]); // each character
            switch (data.matrix[i][it_char])
            {

            case 'p':case 'l':case 'n':case 's':case 'g':case 'b':case 'r':case 'k':
                bannmenn.board[i][currentIndex].type = data.matrix[i][it_char];
                bannmenn.board[i][currentIndex].owner = GOTE;
                currentIndex++;
                break;
            case 'P':case 'L':case 'N':case 'S':case 'G':case 'B':case 'R':case 'K':
                bannmenn.board[i][currentIndex].type = data.matrix[i][it_char];
                bannmenn.board[i][currentIndex].owner = SENTE;
                currentIndex++;
                break;
            case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9': // numbers (spaces)
          //faulty. Needs to be fixed.
                for (int k = 0; k < (data.matrix[i][it_char] - '0'); k++)
                {
                    // printf("[%d]", currentIndex);
                    bannmenn.board[i][currentIndex].type = ' ';
                    bannmenn.board[i][currentIndex].promoted = 0;
                    bannmenn.board[i][currentIndex].owner = 0;
                    currentIndex++;
                }
                break;
            case '+':
                bannmenn.board[i][currentIndex].promoted = true;
                break;
            default:
                break;
            }
            
        }
        // puts("");
        
    }
    // for (int i = 0; i < 9; i++)
    // {
    //     for (int j = 0; j < 9; j++)
    //     {
    //         if(bannmenn.board[i][j].type == ' '){
    //             printf("[   ]");
    //         }else
    //         printf("[%d%c%d]", bannmenn.board[i][j].promoted, bannmenn.board[i][j].type, bannmenn.board[i][j].owner);
    //     }
    //     puts("");
    // }

}
int findPieceNumber(char c){
    c = tolower(c);
    switch(c){
        case 'p':
        return FU;
        break;
        case 'l':
        return KYO;
        break;
        case 'n':
        return KEI;
        break;
        case 's':
        return GIN;
        break;
        case 'g':
        return KIN;
        break;
        case 'b':
        return KAKU;
        break;
        case 'r':
        return HI;
        break;
        case 'k':
        return GYOKU;
        break;
    }
}
void renderBoard()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(bannmenn.board[i][j].type == ' '){
                printf("  ");
            }else{
                if(bannmenn.board[i][j].owner == SENTE)
                    printColor(BLUE, pieceAttr[findPieceNumber(bannmenn.board[i][j].type)].displayChar[bannmenn.board[i][j].promoted]);
                else
                    printColor(RED, pieceAttr[findPieceNumber(bannmenn.board[i][j].type)].displayChar[bannmenn.board[i][j].promoted]);

            }
            // printf("[ %s ]", pieceAttr[findPieceNumber(bannmenn.board[i][j].type)].displayChar[bannmenn.board[i][j].promoted]);
        }
        puts("");
    }
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
