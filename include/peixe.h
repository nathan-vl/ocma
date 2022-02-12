#ifndef PEIXE_H
#define PEIXE_H

enum Peixe
{
    TAINHA = 1,
    CIOBA,
    ROBALO
};

enum Peixe parsePeixe(int n);
int parseQuantidadePeixe(int n);
int valorPeixe(enum Peixe peixe);

#endif
