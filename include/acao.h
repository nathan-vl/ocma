#ifndef ACAO_H
#define ACAO_H

#include "mapa.h"
#include "posicao.h"

enum Acao
{
    INDO_PESCAR,
    PESCANDO,
    INDO_VENDER,
    VENDENDO
};

struct SituacaoJogo
{
    int capacidade;
    struct Posicao destino;
    enum Acao acao;
};

void realizarAcao(struct Mapa *mapa, char *idBot, struct SituacaoJogo *situacaoJogo);

#endif
