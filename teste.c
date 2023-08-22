/*
//
// Created by luann on 21/08/2023.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *pt;

//FILE *dataFile = fopen(arquivo, "r");

void lerArquivo(){

    unsigned int mem, valor;
    FILE *arq;
    unsigned char tipo, linha[99];
    unsigned int count = 0;
    arq = fopen("ifg.md", "r");

    while (fgets(linha, 99, arq) != NULL){
        pt = strtok(linha, " ");
        mem = (int)strtol(pt,NULL,16);

            pt = strtok(NULL ,";");
            count++;
        }
        count = 0;
    }

    if (NULL == arq)
        printf("Erro ao tentar abrir programa.txt \n");
    fclose(arq);
}*/
