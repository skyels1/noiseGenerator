#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    int noiseMap[100][100];
    srand(time(NULL));

    for(int i = 0; i<100; i++) {
        for(int j = 0; j<100; j++) {

            if(rand() % 100 < 5) {
                noiseMap[i][j] = 3;
            }
            else if(rand() % 100 < 10) {
                noiseMap[i][j] = 2;
            }
            else {
                noiseMap[i][j] = 0;
            }
        }
    }




    //noiseMap[3][5] = 3;
/*
    int directions[8][2] = {
        {-1,-1},{-1,0},{-1,1},
        {0,-1},{0,1},
        {1,-1},{1,0},{1,1}
    };
    */
    int directions[4][2] = {
        {-1,0},
        {0,-1},{0,1},
        {1,0}
    };


    for(int i = 0; i<100; i++) {
        for(int j = 0; j<100; j++) {
            if(noiseMap[i][j] == 3) {
                for(int d = 0; d<4; d++) {
                    int Oi = i + directions[d][0];
                    int Oj = j + directions[d][1];
                    if(Oi >= 0 && Oi < 100 && Oj >= 0 && Oj <100) {
                        if(noiseMap[Oi][Oj] < 2) {
                            noiseMap[Oi][Oj] = 2;
                        }
                    }
        }
            }
        }
    }
    for(int i = 0; i<100; i++) {
        for(int j = 0; j<100; j++) {
            if(noiseMap[i][j] == 2) {
                for(int d = 0; d<4; d++) {
                    int Oi = i + directions[d][0];
                    int Oj = j + directions[d][1];
                    if(Oi >= 0 && Oi < 100 && Oj >= 0 && Oj <100) {
                        if(noiseMap[Oi][Oj] < 1) {
                            noiseMap[Oi][Oj] = 1;
                        }
                    }
        }
            }
        }
    }
    

    for(int i = 0; i<100; i++) {
        for(int j = 0; j<100; j++){
            printf("%i", noiseMap[i][j]);
        }
        printf("\n");
    }

    return 0;
}