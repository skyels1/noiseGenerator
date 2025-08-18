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

    for(int i = 0; i<10; i++) {
        for(int j = 0; j<10; j++) {
            if(noiseMap[i][j] == 3) {
                //if() {
                    noiseMap[i-1][j-1] = 2;
                    noiseMap[i+1][j+1] = 2;
                    noiseMap[i-1][j+1] = 2;
                    noiseMap[i+1][j-1] = 2;
                    noiseMap[i+1][j] = 2;
                    noiseMap[i-1][j] = 2;
                    noiseMap[i][j+1] = 2;
                    noiseMap[i][j-1] = 2;
                //
            }
        }
    }
    for(int i = 0; i<10; i++) {
        for(int j = 0; j<10; j++) {
            if(noiseMap[i][j] == 2) {
                //if() {
                    noiseMap[i-1][j-1] = 1;
                    noiseMap[i+1][j+1] = 1;
                    noiseMap[i-1][j+1] = 1;
                    noiseMap[i+1][j-1] = 1;
                    noiseMap[i+1][j] = 1;
                    noiseMap[i-1][j] = 1;
                    noiseMap[i][j+1] = 1;
                    noiseMap[i][j-1] = 1;
                //}
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