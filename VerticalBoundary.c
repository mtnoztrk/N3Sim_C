#include "VerticalBoundary.h"
#include "stdbool.h"

void init_verticalBoundary(VerticalBoundary *obj, double xMin, double yMin, double yMax){
	obj->_xMin = xMin;
	obj->_yMin = yMin;
	obj->_yMax = yMax;
	obj->_on = true;
}