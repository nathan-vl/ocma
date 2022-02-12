#ifndef AREA_PESCA_H
#define AREA_PESCA_H

#include "peixe.h"
#include "posicao.h"

struct AreaPesca
{
    struct Posicao posicao;
    enum Peixe peixe;
    int quantidade;
};

struct AreasPesca
{
    int quantidade;
    struct AreaPesca *areas;
};

struct AreaPesca parseAreaPesca(struct Posicao p, int v);
struct AreasPesca alocarAreasPescaComBuffer(struct AreasPesca buffer);
int valorAreaPesca(struct Posicao atual, struct AreaPesca areaPesca, struct Posicoes portos);

#endif
