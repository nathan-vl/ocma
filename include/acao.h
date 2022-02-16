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

struct MeuBot
{
    int dinheiro;
    int quantidadeCioba;
    int quantidadeRobalo;
    int quantidadeTainha;
    struct Posicao destino;
    enum Acao acao;
};

void realizarAcao(struct Mapa *mapa, char *idBot, struct MeuBot *meuBot);

#endif
