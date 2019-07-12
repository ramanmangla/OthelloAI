//Othello - Part 2 - Smarter AI

#include <stdio.h>
#include <stdbool.h>
#include "OthelloGame.h"

//int findSmarterMove(char board[][26], int n, char colour, int *row, int *col);
//int findSmartestMove(char board[][26], int n, char colour, int *row, int *col);

int main(void){

    char board[26][26];
    int boardDim; //Board's size assumed to be an even number
    int i, j, k, l;
    int arrIndexComp = 0, arrIndexPlayer = 0, coinsComp = 0, coinsPlayer = 0; //Number of legal moves
    char inputRow, inputCol, compColour, playerColour;
    int turnCounter; //For deciding the turn
    bool moveValid = false, boardFull = false;
    int noValidMoves = 0; //For checking two consecutive no valid moves conditions
    int rowAI, colAI; //AI's move

    printf("Enter the board dimension: ");
    scanf("%d", &boardDim);
    printf("Computer plays (B/W) : ");
    scanf(" %c", &compColour);

    //Arrays to store available moves with column 0 for row, column 1 for column
    //and column 2 for the score
    char movesAvailableComp[boardDim*boardDim][2];
    char movesAvailablePlayer[boardDim*boardDim][2];
    int score[boardDim*boardDim];

    initializeBoard(board, boardDim);
    printBoard(board, boardDim);

    if(compColour == 'B'){
        playerColour = 'W';
        turnCounter = 0;
    }else{
        playerColour = 'B';
        turnCounter = 1;
    }

    //Game is full or not, both players dont have available moves (break condition)
    while(boardFull == false && noValidMoves < 2){

        boardFull = true;

        if(turnCounter % 2 == 0){
            //Computer's turn
            arrIndexComp = findMoves(board, boardDim, movesAvailableComp, compColour, score);

            if(arrIndexComp != 0){
                //If computer has moves available
                computeScore(board, boardDim, movesAvailableComp, compColour, arrIndexComp, score);

                //Finding the position with maximum score
                int maxPos = 0;

                for(i = 1; i < arrIndexComp; i++){
                    if(score[i] > score[maxPos]){
                        maxPos = i;
                    }
                }

                printf("Computer places %c at %c%c.\n", compColour, movesAvailableComp[maxPos][0], movesAvailableComp[maxPos][1]);
                //Checking legality of each direction and flipping the coins in that direction
                for(k = -1; k < 2; k++){
                    for(l = -1; l < 2; l++){
                        if(k != 0 || l !=0 ){
                            if(checkLegalInDirection(board, boardDim, movesAvailableComp[maxPos][0],
                                                     movesAvailableComp[maxPos][1], compColour, k, l)){
                                flipCoins(board, boardDim, movesAvailableComp[maxPos][0],
                                          movesAvailableComp[maxPos][1], compColour, k, l);
                            }
                        }
                    }
                }

                //Assigning the position computer's colour
                board[movesAvailableComp[maxPos][0] - 'a'][movesAvailableComp[maxPos][1] - 'a'] = compColour;
                printBoard(board, boardDim);
                turnCounter++;

                if(noValidMoves == 1){
                    noValidMoves = 0;
                }

            }else{
                //If computer doesn't have any available moves
                printf("%c player has no valid move.\n", compColour);
                turnCounter++;
                noValidMoves++;
            }

        }else{
            //Player's turn
            arrIndexPlayer = findMoves(board, boardDim, movesAvailablePlayer, playerColour, score);

            if(arrIndexPlayer != 0){
//                If player has moves available
                printf("Enter move for colour %c (RowCol): ", playerColour);
                scanf(" %c%c", &inputRow, &inputCol);

                //Testing AI is here
                //findSmarterMove(board, boardDim, playerColour, &rowAI, &colAI);
//                findSmartestMove(board, boardDim, playerColour, &rowAI, &colAI);
//                printf("Testing AI move (row, col): %c%c\n", rowAI + 'a', colAI + 'a');
                inputRow = rowAI + 'a';
                inputCol = colAI + 'a';

                for(i = 0; i < arrIndexPlayer; i++){
                    if((movesAvailablePlayer[i][0] == inputRow) && (movesAvailablePlayer[i][1] == inputCol)){
                        moveValid = true;
                        break;
                    }
                }

                if(moveValid == true){
                    //Checking legality of each direction and flipping the coins in that direction
                    for(k = -1; k < 2; k++){
                        for(l = -1; l < 2; l++){
                            if(k != 0 || l !=0 ){
                                if(checkLegalInDirection(board, boardDim, inputRow, inputCol, playerColour, k, l)){
                                    flipCoins(board, boardDim, inputRow, inputCol, playerColour, k, l);
                                }
                            }
                        }
                    }

                    //Assigning the position player's colour
                    board[inputRow - 'a'][inputCol - 'a'] = playerColour;
                    printBoard(board, boardDim);
                    turnCounter++;

                    if(noValidMoves == 1){
                        noValidMoves = 0;
                    }

                }else{
                    printf("Invalid move.\n");
                    break;
                }

            }else{
                printf("%c player has no valid move.\n", playerColour);
                turnCounter++;
                noValidMoves++;
            }

        }

        for(i = 0; i < boardDim; i++){
            for(j = 0; j < boardDim ; j++){
                if(board[i][j] == 'U'){
                    boardFull = false;
                    break;
                }
            }
        }

    }

    //Counting the number of coins of each colour
    for(i = 0; i < boardDim; i++){
        for(j = 0; j < boardDim ; j++){
            if(board[i][j] == compColour){
                coinsComp++;
            }else if(board[i][j] == playerColour){
                coinsPlayer++;
            }
        }
    }

    if(coinsPlayer > coinsComp){
        printf("%c player wins.", playerColour);
    }else if(coinsPlayer < coinsComp){
        printf("%c player wins.", compColour);
    }else{
        printf("Draw!.");
    }

    return 0;
}