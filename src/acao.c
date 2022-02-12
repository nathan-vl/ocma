#include "acao.h"
#include <stdio.h>

void outputAcao(enum Acao acao)
{
    const char acoes[][5] = {"FISH", "SELL"};
    printf("%s\n", acoes[acao]);
}
