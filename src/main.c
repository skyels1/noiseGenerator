#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define row 400
#define col 400
#define dir 8


int main() {
    int noiseMap[row][col];
    srand(time(NULL));

    int spawnSize = 20;
    int greyScale = 255/spawnSize;
    int iterations = 30;

    // populate the array with starters, and later loop to grow them
    for(int i = 0; i<row; i++) {
        for(int j = 0; j<col; j++) {

            if(rand() % 5000 < 1) {
                noiseMap[i][j] = (rand() % spawnSize) + 1;
            }
            else {
                noiseMap[i][j] = 0;
            }
        }
    }

    // box style all sides and corners
    int directions[dir][2] = {
        {-1,-1},{-1,0},{-1,1},
        {0,-1},{0,1},
        {1,-1},{1,0},{1,1}
    };

    // this is the directions not including corners more like star
    /*int directions[dir][2] = {
        {-1,0},
        {0,-1},{0,1},
        {1,0}
    };*/

    
// this is the main update for the map generation, it will loop through the array
// this is main because it goes top to bottom
    while(iterations > 0) {
        for(int i = 0; i<row; i++) {
            for(int j = 0; j<col; j++) {
                if(noiseMap[i][j] > 0) {
                    for(int d = 0; d<dir; d++) {
                        // map tiling, can have the map go from the sides and match the other side
                        // kind of cool but i prefer normal for now
                        //int Oi = (i + directions[d][0] + row) % row;// for tile
                        //int Oj = (j + directions[d][1] + col) % col;
                        int Oi = i + directions[d][0];// for non tile
                        int Oj = j + directions[d][1];
                        if(Oi >= 0 && Oi < row && Oj >= 0 && Oj <col) {
                            if(noiseMap[Oi][Oj] < noiseMap[i][j]) {
                                if(rand() %200 < 10){
                                    noiseMap[Oi][Oj] = noiseMap[i][j];
                                }
                                else {
                                noiseMap[Oi][Oj] = noiseMap[i][j] - 1;
                                }   
                            }
                            // added to change if you want to make it 
                            // so that the mountains are not as circular
                            // will force them to be more smooth
                            // both this and for reverse update
                            if(noiseMap[i][j] > 10) {
                                if(noiseMap[Oi][Oj] < noiseMap[i][j]) {
                                    if(rand() %300 < 10){
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
        }
        // secondary loop for map generation, starts at the bottom and goes up
        // only implemented to help deal with the weird bug that makes it so that
        // the map will look like its bleeding down from top to bottom if this isnt here
        for(int i = row-1; i>=0; i--) {
            for(int j = col-1; j>=0; j--) {
                if(noiseMap[i][j] > 0) {
                    for(int d = 0; d<dir; d++) {
                        // this is for tiling of the map both this and main
                        //int Oi = (i + directions[d][0] + row) % row;// for tile
                        //int Oj = (j + directions[d][1] + col) % col;
                        int Oi = i + directions[d][0];// for non tile
                        int Oj = j + directions[d][1];
                        if(Oi >= 0 && Oi < row && Oj >= 0 && Oj <col) {
                            if(noiseMap[Oi][Oj] == 0) {
                                if(rand() %200 < 10){
                                    noiseMap[Oi][Oj] = noiseMap[i][j];
                                }
                                else {
                                noiseMap[Oi][Oj] = noiseMap[i][j] - 1;
                                }   
                            }
                            if(noiseMap[i][j] > 10) {
                                if(noiseMap[Oi][Oj] < noiseMap[i][j]) {
                                    if(rand() %300 < 10){
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
        }
        // this is to try and get rid of the huge oceans or blank space that appears 
        // it just loops through the array and if its low enough number give it a chance to be bigger
        if(iterations > 29) {
            for(int i = 0; i<row; i++) {
                for(int j = 0; j<col; j++) {
                    if(noiseMap[i][j] == 0) {
                        if(rand() % 1000 < 1) {
                            noiseMap[i][j] = (rand() % 5) + 1;
                            }
                        }
                    if(noiseMap[i][j] == 1) {
                        if(rand() % 2000 < 1) {
                            noiseMap[i][j] = (rand() % 10) + 1;
                            }
                        }
                    if(noiseMap[i][j] == 2) {
                        if(rand() % 3000 < 1) {
                            noiseMap[i][j] = (rand() % 15) + 1;
                            }
                        }
                    if(noiseMap[i][j] == 3) {
                        if(rand() % 4000 < 1) {
                            noiseMap[i][j] = (rand() % 20) + 1;
                            }
                        }

                    if(noiseMap[i][j] == 0) {
                        if(rand() % 5000 < 1) {
                            noiseMap[i][j] = (rand() % 20) + 1;
                            }
                        }
                    }
                 }
            }
        iterations--;
    }
    

    // write to file
    // two files are being written to, one is for the noise, just gray scale
    // and the other is colored, not very detailed but its enough for me

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
            else if(noiseMap[i][j] >= spawnSize * 0.65 && noiseMap[i][j] < spawnSize * 0.8) {
                
                fprintf(f2, "%d %d %d ", 208, 163, 105);// light brown
            }
            else if(noiseMap[i][j] >= spawnSize * 0.8 && noiseMap[i][j] < spawnSize) {
                
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

    // open the viewing application for both windows and linux after running
    // just nice so i dont have to keep opening the files every time i change something and want to see it
    system("xdg-open noiseMap.ppm");
    system("start noiseMap.ppm");
    system("xdg-open noiseMapColor.ppm");
    system("start noiseMapColor.ppm");

    return 0;
}