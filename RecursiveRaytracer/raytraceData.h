#pragma once

#include <glad/glad.h>

/* constants */
#define TRUE 1
#define FALSE 0

#define M_PI 3.1415926535897932384626433832795029

namespace raytraceData {


	/* data structures */
	typedef struct point {
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat w;
	} point;

	/* a vector is just a point */
	typedef point vector;

	/* a line segment */
	typedef struct segment {
		point* start;
		point* end;
	} segment;

	/* a ray is just a segment with an endpoint at infinity */
	typedef struct ray {
		point* start;
		point* end;
	} ray;

	typedef struct color {
		GLfloat r;
		GLfloat g;
		GLfloat b;
		/* these should be between 0 and 1 */
	} color;

	typedef struct light {
		point* p;
		color* c;
	} light;

	typedef struct material {
		/* color */
		color c;
		/* ambient reflectivity */
		GLfloat amb;
		GLfloat diff;
		GLfloat spec;
		GLfloat refl;
	} material;

	typedef struct sphere {
		point* c;  /* center */
		GLfloat r;  /* radius */
		material* m;
	} sphere;
	typedef struct cylinder {
		point* c;
		GLfloat r;
		material* m;
	} cylinder;
	typedef struct cone {
		point* c;
		GLfloat r;
		material* m;
	} cone;


}