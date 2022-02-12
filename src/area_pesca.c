#include "area_pesca.h"
#include "mapa.h"
#include "peixe.h"
#include "posicao.h"
#include <stdlib.h>

struct AreaPesca parseAreaPesca(struct Posicao p, int v)
{
    return (struct AreaPesca){
        .posicao = p,
        .quantidade = parseQuantidadePeixe(v),
        .peixe = parsePeixe(v)};
}

struct AreasPesca alocarAreasPesca(int quantidade)
{
    return (struct AreasPesca){
        .quantidade = quantidade,
        .areas = malloc(sizeof(struct AreaPesca) * quantidade)};
}

void copiarAreasPesca(struct AreasPesca destino, struct AreasPesca origem)
{
    for (int i = 0; i < origem.quantidade; ++i)
    {
        destino.areas[i] = origem.areas[i];
    }
}

struct AreasPesca alocarAreasPescaComBuffer(struct AreasPesca buffer)
{
    struct AreasPesca areasPesca = alocarAreasPesca(buffer.quantidade);
    copiarAreasPesca(areasPesca, buffer);
    return areasPesca;
}

int valorAreaPesca(
    struct Posicao atual,
    struct AreaPesca areaPesca,
    struct Posicoes portos)
{
    // -1 porque não pode pescar o último peixe, então não conta
    const int valorBrutoLocal = valorPeixe(areaPesca.peixe) * (areaPesca.quantidade - 1);

    const struct Posicao portoProximoDestino = maisPerto(areaPesca.posicao, portos);

    const int gastoDistancia = 50 * (calcDistanciaSimples(atual, areaPesca.posicao)
        + calcDistanciaSimples(areaPesca.posicao, portoProximoDestino));

    return valorBrutoLocal - gastoDistancia;
}
