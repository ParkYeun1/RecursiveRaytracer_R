#include "tracer.h"

#include <math.h>

using namespace raytraceData;

tracer::tracer() :
	s1(NULL)
{
}

tracer::~tracer()
{
}

/* point on ray r parameterized by t is returned in p */
void tracer::findPointOnRay(ray* r, float t, point* p) {
	p->x = r->start->x + t * r->end->x;
	p->y = r->start->y + t * r->end->y;
	p->z = r->start->z + t * r->end->z;
	p->w = 1.0;
}

/* raySphereIntersect */
/* returns TRUE if ray r hits sphere s, with parameter value in t */
int tracer::raySphereIntersect(ray* r, sphere* s, float* t) {
	point p;   /* start of transformed ray */
	float a, b, c;  /* coefficients of quadratic equation */
	float D;    /* discriminant */
	point* v;

	/* transform ray so that sphere center is at origin */
	/* don't use matrix, just translate! */
	p.x = r->start->x - s->c->x;
	p.y = r->start->y - s->c->y;
	p.z = r->start->z - s->c->z;
	v = r->end; /* point to direction vector */


	a = v->x * v->x + v->y * v->y + v->z * v->z;
	b = 2 * (v->x * p.x + v->y * p.y + v->z * p.z);
	c = p.x * p.x + p.y * p.y + p.z * p.z - s->r * s->r;

	D = b * b - 4 * a * c;

	if (D < 0) {  /* no intersection */
		return (FALSE);
	}
	else {
		D = static_cast<float>(sqrt(D));
		/* First check the root with the lower value of t: */
		/* this one, since D is positive */
		*t = (-b - D) / (2 * a);
		/* ignore roots which are less than zero (behind viewpoint) */
		if (*t < 0) {
			*t = (-b + D) / (2 * a);
		}
		if (*t < 0) { return(FALSE); }
		else return(TRUE);
	}
}

/* normal vector of s at p is returned in n */
/* note: dividing by radius normalizes */
void tracer::findSphereNormal(sphere* s, point* p, vector* n) {
	n->x = (p->x - s->c->x) / s->r;
	n->y = (p->y - s->c->y) / s->r;
	n->z = (p->z - s->c->z) / s->r;
	n->w = 0.0;
}

int tracer::rayCylinderIntersect(ray* r, cylinder* s, float* t) {
	point p;
	float a, b, c;
	float D;
	point* v;
	p.x = r->start->x - s->c->x;
	p.y = r->start->y - s->c->y;
	p.z = r->start->z - s->c->z;
	v = r->end;
	a = (v->x * v->x) + (v->z * v->z);
	b = (2 * p.x * v->x) + (2 * p.z * v->z);
	c = p.x * p.x + p.z * p.z - s->r * s->r;
	D = b * b - 4 * (a * c);
	if (fabs(D) < 0.001) return (FALSE);

	if (D < 0) {  /* no intersection */
		return (FALSE);
	}
	else {
		D = static_cast<float>(sqrt(D));
		float t1 = (-b - D) / (2 * a);
		float t2 = (-b + D) / (2 * a);
		if (t1 > t2) *t = t2;
		else *t = t1;
	}
	if (*t < 0) { return(FALSE); }
	else
	{
		GLfloat y = r->start->y + *t * r->end->y;
		if (y < s->c->y + s->r && y > s->c->y - s->r)
		{
			return(TRUE);
		}
		return(TRUE);
	}
}

void tracer::findCylinderNormal(cylinder* s, point* p, vector* n) {
	n->x = (p->x - s->c->x) / s->r;
	n->y = 0.0;
	n->z = (p->z - s->c->z) / s->r;
	n->w = 0.0;
}
int tracer::rayConeIntersect(ray* r, cone* s, float* t) {
	point p;
	float a, b, c;
	float D;
	point* v;
	p.x = r->start->x - s->c->x;
	p.y = r->start->y - s->c->y;
	p.z = r->start->z - s->c->z;
	v = r->end;
	float dd = s->r - r->start->y + s->c->y;
	a = (v->x * v->x) + (v->z * v->z - (v->y * v->y));
	b = (2 * p.x * v->x) + (2 * p.z * v->z) + (2 * dd * (v->y));
	c = p.x * p.x + p.z * p.z - dd * dd;

	D = b * b - 4 * (a * c);
	if (fabs(D) < 0.001) return (FALSE);

	if (D < 0) {
		return (FALSE);
	}
	else {
		D = static_cast<float>(sqrt(D));
		float t1 = (-b - D) / (2 * a);
		float t2 = (-b + D) / (2 * a);
		if (t1 > t2) *t = t2;
		else *t = t1;
	}
}

