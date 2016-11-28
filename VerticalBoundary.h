#ifndef VERTICALBOUNDARY_H
#define VERTICALBOUNDARY_H
#include "stdbool.h"

typedef struct VerticalBoundary{
	bool _on;
	double _xMin;
	double _yMin;
	double _yMax;
}VerticalBoundary;
void init_verticalBoundary(VerticalBoundary *, double xMin, double yMin, double yMax);
#endif