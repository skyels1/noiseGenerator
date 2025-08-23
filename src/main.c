#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define row 200
#define col 200
#define dir 8


int main() {
    int noiseMap[row][col];
    srand(time(NULL));

    int spawnSize = 20;
    int greyScale = 255/spawnSize;
    int iterations = 5;

    for(int i = 0; i<row; i++) {
        for(int j = 0; j<col; j++) {

            if(rand() % 1000 < 1) {
                noiseMap[i][j] = (rand() % spawnSize) + 1;
            }
            else {
                noiseMap[i][j] = 0;
            }
        }
    }

    int directions[dir][2] = {
        {-1,-1},{-1,0},{-1,1},
        {0,-1},{0,1},
        {1,-1},{1,0},{1,1}
    };
    
    /*int directions[dir][2] = {
        {-1,0},
        {0,-1},{0,1},
        {1,0}
    };*/

    

    while(iterations > 0) {
        for(int i = 0; i<row; i++) {
            for(int j = 0; j<col; j++) {
                if(noiseMap[i][j] > 0) {
                    for(int d = 0; d<dir; d++) {
                        int Oi = i + directions[d][0];
                        int Oj = j + directions[d][1];
                        if(Oi >= 0 && Oi < row && Oj >= 0 && Oj <col) {
                            if(noiseMap[Oi][Oj] < noiseMap[i][j]) {
                                if(rand() %100 < 10){
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
        for(int i = row-1; i>0; i--) {
            for(int j = col-1; j>0; j--) {
                if(noiseMap[i][j] > 0) {
                    for(int d = 0; d<dir; d++) {
                        int Oi = i + directions[d][0];
                        int Oj = j + directions[d][1];
                        if(Oi >= 0 && Oi < row && Oj >= 0 && Oj <col) {
                            if(noiseMap[Oi][Oj] < noiseMap[i][j]) {
                                if(rand() %100 < 10){
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
            int color = noiseMap[i][j] * greyScale;
            fprintf(f, "%d %d %d ", color, color, color);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("file wrote to noiseMap.ppm\n");

    FILE *f2 = fopen("noiseMapColor.ppm", "w");
    if (!f2) {
        perror("failed to write file");
        return 1;
    }

    fprintf(f2, "P3\n%d %d\n255\n", col, row);

    for(int i = 0; i<row; i++) {
        for(int j = 0; j<col; j++) {

            if(noiseMap[i][j] < spawnSize * 0.05) {
                fprintf(f2, "%d %d %d ", 5, 5, 25);// darker blue
            }
            else if(noiseMap[i][j] < spawnSize * 0.15) {
                fprintf(f2, "%d %d %d ", 10, 21, 80);// dark blue
            }
            else if(noiseMap[i][j] >= spawnSize * 0.15 && noiseMap[i][j] < spawnSize * 0.25) {
                fprintf(f2, "%d %d %d ", 12, 34, 148);// light blue
            }
            else if(noiseMap[i][j] >= spawnSize * 0.25 && noiseMap[i][j] < spawnSize * 0.35) {
                fprintf(f2, "%d %d %d ", 90, 240, 250);// lighter blue
            }
            else if(noiseMap[i][j] >= spawnSize * 0.35 && noiseMap[i][j] < spawnSize * 0.5) {
                fprintf(f2, "%d %d %d ", 55, 199, 74);// light green
            }
            else if(noiseMap[i][j] >= spawnSize * 0.5 && noiseMap[i][j] < spawnSize * 0.65) {
                
                fprintf(f2, "%d %d %d ", 18, 148, 35);// dark green
            }
            else if(noiseMap[i][j] >= spawnSize * 0.65 && noiseMap[i][j] < spawnSize * 0.85) {
                
                fprintf(f2, "%d %d %d ", 208, 163, 105);// light brown
            }
            else if(noiseMap[i][j] >= spawnSize * 0.85 && noiseMap[i][j] < spawnSize) {
                
                fprintf(f2, "%d %d %d ", 79, 80, 85);// gray
            }
            else {
                fprintf(f2, "%d %d %d ", 219, 219, 219);// white ish
            }
        }
        fprintf(f2, "\n");
    }

    fclose(f2);
    printf("file wrote to noiseMapColor.ppm\n");

    /* print to console
    for(int i = 0; i<row; i++) {
        for(int j = 0; j<col; j++){
            printf("%i", noiseMap[i][j]);
        }
        printf("\n");
    }
    */
    system("xdg-open noiseMap.ppm");
    system("start noiseMap.ppm");
    system("xdg-open noiseMapColor.ppm");
    system("start noiseMapColor.ppm");

    return 0;
}