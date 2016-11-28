#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdlib.h>
#include "Sphere.h"

void swap(int num1, int num2, Sphere *_particlesList);
int partition(int left, int right, int pivot, Sphere *_particlesList);
void quickSort(int left, int right, Sphere *_particlesList);

#endif