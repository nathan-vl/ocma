#include "acao.h"
#include "direcao.h"
#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>

void indoPescar(struct Mapa mapa, struct SituacaoJogo *situacaoJogo)
{
    if (posicaoEstaEmPosicoes(situacaoJogo->destino, mapa.bots.adversarios))
    {
        situacaoJogo->destino = melhorAreaPesca(mapa);
    }

    enum Direcao d = calcularProximaDirecao(mapa, situacaoJogo->destino);
    outputDirecao(d);
    if (posicoesSaoIguais(addDirecao(mapa.bots.posicao, d), situacaoJogo->destino))
    {
        situacaoJogo->acao = PESCANDO;
    }
}

void pescando(struct Mapa mapa, struct SituacaoJogo *situacaoJogo)
{
    printf("FISH\n");

    char buffer[10];
    fgets(buffer, 10, stdin);
    switch (buffer[1])
    {
    case 'N':
        situacaoJogo->quantidadeCioba += 1;
        break;
    case 'E':
        situacaoJogo->quantidadeRobalo += 1;
        break;
    case 'U':
        situacaoJogo->quantidadeTainha += 1;
    }

    int capacidadeAtual = situacaoJogo->quantidadeCioba + situacaoJogo->quantidadeRobalo + situacaoJogo->quantidadeTainha;
    int valorBruto = situacaoJogo->dinheiro + situacaoJogo->quantidadeCioba * 150 + situacaoJogo->quantidadeRobalo * 200 + situacaoJogo->quantidadeTainha * 100;
    if (capacidadeAtual >= 10 || valorBruto >= 10000)
    {
        situacaoJogo->destino = maisPerto(mapa.bots.posicao, mapa.portos);
        situacaoJogo->acao = INDO_VENDER;
        return;
    }

    struct Posicoes posicoesAreaPesca = {
        .posicoes = mapa.areasPesca.posicoes,
        .quantidade = mapa.areasPesca.quantidade};
    if (!posicaoEstaEmPosicoes(situacaoJogo->destino, posicoesAreaPesca))
    {
        situacaoJogo->destino = melhorAreaPesca(mapa);
        situacaoJogo->acao = INDO_PESCAR;
    }
}

void indoVender(struct Mapa mapa, struct SituacaoJogo *situacaoJogo)
{
    enum Direcao d = calcularProximaDirecao(mapa, situacaoJogo->destino);
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
    sscanf(buffer, "%i", &situacaoJogo->dinheiro);

    situacaoJogo->quantidadeCioba = 0;
    situacaoJogo->quantidadeRobalo = 0;
    situacaoJogo->quantidadeTainha = 0;

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