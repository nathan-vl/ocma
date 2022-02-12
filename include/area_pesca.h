#ifndef AREA_PESCA_H
#define AREA_PESCA_H

#include "peixe.h"
#include "posicao.h"

struct AreasPesca
{
    int quantidade;
    struct Posicao *posicoes;
    enum Peixe *peixes;
    int *quantidadePeixes;
};

struct AreasPesca alocarAreasPescaComBuffer(struct AreasPesca buffer);
int valorAreaPesca(struct Posicao atual, struct Posicao posicaoAreaPesca, enum Peixe peixe, int quantidade, struct Posicoes portos);
#endif
