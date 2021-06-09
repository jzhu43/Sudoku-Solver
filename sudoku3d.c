//Partnered with Nicholas Chin.//
#include <stdio.h>
#include <stdlib.h>

// Declare printSudoku function
void printSudoku(int***);
// Declare solveSudoku function
int solveSudoku(int***);

//Helper functions. You can define any functions that can help your solve the problem
int checkPosition(int ***arr, int*, int*, int*);                    //This function goes through the grid looking at the compenets of the grid and reports back the values.
int checkPosition(int ***arr, int *grid, int *row, int *element){
    int i, j, k;
    for (i = 0; i < 9; i++){            //Looks through the 9 grids
        for (j = 0; j < 3; j++){        //Looks through each row in 1 grid
            for (k = 0; k < 3; k++){    //Looks throught elements 1 to 3 of the specific row.
                if (*(*(*(arr + i) + j) + k) == 0) {
                    *(grid) = i;
                    *(row) = j;
                    *(element) = k;
                    return 1;       //Denotes that there are still values in the board.
                }
            }
        }
    }
    return 0; // This would denote that the function has gone through the 9 3x3 sudoku board.
}
int checkRow(int ***arr, int, int, int);
int checkRow(int ***arr, int grid, int col, int num){
    int row;
    if (grid < 3){   //If statement Checks Grid 1 to 3 and checks Rows 1 to 3
        row = 0;    
    }
    else if (grid < 6){     //If statment Checks Grid 4 to 6 and Rows 4 to 6
        row = 3;            
    }
    else            //If statement checks Grid 7 to 9 and rows 7 to 9
        row = 6;    

    int stop = row + 3;     //If statment to check if the grid grid = 0, if it is equal to 0 then the grid is 1, if true it will continue to check from rows 1 to 3.

    for (row; row < stop; row++){                                   //Will loop from row 1 to row 3
        for (int element = 0; element < 3; element++){              //Checks from element 1 to 3 of the grid's row.
            if (num == (*(*(*(arr + row) + col) + element))){       //Checks rows from the right.
                return 1;
            }
        }
    }
    return 0;
}
int checkColumn(int ***arr, int, int, int);             //Function checks throughs the columns of the grid
int checkColumn(int ***arr, int grid, int row, int num){
    int col;
    if (grid == 0 || grid == 3 | grid == 6){    //Looking at Grids 1, 4, 7
        col = 0;                                //Looking at Columns 1, 4, 7
    }
    else if (grid == 1 || grid == 4 || grid == 7){  //Looking at Grids 2, 5, 8
        col = 1;                                    //Looking at Columns 2, 5, 8
    }
    else                                            //Looking at Grid 3, 6, 9
        col = 2;                                    //Looking at Colums 3, 6, 9

    int stop = col + 7;             //If grid = 0, therfore it's grids 1, 4, 7. Starts the check from columns 1, 4, 7
    int element;
    for (col; col < stop; col = col + 3){                           // Would hop around through columns 1 to 4 to 7
        for (element = 0; element < 3; element++){                 //This checks through elements 1 to 3 of said grid's column
            if (num == (*(*(*(arr + col) + element) + row))){      //Goes downwards to check the columns
                return 1;
            }
        }
    }
    return 0;
}
int checkBox(int ***arr, int, int);                             //Function checks the grid values to see where in the grid it's at.
int checkBox(int ***arr, int grid, int num){    
    int row, element;
    for (row = 0; row < 3; row++){                              //Goes through all the rows
        for (element = 0; element < 3; element++){              //Goes through the numbers that are in the grid.
            if (*(*(*(arr + grid)+ row)+ element) == num){      
                return 1;                                       //Returns 1 to denote that the number matches
            }
        }
    }
    return 0;                                                   //Numbers don't match up
}

/*
The main program reads a text file containing the block values of the Sudoku grid.
It then saves each 3x3 block into a 2D array. The Sudoku grid is composed of 9 3x3 blocks.
DO NOT MODIFY THE MAIN FUNTION!!!
*/
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;
    int ***blocks = (int***)malloc(9 * sizeof(int**));

    // Open file for reading
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open File!\n");
        return 0;
    }

    // Read 9x9 blocks into 2D arrays
    for(i=0; i<9; i++)
    {
        *(blocks+i) = (int**)malloc(3 * sizeof(int*));
        printf("Reading numbers in block %d... \n", i+1);
        for(j=0; j<3; j++)
        {
            *(*(blocks+i)+j) = (int*)malloc(3 * sizeof(int));

                fscanf(fptr, "%d %d %d", *(*(blocks+i)+j), *(*(blocks+i)+j)+1, *(*(blocks+i)+j)+2);
                printf("%d %d %d\n", *(*(*(blocks+i)+j)), *(*(*(blocks+i)+j)+1), *(*(*(blocks+i)+j)+2));
        }
    }
    
    // Print out original Sudoku grid
     printf("Printing Sudoku before being solved:\n");
     printSudoku(blocks);

    // Call solveSudoku and print out result
  printf("\nSolving Sudoku...\n\n");
    if(solveSudoku(blocks)){
        printf("Sudoku solved!\n");
        printSudoku(blocks);
    }
    else
        printf("This Sudoku cannot be solved!\n");

   return 0;
}


void printSudoku(int*** arr){
    // This function will print out the complete Sudoku grid (arr). It must produce the output in the SAME format as the samples in the instructions.   
    
    // Your implementation here
    int i;
    int j;
    int k;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            for(k = 0; k < 3; k++){
                        printf("%d", *(*(*(arr + j)+i)+k));
                            printf(" ");
                    }
                printf("|");
            }
        printf("\n");
        }
        printf("---------------------");
    //Row 1 finished
        printf("\n");
    for(i = 0; i < 3; i++){
            for(j = 3; j < 6; j++){
                    for(k = 0; k < 3; k++){
                            printf("%d", *(*(*(arr + j)+i)+k));
                            printf(" ");
                    }
                printf("|");
            }
        printf("\n");
        }
        printf("---------------------");
        //Row 2 finished
        printf("\n");
        for(i = 0; i < 3; i++){
            for(j = 6; j < 9; j++){
                    for(k = 0; k < 3; k++){
                            printf("%d", *(*(*(arr + j)+i)+k));
                            printf(" ");
                    }
                printf("|");
            }
        printf("\n");
        }
    //Row 3 finished
}


int solveSudoku(int*** blocks){
    // This is the function to solve the Sudoku (blocks). Feel free to use any helper functions.
    // YOU MUST NOT USE ANY ARRAY NOTATION ([])!
    //Your implementation here
int grid, row, element; 
    int num = 1;
    if (checkPosition(blocks, &grid, &row, &element) == 0) {        
        return 1;
    }
    else {
        for (num = 1; num < 10; num++) {    //Goes through all the numbers in a grid             //A if statement of all the checks to see that they have returned 0
            if(checkColumn(blocks, grid, element, num) == 0 && checkRow(blocks, grid, row, num) == 0 && checkBox(blocks, grid, num) == 0 && *(*(*(blocks + grid) + row)+ element) == 0) {   
                    *(*(*(blocks + grid) + row)+ element) = num;            
                if (solveSudoku(blocks) == 1){
                    return 1;
                }
                else {
                    *(*(*(blocks + grid)+ row)+ element) = 0; //sets element to 0
                }
            }
        }
    }
return 0;
}
