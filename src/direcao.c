#include "direcao.h"
#include "mapa.h"
#include "posicao.h"
#include <stdio.h>
#include <stdlib.h>

const char *direcaoStr(enum Direcao direcao)
{
    const char *direcoes[] = {"UP", "RIGHT", "DOWN", "LEFT"};
    return direcoes[direcao];
}

enum ResultadoDirecao outputDirecao(enum Direcao direcao)
{
    printf("%s\n", direcaoStr(direcao));

    char buffer[5];
    fgets(buffer, 5, stdin);
    switch (buffer[0])
    {
    case 'D':
        return DONE;
    case 'B':
        return BUSY;
    }
    return OUT;
}

struct Posicao addDirecao(struct Posicao posicao, enum Direcao direcao)
{
    struct Posicao destino = posicao;
    switch (direcao)
    {
    case LEFT:
        destino.largura -= 1;
        break;
    case RIGHT:
        destino.largura += 1;
        break;
    case UP:
        destino.altura -= 1;
        break;
    case DOWN:
        destino.altura += 1;
        break;
    }
    return destino;
}

/*
Só pode andar se estiver dentro dos limites
e, se for um porto ou se não tiver bot
*/
_Bool podeAndarEmDirecao(struct Mapa mapa, enum Direcao direcao)
{
    const struct Posicao destino = addDirecao(mapa.bots.posicao, direcao);

    return dentroMapa(mapa.area, destino) && (posicaoEstaEmPosicoes(destino, mapa.portos) || !posicaoEstaEmPosicoes(destino, mapa.bots.adversarios));
}

enum Direcao calcularProximaDirecao(struct Mapa mapa, struct Posicao destino)
{
    int dInicial = calcDistanciaSimples(mapa.bots.posicao, destino);
    for (enum Direcao d = 0; d < 4; ++d)
    {
        if (podeAndarEmDirecao(mapa, d) && (calcDistanciaSimples(addDirecao(mapa.bots.posicao, d), destino) <= dInicial))
        {
            return d;
        }
    }

    for (enum Direcao d = 0; d < 4; ++d)
    {
        if (podeAndarEmDirecao(mapa, d))
        {
            return d;
        }
    }
    return UP;
}
