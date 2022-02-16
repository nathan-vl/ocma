#include "acao.h"
#include "direcao.h"
#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>

void indoPescar(struct Mapa mapa, struct MeuBot *meuBot)
{
    if (posicaoEstaEmPosicoes(meuBot->destino, mapa.bots.adversarios))
    {
        meuBot->destino = melhorAreaPesca(mapa);
    }

    enum Direcao d = calcularProximaDirecao(mapa, meuBot->destino);
    outputDirecao(d);
    if (posicoesSaoIguais(addDirecao(mapa.bots.posicao, d), meuBot->destino))
    {
        meuBot->acao = PESCANDO;
    }
}

void pescando(struct Mapa mapa, struct MeuBot *meuBot)
{
    printf("FISH\n");

    char buffer[10];
    fgets(buffer, 10, stdin);
    switch (buffer[1])
    {
    case 'N':
        meuBot->quantidadeCioba += 1;
        break;
    case 'E':
        meuBot->quantidadeRobalo += 1;
        break;
    case 'U':
        meuBot->quantidadeTainha += 1;
    }

    int capacidadeAtual = meuBot->quantidadeCioba + meuBot->quantidadeRobalo + meuBot->quantidadeTainha;
    int valorBruto = meuBot->dinheiro + meuBot->quantidadeCioba * 150 + meuBot->quantidadeRobalo * 200 + meuBot->quantidadeTainha * 100;
    if (capacidadeAtual >= 10 || valorBruto >= 10000)
    {
        meuBot->destino = maisPerto(mapa.bots.posicao, mapa.portos);
        meuBot->acao = INDO_VENDER;
        return;
    }

    struct Posicoes posicoesAreaPesca = {
        .posicoes = mapa.areasPesca.posicoes,
        .quantidade = mapa.areasPesca.quantidade};
    if (!posicaoEstaEmPosicoes(meuBot->destino, posicoesAreaPesca))
    {
        meuBot->destino = melhorAreaPesca(mapa);
        meuBot->acao = INDO_PESCAR;
    }
}

void indoVender(struct Mapa mapa, struct MeuBot *meuBot)
{
    enum Direcao d = calcularProximaDirecao(mapa, meuBot->destino);
    outputDirecao(d);
    if (posicoesSaoIguais(addDirecao(mapa.bots.posicao, d), meuBot->destino))
    {
        meuBot->acao = VENDENDO;
    }
}

void vendendo(struct Mapa mapa, struct MeuBot *meuBot)
{
    printf("SELL\n");

    char buffer[10];
    fgets(buffer, 10, stdin);
    sscanf(buffer, "%i", &meuBot->dinheiro);

    meuBot->quantidadeCioba = 0;
    meuBot->quantidadeRobalo = 0;
    meuBot->quantidadeTainha = 0;

    meuBot->destino = melhorAreaPesca(mapa);
    meuBot->acao = INDO_PESCAR;
}

void realizarAcao(struct Mapa *mapa, char *idBot, struct MeuBot *meuBot)
{
    mapa->areasPesca = lerAreasPesca(mapa->area);
    mapa->bots = lerBots(idBot);

    switch (meuBot->acao)
    {
    case INDO_PESCAR:
        indoPescar(*mapa, meuBot);
        break;
    case PESCANDO:
        pescando(*mapa, meuBot);
        break;
    case INDO_VENDER:
        indoVender(*mapa, meuBot);
        break;
    case VENDENDO:
        vendendo(*mapa, meuBot);
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