void tracer::findConeNormal(cone* s, point* p, vector* n) {

	n->x = (p->x - s->c->x) / s->r;
	n->y = sqrt((p->x - s->c->x) * (p->x - s->c->x) + (p->z - s->c->z) * (p->z - s->c->z));
	n->z = (p->z - s->c->z) / s->r;
	n->w = 0.0;
}

/* trace */
/* If something is hit, returns the finite intersection point p,
   the normal vector n to the surface at that point, and the surface
   material m. If no hit, returns an infinite point (p->w = 0.0) */
void tracer::trace(ray* r, point* p, vector* n, material** m) {
	float t = 0;     /* parameter value at first hit */
	int hit1 = FALSE;
	int hit2 = FALSE;
	int hit3 = FALSE;
	int hit4 = FALSE;
	int hit5 = FALSE;
	int hit6 = FALSE;
	int hit7 = FALSE;
	int hit8 = FALSE;
	int hit9 = FALSE;
	int hit10 = FALSE;
	int hit11 = FALSE;
	int hit12 = FALSE;

	hit1 = raySphereIntersect(r, s1, &t);
	hit2 = rayCylinderIntersect(r, s2, &t);
	hit4 = rayCylinderIntersect(r, s4, &t);
	hit5 = rayCylinderIntersect(r, s5, &t);
	hit6 = raySphereIntersect(r, s6, &t);
	hit7 = rayConeIntersect(r, s7, &t);
	hit3 = raySphereIntersect(r, s3, &t);
	hit8 = raySphereIntersect(r, s8, &t);
	hit9 = raySphereIntersect(r, s9, &t);
	hit10 = raySphereIntersect(r, s10, &t);
	hit11 = raySphereIntersect(r, s11, &t);
	hit12 = raySphereIntersect(r, s12, &t);
	if (hit2) {
		*m = s2->m;
		findPointOnRay(r, t, p);
		findCylinderNormal(s2, p, n);
	}
	if (hit4) {
		*m = s4->m;
		findPointOnRay(r, t, p);
		findCylinderNormal(s4, p, n);
	}
	if (hit5) {
		*m = s5->m;
		findPointOnRay(r, t, p);
		findCylinderNormal(s5, p, n);
	}
	if (hit6) {
		*m = s6->m;
		findPointOnRay(r, t, p);
		findSphereNormal(s6, p, n);
	}
	if (hit7) {
		*m = s7->m;
		findPointOnRay(r, t, p);
		findConeNormal(s7, p, n);
	}
	if (hit3) {
		*m = s3->m;
		findPointOnRay(r, t, p);
		findSphereNormal(s3, p, n);
	}
	if (hit1) {
		*m = s1->m;
		findPointOnRay(r, t, p);
		findSphereNormal(s1, p, n);
	}
	if (hit8) {
		*m = s8->m;
		findPointOnRay(r, t, p);
		findSphereNormal(s8, p, n);
	}
	if (hit9) {
		*m = s9->m;
		findPointOnRay(r, t, p);
		findSphereNormal(s9, p, n);
	}
	if (hit10) {
		*m = s10->m;
		findPointOnRay(r, t, p);
		findSphereNormal(s10, p, n);
	}
	if (hit11) {
		*m = s8->m;
		findPointOnRay(r, t, p);
		findSphereNormal(s11, p, n);
	}
	if (hit12) {
		*m = s12->m;
		findPointOnRay(r, t, p);
		findSphereNormal(s12, p, n);
	}


}


