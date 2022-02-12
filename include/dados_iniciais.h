#ifndef DADOS_INICIAIS_H
#define DADOS_INICIAIS_H

#include "posicao.h"
#include <stdio.h>

struct Posicao lerTamanhoMapa(void)
{
    struct Posicao tamanho;

    char buffer[50];
    fgets(buffer, 50, stdin);
    sscanf(buffer, "AREA %i %i",
           &tamanho.altura, &tamanho.largura);

    return tamanho;
}

void lerIdBot(char *destino)
{
    char buffer[15];
    fgets(buffer, 15, stdin);
    sscanf(buffer, "ID %s", destino);
}

#endif
