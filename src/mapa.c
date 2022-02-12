#include "area_pesca.h"
#include "mapa.h"
#include "posicao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mapa lerMapa(struct Posicao area)
{
    const int tamanho = area.largura * area.altura;

    struct Posicao bufferPosicoesPortos[tamanho];
    int indicePorto = 0;

    struct AreaPesca bufferAreasPesca[tamanho];
    int indiceAreaPesca = 0;
    for (int y = 0; y < area.altura; ++y)
    {
        for (int x = 0; x < area.largura; ++x)
        {
            int v;
            scanf(" %i", &v);
            struct Posicao posicaoAtual = (struct Posicao){.altura = y, .largura = x};

            // Apenas os portos e áreas de pesca que tem mais de um peixe
            if (v == 1)
            {
                bufferPosicoesPortos[indicePorto] = posicaoAtual;
                ++indicePorto;
            }
            else if ((v >= 10) && (v % 10) > 1)
            {
                bufferAreasPesca[indiceAreaPesca] = parseAreaPesca(posicaoAtual, v);
                ++indiceAreaPesca;
            }
        }
    }
    scanf("%*c"); // Tira o /n do fluxo de entrada

    struct Posicoes portos = {
        .quantidade = indicePorto,
        .posicoes = malloc(sizeof(struct Posicao) * indicePorto)};
    for (int i = 0; i < indicePorto; ++i)
    {
        portos.posicoes[i] = bufferPosicoesPortos[i];
    }

    struct AreasPesca areasPesca = alocarAreasPescaComBuffer(
        (struct AreasPesca){
            .quantidade = indiceAreaPesca,
            .areas = bufferAreasPesca});
    return (struct Mapa){
        .area = area,
        .portos = portos,
        .areasPesca = areasPesca};
}

struct AreasPesca lerAreasPesca(struct Posicao areaMapa)
{
    int tamanho = areaMapa.altura * areaMapa.largura;

    struct AreaPesca bufferAreasPesca[tamanho];
    int indiceAreaPesca = 0;

    for (int y = 0; y < areaMapa.altura; ++y)
    {
        for (int x = 0; x < areaMapa.largura; ++x)
        {
            int v;
            scanf(" %i", &v);
            struct Posicao posicaoAtual = (struct Posicao){.altura = y, .largura = x};

            // Apenas as áreas de pesca que tem mais de um peixe
            if ((v >= 10) && (v % 10) > 1)
            {
                bufferAreasPesca[indiceAreaPesca] = parseAreaPesca(posicaoAtual, v);
                ++indiceAreaPesca;
            }
        }
    }
    scanf("%*c"); // Tira o /n do fluxo de entrada
    return alocarAreasPescaComBuffer((struct AreasPesca){
        .quantidade = indiceAreaPesca,
        .areas = bufferAreasPesca});
}

struct Posicao melhorAreaPesca(struct Mapa mapa)
{
    struct Posicao posMelhorAreaPesca;
    int melhorValor = 0;

    for (int i = 0; i < mapa.areasPesca.quantidade; ++i)
    {
        struct AreaPesca area = mapa.areasPesca.areas[i];
        if (!posicaoEstaEmPosicoes(mapa.bots.posicao, mapa.bots.adversarios))
        {
            int valor = valorAreaPesca(mapa.bots.posicao, area, mapa.portos);
            if (valor > melhorValor)
            {
                posMelhorAreaPesca = area.posicao;
                melhorValor = valor;
            }
        }
    }

    return posMelhorAreaPesca;
}
