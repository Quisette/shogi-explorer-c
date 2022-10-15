#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shogilib.h"
#include <string.h>
#include <ctype.h>
struct PieceAttr pieceAttr[14];
struct Board bannmenn;
struct UserInput input;
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

        token = strtok(rawSfenBoard, "/");
        for (int i = 0; i < 9; i++)
        {
            sfenData.matrix[i] = token;
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
    /* turn and move number parsing */
    (data.turn == 'w')?bannmenn.turn = SENTE:GOTE;
    bannmenn.moveNumber = data.moveNumber;
    /* main board parsing */
    for (int i = 0; i < 9; i++)
    {
        int currentIndex = 0; 
        for (int it_char = 0; it_char < strlen(data.matrix[i]); it_char++)
        {                                    // each row
            
            switch (data.matrix[i][it_char])// each character
            {

            case 'p':case 'l':case 'n':case 's':case 'g':case 'b':case 'r':case 'k':
                bannmenn.pieces[i][currentIndex].type = data.matrix[i][it_char];
                
                currentIndex++;
                break;
            case 'P':case 'L':case 'N':case 'S':case 'G':case 'B':case 'R':case 'K':
                bannmenn.pieces[i][currentIndex].type = data.matrix[i][it_char];
                
                currentIndex++;
                break;
            case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9': // numbers (spaces)
                for (int k = 0; k < (data.matrix[i][it_char] - '0'); k++)
                {
                    bannmenn.pieces[i][currentIndex].type = ' ';
                    bannmenn.pieces[i][currentIndex].promoted = 0;
                    currentIndex++;
                }
                break;
            case '+':
                bannmenn.pieces[i][currentIndex].promoted = true;
                break;
            default:
                break;
            }
            
        }
    }
    /* Mochikoma Parsing */
    int komaNumber = 1;
    for (int it_char = 0; it_char <strlen(data.mochiKomaList); it_char++){
        char objectChar = data.mochiKomaList[it_char];
        if(isdigit(objectChar)) komaNumber = ctoi(objectChar);
        else if (isupper(objectChar)) {
            bannmenn.senteKomadai.komaList[getPieceNumber(objectChar)]+= komaNumber;
            komaNumber = 1;
            }
        else if(islower(objectChar)) {
            bannmenn.goteKomadai.komaList[getPieceNumber(objectChar)]+= komaNumber ;
            komaNumber = 1;
            }
    }
    // for(int i = 0; i < 8; i++) {
    //     printf("%d %d %d\n",i, bannmenn.senteKomadai.komaList[i],bannmenn.goteKomadai.komaList[i]);
    // }

}
int getPieceNumber(char c){
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
    printf("\033c");
    //displays data
    puts("------------------");

    printf("%d手目、",bannmenn.moveNumber);
    (bannmenn.turn)? printf("後手番です\n"): printf("先手番です\n");
    puts("------------------");
    //displays Board 
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(bannmenn.pieces[i][j].type == ' '){
                printf("  ");
            }else{
                if(!owner(bannmenn.pieces[i][j].type))
                    printColor(BLUE, getPieceName(bannmenn.pieces[i][j]));
                else
                    printColor(RED,  getPieceName(bannmenn.pieces[i][j]));

            }
        }
        puts("");
    }
    puts("------持  駒------");

    // displays mochiKoma
    bool komaEmpty = 1;
    printColor(BLUE,"先手  ");
    for (int i = GYOKU; i >= FU; i--){
        if(bannmenn.senteKomadai.komaList[i] != 0) komaEmpty = 0;
        for (int j = 1; j <= bannmenn.senteKomadai.komaList[i]; j++)
        printColor(BLUE,pieceAttr[i].displayChar[0]);
    } 
    if(komaEmpty) printColor(BLUE,"なし");

    komaEmpty = 1;
    printColor(RED,"\n後手  ");
    for (int i = GYOKU; i >= FU; i--){
        if(bannmenn.goteKomadai.komaList[i] != 0) komaEmpty = 0;
        for (int j = 1; j <= bannmenn.goteKomadai.komaList[i]; j++)
        printColor(RED,pieceAttr[i].displayChar[0]);
    } 
    if(komaEmpty) printColor(RED,"なし") ;
 
    puts("\n------------------");

}
// let the user browse through shogi moves
void scrollKifu()
{
    

}
// let user enter the move to interact with the shogi board
void userInput()
{
    char rawInput[20] ;
    
    char *token;
    fgets(rawInput,20,stdin);
    if(Regex(rawInput,INPUT_REGEX) == 1){
        puts("Format Error. "); return;
    }
    token = strtok(rawInput, " ");
    input.init.X = ctoi(*token);
    input.init.Y = ctoi(*(token + 1)) ;
    token = strtok(NULL, " ");
    input.final.X = ctoi(*token);
    input.final.Y = ctoi(*(token + 1)) ;
    token = strtok(NULL, " ");
    input.type = token;
    // printf("%d%d, %d%d , %s", input.init.X, input.init.Y,  input.final.X, input.final.Y,input.type);
}
// back to the origin from user inputs
void returnToOrigin()
{
}

char coordTransfer(char axis, char input){
    if(axis != 'X' && axis != 'Y') return -1;
    else if(axis == 'X') return 9 - input;
    else return input-1;
}

struct PieceOnBoard *getPieceBycoord(struct Location loc){
    return &bannmenn.pieces[coordTransfer('Y',loc.Y)][coordTransfer('X',loc.X)];
}

char* getPieceName(struct PieceOnBoard piece){
    return pieceAttr[getPieceNumber(piece.type)].displayChar[piece.promoted];
}
void makeMove(struct Location init, struct Location final, bool promote){

    if(owner(getPieceBycoord(final)->type) == SENTE){
       bannmenn.goteKomadai.komaList[getPieceNumber(getPieceBycoord(final)->type)]++; 
    }else{
       bannmenn.senteKomadai.komaList[getPieceNumber(getPieceBycoord(final)->type)]++; 

    }
    getPieceBycoord(final)->promoted = promote;
    getPieceBycoord(final)->type = getPieceBycoord(init)->type;
  
    getPieceBycoord(init)->type = ' ';
    bannmenn.moveNumber++;
    bannmenn.turn = !bannmenn.turn;


}

char owner(char pieceType){
    if (pieceType == ' ') 
        return -1;
    else if(isupper(pieceType)) return SENTE; 
    else return GOTE;
}