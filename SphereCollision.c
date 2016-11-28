#include "SphereCollision.h"
#include <stdio.h>
#include <math.h>

void init_SphereSphereCollision(SphereCollision *c, Sphere *s, Sphere *s2) {
	c->_time = -1;
	c->_sphere = *s;
	//c->_sphere._color = s->_color;
	//c->_sphere._initialParticlesColor = s->_initialParticlesColor;
	c->_sphereTag = s->_tag;
	c->_sphere2 = *s2;
	c->_sphere2Tag = s2->_tag;
	c->_type = 1; 
}
void init_SphereVerticalBoundaryCollision(SphereCollision *c, Sphere *s, VerticalBoundary *s2) {
	c->_time = -1;
	c->_sphere = *s;
	c->_sphereTag = s->_tag;
	c->_vb = *s2;
	c->_type = 2;
}

void init_SphereHorizontalBoundaryCollision(SphereCollision *c, Sphere *s, HorizontalBoundary *s2) {
	c->_time = -1;
	c->_sphere = *s;
	c->_sphereTag = s->_tag;
	c->_hb = *s2;
	c->_type = 3;
}

double getTime(SphereCollision *col){
	if (col->_time == -1){
		switch (col->_type){
		case 1:{
				   //change reference to sphere coordinate system; sphere velocity, x and y is zero
				   //velocity, x and y for sphere2 in sphere coordinates system
				   double vx = getVx(&col->_sphere2) - getVx(&col->_sphere);
				   double vy = getVy(&col->_sphere2) - getVy(&col->_sphere);
				   double x = getX(&col->_sphere2) - getX(&col->_sphere);
				   double y = getY(&col->_sphere2) - getY(&col->_sphere);
				   //collision radius
				   double r = getRadius(&col->_sphere2) + getRadius(&col->_sphere);
				   //circumference - line intersection equation coefficients
				   double a = vx*vx + vy*vy;
				   double b = 2 * (x*vx + y*vy);
				   double c = x*x + y*y - r*r;
				   // if solution exists
				   double aux = b*b - 4 * a*c;
				   if (aux >= 0){
					   //always choose first collision
					   double aux2 = -b - sqrt(aux);
					   //if solution time >= 0
					   if (aux2 >= 0 && a != 0){
						   col->_time = aux2 / (2 * a);
						   if (col->_time >= 1)
							   col->_time = -1;
					   }
				   }
				   return col->_time;
				   break;
		}	
		case 2:{
				   double time = -1;
				   double sx = getX(&col->_sphere);
				   double sy = getY(&col->_sphere);
				   double svx = getVx(&col->_sphere);
				   double svy = getVy(&col->_sphere);
				   double r = getRadius(&col->_sphere);
				   double bx = col->_vb._xMin;
				   if (sx < bx){
					   time = (bx - r - sx) / svx;
				   }
				   else{
					   time = (bx + r - sx) / svx;
				   }
				   double auxy = sy + time*svy;
				   if (auxy >= col->_vb._yMin && auxy <= col->_vb._yMax){
					   if (time >= 0 && time < 1) col->_time = time;
					   else 
						   col->_time = -1;
				   }
				   else 
					   col->_time = -1;
				   return col->_time;
				   break;
		}
		case 3:{
				   double time = -1;
				   double sx = getX(&col->_sphere);
				   double sy = getY(&col->_sphere);
				   double svx = getVx(&col->_sphere);
				   double svy = getVy(&col->_sphere);
				   double r = getRadius(&col->_sphere);
				   double by = col->_hb._yMin;
				   if (sy < by){
					   time = (by - r - sy) / svy;
				   }
				   else{
					   time = (by + r - sy) / svy;
				   }

				   double auxx = sx + time*svx;

				   if (auxx >= col->_hb._xMin && auxx <= col->_hb._xMax){
					   if (time >= 0 && time < 1) col->_time = time;
					   else 
						   col->_time = -1;
				   }
				   else 
					   col->_time = -1;
				   return col->_time;
				   break;
		}
		default:
			printf("Unexpected error at collision types.");
			return -2; //error code
			break;
		}

	}
	else
		return col->_time;
}