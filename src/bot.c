#include "bot.h"
#include "direcao.h"
#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lerQuantidadeBots(void)
{
    int quantidade;
    char buffer[20];
    fgets(buffer, 20, stdin);
    sscanf(buffer, "BOTS %i", &quantidade);
    return quantidade;
}

void lerBot(char id[10], struct Posicao *posicao)
{
    char buffer[20];
    fgets(buffer, 20, stdin);
    sscanf(buffer, "%s %i %i", id, &posicao->altura, &posicao->largura);
}

struct Bots lerBots(char *idBot)
{
    struct Bots bots;

    int quantidade = lerQuantidadeBots();

    bots.adversarios.quantidade = quantidade - 1;
    bots.adversarios.posicoes = NULL;
    if (quantidade > 1)
    {
        bots.adversarios.posicoes = malloc(sizeof(struct Posicao) * bots.adversarios.quantidade);
    }

    int indiceBot = 0;
    for (int i = 0; i < quantidade; ++i)
    {
        struct Posicao pos;
        char id[15];
        lerBot(id, &pos);
        if (strncmp(idBot, id, strlen(idBot)) == 0)
        {
            bots.posicao = pos;
        }
        else
        {
            bots.adversarios.posicoes[indiceBot] = pos;
            ++indiceBot;
        }
    }

    return bots;
}
