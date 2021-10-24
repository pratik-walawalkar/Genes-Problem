#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "input_problem_1.txt"

#define MAXROWS 100
#define MAXCOLS 100
#define MAXWORDS 10

char grid[MAXROWS][MAXCOLS];
char listOfCondons[MAXWORDS][MAXCOLS];
char codonsStart[] = "AUG";
char codonsEnd[MAXROWS][MAXCOLS] = {"UAA", "UAG", "UGA"};

int x[4] = {-1, 0, 1, 0};
int y[4] = {0, 1, 0, -1};

int startCodon(char word[]){
    int count = 0;
    for(int i=0; i<3; i++){
        
        if(word[i] == codonsStart[i]){
            count++;
        }
    }
    if(count==3){
        //printf("word: %s| start: %s ", word, codonsStart);
        return true;
    }
    return false;

}

int codonEnd(char word[]){



    for(int n=0; n<3; n++){
            int count = 0;
        //printf("%s", codonsEnd[n]);
        for(int i=0; i<3; i++){
            //printf("compare %c -> %c", codonsEnd[n][i], word[i]);
            if(codonsEnd[n][i] == word[i]){
                count++;
            }
        }
        if(count==3){
            // printf("word: %s| end: %s ", word, codonsEnd[n]);
            return true;
        }
    }
    return false;
}

int findCodons(char *codon, char grid[MAXROWS][MAXCOLS], int r, int c, int row, int col, int dir)
{

    int count=0, n=0, state=0, key=0;
    bool repeat=true;
    int codons_in_sequence=0, maxCodons=0;

    //char word[3];

    while(repeat==true){
        int rd = r + n*x[dir];
        int cd = c + n*y[dir];
        //printf("rd:%d cd:%d row:%d col:%d ", rd,cd, row, col);
        // printf("compare %c -> %c (%d,%d)| ", grid[rd][cd], codonsStart[n], rd, cd);
        if (rd >= row || rd < 0 || cd >= col || cd < 0){
            repeat = false;
            break;
        }
        else{
            codon[key] = grid[rd][cd];
            count++;
        }
        key++;
        n++;

        if(count%3 == 0 && count != 0){
            //printf("count is 3 and word is %s\n", codon);
            
            if(startCodon(codon) == true && (state==0 || state==3)){
                //printf("State 1: Codon start at (%d, %d) in dir=%d - %s\n", rd, cd, dir, codon); // Print the coordinate of codon start
                state = 2;
                n+2;
                codons_in_sequence++;
            }

            else if(codonEnd(codon) == true || state==2){

                if (codonEnd(codon) == true){
                    //printf("State 3: Codon end at (%d, %d) in dir=%d - %s\n", rd, cd, dir, codon); // Print the coordinate of codon end
                    state = 3;
                    codons_in_sequence++;
                    //printf("Maximum number of codons: %d\n", codons_in_sequence);
                }
                else{
                    for (int i = 0; i < 64; i++) {
                        int codonMatch = 0;
                        for (int j = 0; j < 3; j++) {
                            if (listOfCondons[i][j]==codon[j]){
                                codonMatch++;
                            }
                        }
                        if(codonMatch==3){
                            //printf("Codon Match! - %s & %s ", listOfCondons[i], codon);
                            state = 2;
                            codons_in_sequence++;
                        }
                        state = 0;
                    }
                }
            }
            else{
                state = 0;
            }
            
            key = 0;
        }
        if(codons_in_sequence>maxCodons){
            
            maxCodons=codons_in_sequence;
        }
        
    }

    return maxCodons;
}


int patternSearch(char grid[MAXROWS][MAXCOLS], int row, int col)
{
    int count=0, maxCodons, codons_in_sequence;
    char codon[3];
    int r=0, c=0;
    // Consider every point as starting
    // point and search given word
    // printf("%c", grid[row-1][col-1]); // for debugging purpose
    for (int r = 0; r < row; r++){
        for (int c = 0; c < col; c++){
            int state=0;
            for(int dir=0; dir<4; dir++){

                codons_in_sequence = findCodons(codon, grid, r, c, row, col, dir);
                if(codons_in_sequence>maxCodons){
                    maxCodons=codons_in_sequence;
                } 
                // printf("codon: %s\n", codon);
                /*
                if(startCodon(codon) == true){
                    printf("Codon start at (%d, %d)\n", r, c); // Print the coordinate of codon start
                    state = 1;
                    printf("state 1 ");
                    break;
                }
                else if(state==1 || state==2){
                    state = 2;
                    break;
                }
                else if(codonEnd(codon) == true){
                    printf("Codon end at (%d, %d)\n", r, c); // Print the coordinate of codon end
                    state = 3;
                    printf("state 3 ");
                    break;
                }
                else{
                    state = 0;
                }
                */
                //printf("next col ");
                //printf("temp = %d\n", temp);  // for debugging purpose

                // count += temp;  
                //printf("count = %d\n", count); // for debugging purpose
            }
        }   
        //printf("next row ");

    } 
    return maxCodons;
}


int main()
{
    FILE *scores;
    int testi, maxCodons;

    freopen("codons.txt", "r", stdin);
    int noCondons;

    scanf("%d", &noCondons);

    for (int i = 0; i < noCondons; i++) {
        for (int j = 0; j < 3; j++) {
            scanf(" %c", &listOfCondons[i][j]); // Note: there should be a space before %c to skip spaces and newlines
        }
    }
    // printf("%c", codonsStart[0]);
    /*// Print Codons list
    for (int i = 0; i < noCondons; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c", listOfCondons[i][j]); // Note: there should be a space before %c to skip spaces and newlines
        }
        printf("\n");
    }
    */

	freopen("input_problem_3.txt", "r", stdin);
    int numTestCases, row, col;

// 1. Input number of test cases
	scanf("%d", &numTestCases);

// 2. Input number of rows
	for (testi = 0; testi < numTestCases; testi++) {
		scanf("%d %d", &row, &col);  

// 3. Iterate to input the grid
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				scanf(" %c", &grid[i][j]); // Note: there should be a space before %c to skip spaces and newlines
			}
		}
        /*
        printf("%d \n", numTestCases);
        printf("%d %d\n", row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                printf("%c", grid[i][j]); 
            }
            printf("\n");
        }
        */
        maxCodons = patternSearch(grid, row, col);
        printf("Test case %d: Maximum number of codons: %d", testi, maxCodons);
        printf("\n");
        //printf("Maximum number of codons: %d ", count);
    }
}