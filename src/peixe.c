#include "peixe.h"

enum Peixe parsePeixe(int n)
{
    return n / 10;
}

int parseQuantidadePeixe(int n)
{
    return n % 10;
}

int valorPeixe(enum Peixe peixe)
{
    /*
    TAINHA: 100
    CIOBA: 150
    ROBALO: 200
    */

    return 50 * (peixe + 1);
}