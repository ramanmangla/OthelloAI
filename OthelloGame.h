//
// Created by Raman Mangla
//

#ifndef OTHELLO_OTHELLOGAME_H
#define OTHELLO_OTHELLOGAME_H

//Function to print the board
void printBoard(char board[][26], int n){

    int i, j, k;

    //Printing index row
    printf("  ");

    for(i = 0; i < n; i++){
        printf(" %c ", (char) (i + 'a'));
    }

    //Printing index column and board
    printf("\n");

    for(k = 0;k < n; k++){
        printf("%c ", (char) (k + 'a'));

        for(j = 0; j < n ; j++){
            printf(" %c ", board[k][j]);
        }

        printf("\n");
    }

}

//Function to initialize the board configuration
void initializeBoard(char board[][26], int n){

    int i, j;

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            board[i][j] = '*';
        }
    }

    board[(n / 2) - 1][(n / 2) - 1] = 'W';
    board[(n / 2) - 1][n / 2] = 'B';
    board[n / 2][(n / 2) - 1] = 'B';
    board[n / 2][n / 2] = 'W';

}

//Function to check whether a position is in bounds of the board
bool positionInBounds(int n, char row, char col){

    int rowIndex = ((int) (row)) - 'a';
    int colIndex = ((int) (col)) - 'a';

    if(rowIndex < n && colIndex < n && rowIndex >= 0 && colIndex >= 0){
        return true;
    }else{
        return false;
    }

}

//Function to check if a position is legal by checking a direction
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol){

    int rowIndex = ((int)(row)) - 'a';
    int colIndex = ((int)(col)) - 'a';
    int count = 1, dim = n;
    bool legal = false;
    int rowIncrement = count * deltaRow;
    int colIncrement = count * deltaCol;

    if(board[rowIndex][colIndex] == 'U'){
        while(board[rowIndex + rowIncrement][colIndex + colIncrement] != colour &&
              board[rowIndex + rowIncrement][colIndex + colIncrement] != 'U' &&
              positionInBounds(dim, row + rowIncrement, col + colIncrement)){
            count++;
            rowIncrement = count * deltaRow;
            colIncrement = count * deltaCol;
        }

        if(board[rowIndex + rowIncrement][colIndex + colIncrement] == colour && count > 1 &&
           positionInBounds(dim, row + rowIncrement, col + colIncrement)){
            legal = true;
        }
    }

    return legal;

}

//Function to flip coins when a legal position and a legal direction is given
void flipCoins(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol){

    int rowIndex = ((int)(row)) - 'a';
    int colIndex = ((int)(col)) - 'a';
    int count = 1;
    int rowIncrement = count * deltaRow;
    int colIncrement = count * deltaCol;

    while(board[rowIndex + rowIncrement][colIndex + colIncrement] != colour){
        board[rowIndex + rowIncrement][colIndex + colIncrement] = colour;
        count++;
        rowIncrement = count * deltaRow;
        colIncrement = count * deltaCol;
    }

}


//Function to find all available moves
int findMoves(char board[][26], int n, char movesAvailable[][2], char colour, int score[]){

    bool legality;
    int ctr, i, j, k, l;
    char row, col;
    int arrIndex = 0;

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            row = 'a' + i;
            col = 'a' + j;
            ctr = 0;

            if(board[i][j] == 'U'){
                for(k = -1; k < 2; k++){
                    for(l = -1; l < 2; l++){
                        if(k != 0 || l !=0 ){
                            legality = checkLegalInDirection(board, n, row, col, colour, k, l);

                            if(legality == true){
                                ctr++; //ctr increments whenever a direction is legal
                            }
                        }
                    }
                }

                if(ctr != 0){
                    movesAvailable[arrIndex][0] = row;
                    movesAvailable[arrIndex][1] = col;
                    score[arrIndex] = 0; //Initializing scores to 0
                    arrIndex++;
                }
            }
        }
    }

    return arrIndex;

}

//Function to compute score for each available move for computer's turn where score = no. of coins flipped
void computeScore(char board[][26], int n, char movesAvailable[][2], char colour, int arrIndex, int scoreArr[]){

    int j;
    char row, col;
    int rowIndex, colIndex;
    int score;

    for(j = 0; j < arrIndex; j++){
        row = movesAvailable[j][0];
        col = movesAvailable[j][1];
        score = 0;

        rowIndex = ((int)(row)) - 'a';
        colIndex = ((int)(col)) - 'a';

        if((rowIndex == n - 1 && colIndex == n - 1) || (rowIndex == 0 && colIndex == 0) ||
           (rowIndex == n - 1 && colIndex == 0) || (rowIndex == 0 && colIndex == n - 1)){
            //Corners
            score = 20;
        }else if((rowIndex == n - 2 && colIndex == n - 1) || (rowIndex == n - 2 && colIndex == 0) ||
                 (rowIndex == n - 1 && colIndex == 1) || (rowIndex == n - 1 && colIndex == n - 2) ||
                 (rowIndex == 1 && colIndex == 0) || (rowIndex == 1 && colIndex == n - 1) ||
                 (rowIndex == 0 && colIndex == 1) || (rowIndex == 0 && colIndex == n - 2) ||
                 (rowIndex == 1 && colIndex == 1) || (rowIndex == n - 2 && colIndex == n - 2) ||
                 (rowIndex == 1 && colIndex == n - 2) || (rowIndex == n - 2 && colIndex == 1)){
            //Adjacent to corners
            score = 6;
        }else if(rowIndex == n - 1 || rowIndex == 0 || colIndex == n - 1 || colIndex == 0){
            //Edges
            score = 15;
        }else if(rowIndex == n - 2 || rowIndex == 1 || colIndex == n - 2 || colIndex == 1){
            //Adjacent
            score = 7;
        }else if(rowIndex == n - 3 || rowIndex == 2 || colIndex == n - 3 || colIndex == 2){
            //Adjacent to adjacent
            score = 9;
        }

        scoreArr[j] = score;
    }
}

#endif //OTHELLO_OTHELLOGAME_H
