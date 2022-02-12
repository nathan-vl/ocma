#include "area_pesca.h"
#include "mapa.h"
#include "peixe.h"
#include "posicao.h"
#include <stdlib.h>

struct AreasPesca alocarAreasPesca(int quantidade)
{
    return (struct AreasPesca){
        .quantidade = quantidade,
        .peixes = malloc(sizeof(enum Peixe) * quantidade),
        .posicoes = malloc(sizeof(struct Posicao) * quantidade),
        .quantidadePeixes = malloc(sizeof(int) * quantidade)};
}

void copiarAreasPesca(struct AreasPesca destino, struct AreasPesca origem, int quantidade)
{
    for (int i = 0; i < quantidade; ++i)
    {
        destino.peixes[i] = origem.peixes[i];
        destino.posicoes[i] = origem.posicoes[i];
        destino.quantidadePeixes[i] = origem.quantidadePeixes[i];
    }
}

struct AreasPesca alocarAreasPescaComBuffer(struct AreasPesca buffer)
{
    struct AreasPesca areasPesca = alocarAreasPesca(buffer.quantidade);
    copiarAreasPesca(areasPesca, buffer, buffer.quantidade);
    return areasPesca;
}

int valorAreaPesca(
    struct Posicao atual, struct Posicao posicaoAreaPesca,
    enum Peixe peixe, int quantidade, struct Posicoes portos)
{
    // -1 porque não pode pescar o último peixe, então não conta
    const int valorBrutoLocal = valorPeixe(peixe) * (quantidade - 1);

    const struct Posicao portoProximoDestino = maisPerto(posicaoAreaPesca, portos);

    const int gastoDistancia = 50 * (calcDistanciaSimples(atual, posicaoAreaPesca) + calcDistanciaSimples(posicaoAreaPesca, portoProximoDestino));

    return valorBrutoLocal - gastoDistancia;
}
