#include <stdio.h>

int main() {
    int noiseMap[10][10] = {
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0
    };

    noiseMap[3][5] = 3;

    int directions[8][2] = {
        {-1,-1},{-1,0},{-1,1},
        {0,-1},{0,1},
        {1,-1},{1,0},{1,1}
    };


    for(int i = 0; i<10; i++) {
        for(int j = 0; j<10; j++) {
            if(noiseMap[i][j] == 3) {
                for(int d = 0; d<8; d++) {
                    int Oi = i + directions[d][0];
                    int Oj = j + directions[d][1];
                    if(Oi >= 0 && Oi <= 10 && Oj >= 0 && Oj <=10) {
                        if(noiseMap[Oi][Oj] < 2) {
                            noiseMap[Oi][Oj] = 2;
                        }
                    }
        }
            }
        }
    }
    for(int i = 0; i<10; i++) {
        for(int j = 0; j<10; j++) {
            if(noiseMap[i][j] == 2) {
                for(int d = 0; d<8; d++) {
                    int Oi = i + directions[d][0];
                    int Oj = j + directions[d][1];
                    if(Oi >= 0 && Oi <= 10 && Oj >= 0 && Oj <=10) {
                        if(noiseMap[Oi][Oj] < 1) {
                            noiseMap[Oi][Oj] = 1;
                        }
                    }
        }
            }
        }
    }
    

    for(int i = 0; i<10; i++) {
        for(int j = 0; j<10; j++){
            printf("%i", noiseMap[i][j]);
        }
        printf("\n");
    }

    return 0;
}