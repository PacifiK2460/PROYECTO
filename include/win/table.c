#include "../win.h"

struct TABLE{
    int x, y;
    int columas, filas;
    //Bidimencional: texto mas largo por columna
    int* textoMasLargo;
    //Tridimencional: columna, fila y texto
    char*** data;
};

TABLE* newTable(int x, int y, int columnas, int filas, char*** data){
    TABLE* table = (struct TABLE*)calloc(1,sizeof(struct TABLE));
    table->columas = columnas;
    table->filas = filas;
    table->data = data;
    table->x = x;
    table->y = y;

    table->textoMasLargo = malloc(columnas * filas * sizeof(int));
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(len(data[i][j]) > table->textoMasLargo[j]) table->textoMasLargo[j] = len(data[i][j]);
        }
    }
    return table;
}

char*** prepareTableData(int fila, int columna){
    char*** data = malloc(fila * sizeof(char));
    for(int i = 0; i < fila; i++){
        data[i] = malloc(columna * sizeof(char*));
    }
    return data;
}

void setTableData(int fila, int columna, char*** dest, char* src){
    dest[fila][columna] = malloc(len(src) * sizeof(char));
    cp(dest[fila][columna], src);
}

void printTable(TABLE* table){
    int offset;
    for(int i = 0; i < table->filas; i++){
        for(int j = 0; j < table->columas; j++){
            if(j == 0) offset = 0;
            else offset = table->textoMasLargo[j];

            printf(
                RESET "%s"
                "\e[%i;%iH%*s"
                RESET,
                (i == 0 ? BRGB(16,158,94) FRGB(255,255,255) : NONE),
                table->y + i,table->x + offset +1 , offset,table->data[i][j]);
        }
    }
}