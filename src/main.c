#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

 /*favorite seed
#define row 400
#define col 400
#define dir 8
#define spawnSize 20
#define spawnChance 20000
#define spreadChance 20
#define spreadChanceGrow 1000
#define elevationSpread 20
// iterations set to 30 and 27 */

// /*with higher quality
#define row 1000
#define col 1000
#define dir 8
#define spawnSize 20
#define spawnChance RAND_MAX
#define spreadChance 30
#define spreadSetBack 1
#define spreadChanceGrow 2500
#define elevationSpread 20
// iterations set to 30 and 27 */


int main() {
    static uint8_t noiseMap[row][col];

    srand(time(NULL));

    int iterations = 30;
    int iterationLoop = 27;
    int greyScale = 255/spawnSize;

    // populate the array with starters, and later loop to grow them
    for(int i = 0; i<row; i++) {
        for(int j = 0; j<col; j++) {

            if(rand() % spawnChance < 1) {
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
                        // change the likely hood of the seed spreading to get less "islands"
                        if(rand() %spreadSetBack == 0) {
                            // map tiling, can have the map go from the sides and match the other side
                            // kind of cool but i prefer normal for now
                            //int Oi = (i + directions[d][0] + row) % row;// for tile
                            //int Oj = (j + directions[d][1] + col) % col;
                            int Oi = i + directions[d][0];// for non tile
                            int Oj = j + directions[d][1];
                            if(Oi >= 0 && Oi < row && Oj >= 0 && Oj <col) {
                                if(noiseMap[Oi][Oj] < noiseMap[i][j]) {
                                    if(rand() %spreadChance < 1){
                                        noiseMap[Oi][Oj] = noiseMap[i][j];
                                    }
                                    // to add a chance to grow the seed positive rather than negative without going over the cap
                                    else if(rand() %spreadChanceGrow < 1 && noiseMap[i][j] <(spawnSize-1)){
                                        noiseMap[Oi][Oj] = noiseMap[i][j] + 1;
                                    }
                                    else {
                                    noiseMap[Oi][Oj] = noiseMap[i][j] - 1;
                                    } 
                                }
                                // added to change if you want to make it 
                                // so that the mountains are not as circular
                                // will force them to be more smooth
                                // both this and for reverse update
                                if(noiseMap[i][j] > (spawnSize*0.5) && noiseMap[i][j] <= (spawnSize*0.85)) {
                                    if(noiseMap[Oi][Oj] < noiseMap[i][j]) {
                                        if(rand() %elevationSpread < 1){
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
        }
        // secondary loop for map generation, starts at the bottom and goes up
        // only implemented to help deal with the weird bug that makes it so that
        // the map will look like its bleeding down from top to bottom if this isnt here
        for(int i = row-1; i>=0; i--) {
            for(int j = col-1; j>=0; j--) {
                if(noiseMap[i][j] > 0) {
                    for(int d = 0; d<dir; d++) {
                        // less islands spawn from this check to lower the amount of spreading
                        if(rand() %spreadSetBack < 1) {
                            // this is for tiling of the map both this and main
                            //int Oi = (i + directions[d][0] + row) % row;// for tile
                            //int Oj = (j + directions[d][1] + col) % col;
                            int Oi = i + directions[d][0];// for non tile
                            int Oj = j + directions[d][1];
                            if(Oi >= 0 && Oi < row && Oj >= 0 && Oj <col) {
                                if(noiseMap[Oi][Oj] < noiseMap[i][j]) {
                                    if(rand() %spreadChance < 1){
                                        noiseMap[Oi][Oj] = noiseMap[i][j];
                                    }
                                    // to add a chance to grow the seed positive rather than negative
                                    else if(rand() %spreadChanceGrow < 1 && noiseMap[i][j] <(spawnSize-1)){
                                        noiseMap[Oi][Oj] = noiseMap[i][j] + 1;
                                    }
                                    else {
                                    noiseMap[Oi][Oj] = noiseMap[i][j] - 1;
                                    }
                                }
                                // check if its higher and give it more chance to spread
                                if(noiseMap[i][j] > (spawnSize*0.5) && noiseMap[i][j] <= (spawnSize*0.85)) {
                                    if(noiseMap[Oi][Oj] < noiseMap[i][j]) {
                                        if(rand() %elevationSpread < 1){
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
        }
        // this is to try and get rid of the huge oceans or blank space that appears 
        // it just loops through the array and if its low enough number give it a chance to be bigger
        if(iterations > iterationLoop) {
            for(int i = 0; i<row; i++) {
                for(int j = 0; j<col; j++) {
                    if(noiseMap[i][j] == 0) {
                        if(rand() % 750 < 1) {
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
                        // extra step for when map has a 0
                        // since i like the look of very shallow parts of the water
                        // this allows more large mountains in 0 and shallow
                        // both with their own chances
                    if(noiseMap[i][j] == 0) {
                        if(rand() % 7000 < 1) {
                            noiseMap[i][j] = (rand() % 20) + 1;
                            }
                        }
                        // added chance to spawn in water on higher elevations
                    if(noiseMap[i][j] >= 15 && noiseMap[i][j] <= 20) {
                        if(rand() % 3000 < 1) {
                            noiseMap[i][j] = 0;
                            }
                        }
                    }
                 }
            }
        iterations--;
    }

    // smoothing
    for(int i = 1; i < row - 1; i++) {
        for(int j = 1; j < col -1; j++) {
            int sum = 
            noiseMap[i][j] + 
            noiseMap[i + 1][j + 1] + noiseMap[i - 1][j - 1] +
            noiseMap[i - 1][j + 1] + noiseMap[i + 1][j - 1] + 
            noiseMap[i + 1][j] + noiseMap[i - 1][j] + 
            noiseMap[i][j + 1] + noiseMap[i][j - 1];
            
            noiseMap[i][j] = sum / 9;
        }
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
                fprintf(f2, "%d %d %d ", 208, 163, 105);// light brown
            }
            else if(noiseMap[i][j] >= spawnSize * 0.5 && noiseMap[i][j] < spawnSize * 0.65) {
                fprintf(f2, "%d %d %d ", 55, 199, 74);// light green
            }
            else if(noiseMap[i][j] >= spawnSize * 0.65 && noiseMap[i][j] < spawnSize * 0.85) {
                fprintf(f2, "%d %d %d ", 18, 148, 35);// dark green
            }
            else if(noiseMap[i][j] >= spawnSize * 0.85 && noiseMap[i][j] < spawnSize * 0.99) {
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