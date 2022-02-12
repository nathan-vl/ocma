#include "acao.h"
#include "direcao.h"
#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>

void indoPescar(struct Mapa mapa, struct SituacaoJogo *situacaoJogo)
{
    if (posicaoEstaEmPosicoes(mapa.bots.posicao, mapa.bots.adversarios))
    {
        situacaoJogo->destino = melhorAreaPesca(mapa);
    }

    enum Direcao d = proximaDirecao(mapa, situacaoJogo->destino);
    outputDirecao(d);
    if (posicoesSaoIguais(addDirecao(mapa.bots.posicao, d), situacaoJogo->destino))
    {
        situacaoJogo->acao = PESCANDO;
    }
}

void pescando(struct Mapa mapa, struct SituacaoJogo *situacaoJogo)
{
    printf("FISH\n");
    situacaoJogo->capacidade += 1;

    char buffer[10];
    fgets(buffer, 10, stdin); // Tipo do peixe descartado

    if (situacaoJogo->capacidade >= 10)
    {
        situacaoJogo->destino = maisPerto(mapa.bots.posicao, mapa.portos);
        situacaoJogo->acao = INDO_VENDER;
    }
    else
    {
        struct Posicoes posicoesAreaPesca = {
            .posicoes = mapa.areasPesca.posicoes,
            .quantidade = mapa.areasPesca.quantidade};
        if (!posicaoEstaEmPosicoes(situacaoJogo->destino, posicoesAreaPesca))
        {
            situacaoJogo->destino = melhorAreaPesca(mapa);
            situacaoJogo->acao = INDO_PESCAR;
        }
    }
}

void indoVender(struct Mapa mapa, struct SituacaoJogo *situacaoJogo)
{
    enum Direcao d = proximaDirecao(mapa, situacaoJogo->destino);
    outputDirecao(d);
    if (posicoesSaoIguais(addDirecao(mapa.bots.posicao, d), situacaoJogo->destino))
    {
        situacaoJogo->acao = VENDENDO;
    }
}

void vendendo(struct Mapa mapa, struct SituacaoJogo *situacaoJogo)
{
    printf("SELL\n");

    char buffer[10];
    fgets(buffer, 10, stdin);
    // Valor descartado

    situacaoJogo->capacidade = 0;
    situacaoJogo->destino = melhorAreaPesca(mapa);
    situacaoJogo->acao = INDO_PESCAR;
}

void realizarAcao(struct Mapa *mapa, char *idBot, struct SituacaoJogo *situacaoJogo)
{
    mapa->areasPesca = lerAreasPesca(mapa->area);
    mapa->bots = lerBots(idBot);

    switch (situacaoJogo->acao)
    {
    case INDO_PESCAR:
        indoPescar(*mapa, situacaoJogo);
        break;
    case PESCANDO:
        pescando(*mapa, situacaoJogo);
        break;
    case INDO_VENDER:
        indoVender(*mapa, situacaoJogo);
        break;
    case VENDENDO:
        vendendo(*mapa, situacaoJogo);
        break;
    }

    free(mapa->areasPesca.posicoes);
    free(mapa->areasPesca.peixes);
    free(mapa->areasPesca.quantidadePeixes);
    if (mapa->bots.adversarios.quantidade >= 1)
    {
        free(mapa->bots.adversarios.posicoes);
    }
}