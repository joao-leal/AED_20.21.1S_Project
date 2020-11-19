#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void variantec0 (double **matriz, FILE* fp2, int rota, int vertice1, int aero, FILE* fp1);

void variantea0 (double **matriz, FILE* fp2, int rota, int vertice1, int aero, FILE* fp1);

int main(int argc,char *argv[]) {

    double **matriz;
    int aero, rota, vertice1, /*vertice2,*/ i, j, iteracao = 0;
    char variante[5], saida[100];

    FILE* fp1;
    fp1= fopen(argv[1], "r");

        strncpy(saida, argv[1], strlen(argv[1])-7);
        saida[strlen(argv[1])-strlen(".routes0")] = '\0';
        strcat(saida, ".bbones");


    FILE* fp2;
    fp2= fopen(saida, "a");

    if(fp1 == NULL){
        exit(0);
    }


    do {
        if(fscanf(fp1, "%d %d %s %d", &aero, &rota, &*variante, &vertice1) == 4 ){
            if((strcmp(variante, "A0") == 0) || (strcmp(variante, "C0") == 0) || (strcmp(variante, "D0") == 0)){
                matriz = (double**) malloc(sizeof(double*)*rota);
                for (i = 0; i < rota; i++) {
                    matriz[i] = (double*) malloc(sizeof(double)*3);
                }
                for (i = 0; i < rota; i++) {
                    for (j = 0; j < 3; j++) {
                        if(fscanf(fp1, "%lf", &matriz[i][j]) != 1) {
                            exit (0);
                        }

                    }

                }

                if(iteracao != 0){

                    fprintf(fp2, "\n");
                }

                if(strcmp(variante, "A0") == 0){

                    variantea0 (matriz, fp2, rota, vertice1, aero, fp1);
                }

                if(strcmp(variante, "C0") == 0){

                    variantec0 (matriz, fp2, rota, vertice1, aero, fp1);

                }

                for(i=0; i < rota; i++){
                    free(matriz[i]);
                }

                free(matriz);

            }

        }

        iteracao++;

    } while(feof(fp1) == 0);


    fclose(fp1);
    fclose(fp2);

    return 0;
}


void variantea0 (double **matriz, FILE* fp2, int rota, int vertice1, int aero, FILE* fp1){

    int counter = 0;
    int i, j;

    for (i = 0; i < rota; i++) {
        for (j = 0; j < 2; j++) {

            if (matriz[i][j] ==  vertice1) {
                counter++;

            }
        }
    }

    fprintf(fp2, "%d %d A0 %d %d \n", aero, rota, vertice1, counter);
    return;
}


void variantec0 (double **matriz, FILE* fp2, int rota, int vertice1, int aero, FILE* fp1){

    int i, j, pvector = 0, counter = 0, pvector2, n;
    double vector[aero];

    for(i = 0; i < rota; i++){
        for(j = 0; j < 2; j++){

            if (matriz[i][j] == vertice1) {

                    counter++;

                    if (j == 1) {
                        vector[pvector] = matriz[i][0];
                        pvector++;
                    }

                    else{

                        vector[pvector] = matriz[i][1];
                        pvector++;
                    }

                }

            }

        }

    if(pvector == 0){

        fprintf(fp2, "%d %d C0 %d -1 \n", aero, rota, vertice1);

        return;
    }



    for (pvector2 = 0; pvector2 <= pvector; pvector2++) {
        for(i = 0; i < rota; i++){
            for(j = 0; j < 2; j++){
                if(matriz[i][j] == vector[pvector2]){
                    for(n = 0; n <= pvector; n++){
                        if (j == 0 && matriz[i][1] == vector[n]) {

                            fprintf(fp2, "%d %d C0 %d 1 \n", aero, rota, vertice1);

                            return;
                        }

                        else if(j == 1 && matriz[i][0] == vector[n]){

                            fprintf(fp2, "%d %d C0 %d 1 \n", aero, rota, vertice1);

                            return;

                        }

                    }

                }

            }

        }

    }

    fprintf(fp2, "%d %d C0 %d 0 \n", aero, rota, vertice1);

    return;
}
