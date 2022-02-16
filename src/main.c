#include "acao.h"
#include "area_pesca.h"
#include "bot.h"
#include "direcao.h"
#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>

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

    struct MeuBot meuBot = {
        .acao = INDO_PESCAR,
        .destino = melhorAreaPesca(mapa),
        .quantidadeCioba = 0,
        .quantidadeRobalo = 0,
        .quantidadeTainha = 0};

    outputDirecao(calcularProximaDirecao(mapa, meuBot.destino));

    free(mapa.areasPesca.posicoes);
    free(mapa.areasPesca.peixes);
    free(mapa.areasPesca.quantidadePeixes);

    if (mapa.bots.adversarios.quantidade >= 1)
    {
        free(mapa.bots.adversarios.posicoes);
    }

    while (1)
    {
        realizarAcao(&mapa, idBot, &meuBot);
    }

    // Sei que esse trecho não será executado
    free(mapa.portos.posicoes);

    return 0;
}
