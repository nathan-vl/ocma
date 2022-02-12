#include "area_pesca.h"
#include "bot.h"
#include "dados_iniciais.h"
#include "direcao.h"
#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>

enum AcaoAtual
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
    enum AcaoAtual acaoAtual;
};

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
        situacaoJogo->acaoAtual = PESCANDO;
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
        situacaoJogo->acaoAtual = INDO_VENDER;
    }
    else
    {
        struct Posicoes posicoesAreaPesca = {
            .posicoes = mapa.areasPesca.posicoes,
            .quantidade = mapa.areasPesca.quantidade
        };
        if (!posicaoEstaEmPosicoes(situacaoJogo->destino, posicoesAreaPesca))
        {
            situacaoJogo->destino = melhorAreaPesca(mapa);
            situacaoJogo->acaoAtual = INDO_PESCAR;
        }
    }
}

void indoVender(struct Mapa mapa, struct SituacaoJogo *situacaoJogo)
{
    enum Direcao d = proximaDirecao(mapa, situacaoJogo->destino);
    outputDirecao(d);
    if (posicoesSaoIguais(addDirecao(mapa.bots.posicao, d), situacaoJogo->destino))
    {
        situacaoJogo->acaoAtual = VENDENDO;
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
    situacaoJogo->acaoAtual = INDO_PESCAR;
}

int main(void)
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    char idBot[20];

    struct Posicao tamanhoMapa = lerTamanhoMapa();
    lerIdBot(idBot);

    // Essa primeira leitura é realizada para alocar os portos uma única vez.
    struct Mapa mapa = lerMapa(tamanhoMapa);
    mapa.bots = lerBots(idBot);

    struct SituacaoJogo situacaoJogo = {
        .acaoAtual = INDO_PESCAR,
        .destino = melhorAreaPesca(mapa),
        .capacidade = 0};

    outputDirecao(proximaDirecao(mapa, situacaoJogo.destino));

    free(mapa.areasPesca.posicoes);
    free(mapa.areasPesca.peixes);
    free(mapa.areasPesca.quantidadePeixes);
    if (mapa.bots.adversarios.quantidade >= 1)
    {
        free(mapa.bots.adversarios.posicoes);
    }

    while (1)
    {
        mapa.areasPesca = lerAreasPesca(tamanhoMapa);
        mapa.bots = lerBots(idBot);

        switch (situacaoJogo.acaoAtual)
        {
        case INDO_PESCAR:
            indoPescar(mapa, &situacaoJogo);
            break;
        case PESCANDO:
            pescando(mapa, &situacaoJogo);
            break;
        case INDO_VENDER:
            indoVender(mapa, &situacaoJogo);
            break;
        case VENDENDO:
            vendendo(mapa, &situacaoJogo);
            break;
        }

        free(mapa.areasPesca.posicoes);
        free(mapa.areasPesca.peixes);
        free(mapa.areasPesca.quantidadePeixes);
        if (mapa.bots.adversarios.quantidade >= 1)
        {
            free(mapa.bots.adversarios.posicoes);
        }
    }

    // Sei que esse trecho não será executado
    free(mapa.portos.posicoes);

    return 0;
}
