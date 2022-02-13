#ifndef BOT_H
#define BOT_H

#include "posicao.h"

struct Bots
{
    struct Posicao posicao;
    struct Posicoes adversarios;
};

void lerIdBot(char *destino);
struct Bots lerBots(char *idBot);

#endif
