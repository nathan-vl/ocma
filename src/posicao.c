#include "posicao.h"
#include "acao.h"
#include "mapa.h"
#include <stdlib.h>

int abs(int n)
{
    if (n < 0)
        return -n;
    return n;
}

_Bool dentroMapa(struct Posicao tamanhoMapa, struct Posicao p)
{
    return p.altura >= 0 && p.altura < tamanhoMapa.altura && p.largura >= 0 && p.largura < tamanhoMapa.largura;
}

int calcDistanciaSimples(struct Posicao p1, struct Posicao p2)
{
    return abs(p1.altura - p2.altura) + abs(p1.largura - p2.largura);
}

_Bool posicoesSaoIguais(struct Posicao p1, struct Posicao p2)
{
    return (p1.altura == p2.altura) && (p1.largura == p2.largura);
}

struct Posicao maisPerto(struct Posicao inicio, struct Posicoes alvos)
{
    int menorDistancia = calcDistanciaSimples(inicio, alvos.posicoes[0]);
    struct Posicao p = alvos.posicoes[0];

    for (int i = 1; i < alvos.quantidade; ++i)
    {
        int distancia = calcDistanciaSimples(inicio, alvos.posicoes[i]);
        if (distancia < menorDistancia)
        {
            p = alvos.posicoes[i];
            menorDistancia = distancia;
        }
    }

    return p;
}

_Bool posicaoEstaEmPosicoes(struct Posicao posicao, struct Posicoes posicoes)
{
    _Bool resultado = 0;
    for (int i = 0; i < posicoes.quantidade; ++i)
    {
        resultado = resultado || posicoesSaoIguais(posicao, posicoes.posicoes[i]);
    }
    return resultado;
}
