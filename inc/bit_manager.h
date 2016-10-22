#ifndef BITMANAGER_H_
#define BITMANAGER_H_

int log_2(double x);
short valor_maximo(short * vet, int size);
int mask(int n);
short comp2_to_bit1(short a, int min_bit);
short bit1_to_comp2(short a, int min_bit);
int min_bit_calc(short *v, int size);

#endif