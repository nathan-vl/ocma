#ifndef DIRECAO_H
#define DIRECAO_H

#include "mapa.h"
#include "posicao.h"
#include <stdio.h>

enum ResultadoDirecao
{
    DONE,
    BUSY,
    OUT
};

enum Direcao
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum ResultadoDirecao outputDirecao(enum Direcao direcao);
struct Posicao addDirecao(struct Posicao posicao, enum Direcao direcao);
_Bool podeAndarEmDirecao(struct Mapa mapa, enum Direcao direcao);
enum Direcao proximaDirecao(struct Mapa mapa, struct Posicao destino);

#endif
