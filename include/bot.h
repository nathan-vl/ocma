#ifndef BOT_H
#define BOT_H

#include "posicao.h"

struct Bots
{
    struct Posicao posicao;
    struct Posicoes adversarios;
};

struct Bots lerBots(char *idBot);

#endif
