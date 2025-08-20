#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define row 200
#define col 200
#define dir 4


int main() {
    int noiseMap[row][col];
    srand(time(NULL));

    for(int i = 0; i<row; i++) {
        for(int j = 0; j<col; j++) {

            if(rand() % 100 < 1) {
                noiseMap[i][j] = (rand() % 20) + 1;
            }
            else {
                noiseMap[i][j] = 0;
            }
        }
    }

    //noiseMap[3][5] = 3;

    /*int directions[dir][2] = {
        {-1,-1},{-1,0},{-1,1},
        {0,-1},{0,1},
        {1,-1},{1,0},{1,1}
    };*/
    
    int directions[dir][2] = {
        {-1,0},
        {0,-1},{0,1},
        {1,0}
    };

    int iterations = 100;

    while(iterations > 0) {
        for(int i = 0; i<row; i++) {
            for(int j = 0; j<col; j++) {
                if(noiseMap[i][j] > 0) {
                    for(int d = 0; d<dir; d++) {
                        int Oi = i + directions[d][0];
                        int Oj = j + directions[d][1];
                        if(Oi >= 0 && Oi < row && Oj >= 0 && Oj <col) {
                            if(noiseMap[Oi][Oj] < noiseMap[i][j]) {
                                if(rand() %100 < 1){
                                    noiseMap[Oi][Oj] = noiseMap[i][j];
                                }
                                else {
                                noiseMap[Oi][Oj] = noiseMap[i][j] - 1;
                                }   
                            }  
                        }
                    }
                }
            }
        }
        iterations--;
    }

    // write to file

    FILE *f = fopen("noiseMap.ppm", "w");
    if (!f) {
        perror("failed to write file");
        return 1;
    }

    fprintf(f, "P3\n%d %d\n255\n", col, row);

    for(int i = 0; i<row; i++) {
        for(int j = 0; j<col; j++) {
            int color = noiseMap[i][j] * 12;
            fprintf(f, "%d %d %d ", color, color, color);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("file wrote to noiseMap.ppm\n");

    /* print to console
    for(int i = 0; i<row; i++) {
        for(int j = 0; j<col; j++){
            printf("%i", noiseMap[i][j]);
        }
        printf("\n");
    }
    */

    return 0;
}