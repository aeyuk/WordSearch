/*CATE YUK
Takes an integer size and a filename as its two command-line arguments, printing a 2D array of a word search and returning the number of appearances of a user-entered word.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//free the allocated space after use
char** allocateSpace(int rows, int cols) {
    char **puzzle;
    puzzle = malloc(sizeof(char *) * rows); //allocate memory
    for (int a = 0; a < rows; a++) {
        puzzle[a] = malloc(sizeof(char) * cols);
        if (puzzle == NULL) {
            printf("No more memory");
        }
    }
    return puzzle;
}

void scanPuzzle(int argc, char**argv, FILE *fp, char **puzzle, int rows, int cols) {
   fp = fopen(argv[2], "r");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(fp, " %c", &puzzle[i][j]);
        }
    }
}   

void printPuzzle(char **puzzle, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", puzzle[i][j]);
        }
    printf("\n");
    }
}


int leftToRight(char **puzzle, char *word, int rows, int cols, char **dots) {
    int num = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((puzzle[i][j] == word[0]) && (strlen(word) <= (cols - j))) {
                int matched = 1;
                for (int k = 0; k < strlen(word); k++) {
                    if (word[k] != puzzle[i][j+k]) {
                        matched = 0;
                        break;
                    }                   
                }
                if (matched == 1) {
                    num++;                   
                    for (int k = 0; k < strlen(word); k++) {
                        dots[i][j+k] = word[k];
                    }
                }
            }
        }
    }
    return num;
                                   
}


int topToBottom(char **puzzle, char *word, int rows, int cols, char **dots) {
    int num = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (puzzle[i][j] == word[0] && (strlen(word) <= (rows - i))) {
                int matched = 1;
                for (int k = 0; k < strlen(word); k++) {
                    if (word[k] != puzzle[i+k][j]) {
                        matched = 0;
                        break;
                    }
                }
                if (matched == 1) {
                    num++;
                    for (int k = 0; k < strlen(word); k++) {
                        dots[i+k][j] = word[k];
                    }
                }
            }
        }
    }
    return num;
}



int bottomToTop(char **puzzle, char *word, int rows, int cols, char **dots) {
    int num = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((puzzle[i][j] == word[0]) && strlen(word) <= (i+1)) {
                int matched = 1;
                for (int k = 0; k < strlen(word); k++) {
                    if (word[k] != puzzle[i-k][j]) {
                        matched = 0;
                        break;
                    }
                }
                if (matched == 1) { 
                    num++;
                    for (int k = 0; k < strlen(word); k++) {
                        dots[i-k][j] = word[k];
                    }
                }
            }
        }
    }
    return num;
}


int rightToLeft(char **puzzle, char *word, int rows, int cols, char **dots) {
    int num = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((puzzle[i][j] == word[0]) && (strlen(word) <= (j+1))) {
                int matched = 1;
                for (int k = 0; k < strlen(word); k++) {
                    if (word[k] != puzzle[i][j-k]) {
                        matched = 0;
                        break;
                    }
                }
                if (matched == 1) {
                    num++;
                    for (int k = 0; k < strlen(word); k++) {
                        dots[i][j-k] = word[k];
                    }
                } 
            }
        }
    }
    return num;
}



void printDots(char** dots, char** puzzle, char* word, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", dots[i][j]);
        }
    printf("\n");
    }
    printf("\n");
}



void freeSpace(char **puzzle, int rows, int cols) {
    for (int a = 0; a < rows; a++) free(puzzle[a]);
    free(puzzle);
}



int main(int argc, char**argv) {
    if (argc != 3) {
        printf("Error: wrong number of arguments\n");
        return 1;
    }
    FILE *fp;
    fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("Unable to open the file %s\n", argv[2]);
        return 2;
    }
    

    int rows = atoi(argv[1]);
    int cols = atoi(argv[1]);
    char **z = allocateSpace(rows, cols);
    char **dots = allocateSpace(rows, cols);
    int numLR = 0;
    int numTB = 0;
    int numBT = 0;
    int numRL = 0;
    int total = 0;
 
    scanPuzzle(argc, argv, fp, z, rows, cols);    

    printf("The word puzzle is:\n");
    printPuzzle(z, rows, cols);
    printf("\n");
    
    char word[rows + 1];
    printf("Enter a word to find in the puzzle: ");
    scanf(" %s", word);
    printf("\n");
    while (strcmp(word, "zzz") != 0) {

        //initialize 2d array to dots
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                dots[i][j] = '.';
            }
        }       
    
    
        numLR = leftToRight(z, word, rows, cols, dots);    
 
        numTB = topToBottom(z, word, rows, cols, dots);
    
        numBT = bottomToTop(z, word, rows, cols, dots);
    
        numRL = rightToLeft(z, word, rows, cols, dots);
    
        total = numLR + numTB + numBT + numRL;
    
        printf("The word %s was found %d times, as shown below\n", word, total);    
        printf("%d times written left-to-right\n", numLR);
        printf("%d times written top-to-bottom\n", numTB);
        printf("%d times written bottom-to-top\n", numBT);
        printf("%d times written right-to-left\n", numRL);
        printf("\n");

        printDots(dots, z, word, rows, cols);
    
        printf("Enter another word to find (or 'zzz' to exit): ");
        scanf(" %s", word);
        printf("\n");
    }
    
    fclose(fp);
    freeSpace(z, rows, cols);
    freeSpace(dots, rows, cols);
    return 0;
}

