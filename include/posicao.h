#ifndef POSICAO_H
#define POSICAO_H

struct Posicao
{
    int altura;
    int largura;
};

struct Posicoes
{
    int quantidade;
    struct Posicao *posicoes;
};

_Bool dentroMapa(struct Posicao tamanhoMapa, struct Posicao p);
int calcDistanciaSimples(struct Posicao p1, struct Posicao p2);
struct Posicao maisPerto(struct Posicao posicao, struct Posicoes posicoes);
_Bool posicoesSaoIguais(struct Posicao p1, struct Posicao p2);
_Bool posicaoEstaEmPosicoes(struct Posicao posicao, struct Posicoes posicoes);

#endif
