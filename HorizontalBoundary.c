#include "HorizontalBoundary.h"
#include "stdbool.h"

void init_horizontalBoundary(HorizontalBoundary *obj, double xMin, double yMin, double xMax){
	obj->_xMin = xMin;
	obj->_yMin = yMin;
	obj->_xMax = xMax;
	obj->_on = true;
}