#ifndef HORIZONTALBOUNDARY_H
#define HORIZONTALBOUNDARY_H
#include <stdlib.h>
#include "stdbool.h"

typedef struct HorizontalBoundary{
	bool _on;
	double _xMin, _yMin;
	double _xMax;
}HorizontalBoundary;
void init_horizontalBoundary(HorizontalBoundary *obj, double xMin, double yMin, double xMax);

#endif