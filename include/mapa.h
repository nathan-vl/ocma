#ifndef MAPA_H
#define MAPA_H

#include "area_pesca.h"
#include "bot.h"
#include "posicao.h"

struct Mapa
{
    struct Posicao area;
    struct Posicoes portos;
    struct AreasPesca areasPesca;
    struct Bots bots;
};

struct Posicao lerTamanhoMapa(void);
struct Mapa lerMapa(struct Posicao area);
struct AreasPesca lerAreasPesca(struct Posicao areaMapa);
struct Posicao melhorAreaPesca(struct Mapa mapa);

#endif
