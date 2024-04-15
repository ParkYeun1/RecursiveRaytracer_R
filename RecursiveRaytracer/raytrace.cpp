#include "raytrace.h"
#include <math.h>
#include <iostream>

using namespace raytraceData;

raytrace::raytrace(int w, int h)
{
	/* low-level graphics setup */
	lowlevel.initCanvas(w, h);

	/* raytracer setup */
	initCamera(w, h);
	initScene();
}

raytrace::~raytrace()
{
	if (s1 != NULL) delete s1;
	if (s2 != NULL) delete s2;
	if (s3 != NULL) delete s3;
	if (s4 != NULL) delete s4;
	if (s5 != NULL) delete s5;
	if (s6 != NULL) delete s6;
	if (s7 != NULL) delete s7;
	if (s8 != NULL) delete s8;
	if (s9 != NULL) delete s9;
	if (s10 != NULL) delete s10;
	if (s11 != NULL) delete s11;
	if (s12 != NULL) delete s12;
	if (viewpoint != NULL) delete viewpoint;
}


GLubyte* raytrace::display(void)
{
	drawScene();  /* draws the picture in the canvas */

	return lowlevel.flushCanvas();  /* draw the canvas to the OpenGL window */
}

void raytrace::initScene()
{
	s1 = makeSphere(0.0, 5.4, -3.0, 0.1);
	s2 = makeCylinder(1.2, 0.0, -6.0, 0.3);
	s3 = makeSphere(-0.3, 0.1, -5.0, 0.4);
	s4 = makeCylinder(-0.4, 1.0, -10.0, 0.3);
	s5 = makeCylinder(0.4, -10.0, -5.0, 0.1);
	s6 = makeSphere(-1.7, -0.8, -9.0, 1.0);
	s7 = makeCone(20.0, 0.8, -20.0, 0.3);
	s8 = makeSphere(0.0, 0.1, -3.0, 0.1);
	s9 = makeSphere(10.7, -0.2, -4.5, 0.2);
	s10 = makeSphere(20.0, 0.3, -3.0, 0.1);
	s11 = makeSphere(20.0, 0.4, -3.0, 0.1);
	s12 = makeSphere(20.0, 0.5, -3.0, 0.1);
	s1->m = makeMaterial(0.0, 0.2, 0.5, 0.0, 1.0, 1.0, 0.0);
	s2->m = makeMaterial(0.2, 0.0, 0.2, 0.0, 1.0, 1.0, 0.0);
	s3->m = makeMaterial(0.2, 0.2, 0.0, 0.0, 1.0, 1.0, 1.0);
	s4->m = makeMaterial(0.0, 0.1, 0.05, 0.0, 1.0, 1.0, 1.0);
	s5->m = makeMaterial(0.3, 0.2, 0.2, 0.0, 1.0, 1.0, 0.0);
	s6->m = makeMaterial(0.0, 0.1, 0.2, 0.0, 1.0, 1.0, 0.0);
	s7->m = makeMaterial(0.3, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0);
	s8->m = makeMaterial(0.3, 0.3, 0.3, 0.0, 1.0, 1.0, 0.0);
	s9->m = makeMaterial(0.3, 0.3, 0.3, 0.0, 1.0, 1.0, 0.0);
	s10->m = makeMaterial(0.3, 0.3, 0.3, 0.0, 1.0, 1.0, 0.0);
	s11->m = makeMaterial(0.3, 0.3, 0.3, 0.0, 1.0, 1.0, 0.0);
	s12->m = makeMaterial(0.3, 0.3, 0.3, 0.0, 1.0, 1.0, 0.0);
	tracer.s1 = s1;
	tracer.s2 = s2;
	tracer.s3 = s3;
	tracer.s4 = s4;
	tracer.s5 = s5;
	tracer.s6 = s6;
	tracer.s7 = s7;
	tracer.s8 = s8;
	tracer.s9 = s9;
	tracer.s10 = s10;
	tracer.s11 = s11;
	tracer.s12 = s12;
}

void raytrace::initCamera(int w, int h)
{
	viewpoint = makePoint(0.0, 0.0, 0.0, 1.0);
	pnear = -1.0;
	fovx = M_PI / 6;
	/* window dimensions */
	width = w;
	height = h;
}

void raytrace::drawScene(void)
{
	int i, j;
	GLfloat imageWidth;

	/* declare data structures on stack to avoid malloc & free */
	point worldPix;  /* current pixel in world coordinates */
	point direction;
	ray r;
	color c;
	/* z and w are constant for all pixels */
	worldPix.w = 1.0;
	worldPix.z = pnear;
	r.start = &worldPix;
	r.end = &direction;
	imageWidth = 2 * pnear * tan(fovx / 2);

	/* trace a ray for every pixel */
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {

			worldPix.y = (j - (height / 2)) * imageWidth / width;
			worldPix.x = (i - (width / 2)) * imageWidth / width;
			calculateDirection(viewpoint, &worldPix, &direction);

			rayColor(&r, &c);
			lowlevel.drawPixel(i, j, c.r, c.g, c.b);
		}
	}
}

sphere* raytrace::makeSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r) {
	sphere* s;
	s = new sphere();

	/* put stuff in it */
	s->c = makePoint(x, y, z, 1.0);   /* center */
	s->r = r;   /* radius */
	s->m = NULL;   /* material */
	return(s);
}
cylinder* raytrace::makeCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat r) {
	cylinder* s;

	s = new cylinder();
	s->c = makePoint(x, y, z, 1.0);
	s->r = r;
	s->m = NULL;
	return(s);
}
cone* raytrace::makeCone(GLfloat x, GLfloat y, GLfloat z, GLfloat r) {
	cone* s;
	s = new cone();
	s->c = makePoint(x, y, z, 1.0);
	s->r = r;
	s->m = NULL;
	return(s);
}

/* returns the color seen by ray r in parameter c */
void raytrace::rayColor(ray* r, color* c) {
	point p;  /* first intersection point */
	vector n, in;
	material* m;

	int d = 3;
	p.w = 0.0;  /* inialize to "no intersection" */
	tracer.trace(r, &p, &n, &m);

	if (p.w != 0.0) {
		shade(&p, &n, m, r, c, d);
	}
	else {             /* nothing was hit */
		c->r = 0.0;
		c->g = 0.0;
		c->b = 0.0;
	}
}

bool raytrace::shadow(ray* r)
{
	point p;
	vector n;
	material* m;

	p.w = 0.0;
	tracer.trace(r, &p, &n, &m);
	if (p.w != 0.0 && r->start->x <= p.x && (r->start->x + r->end->x) >= p.x && r->start->y <= p.y && (r->start->y + r->end->y) >= p.y && r->start->z <= p.z && (r->start->z + r->end->z) >= p.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
material* raytrace::makeMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat amb, GLfloat diff, GLfloat spec, GLfloat refl) {
	material* m;
	/* allocate memory */
	m = (material*)malloc(sizeof(material));

	m->c.r = r;
	m->c.g = g;
	m->c.b = b;
	m->amb = amb;
	m->diff = diff;
	m->spec = spec;
	m->refl = refl;
	return(m);
}
color* raytrace::makeColor(GLfloat r, GLfloat g, GLfloat b) {
	color* c;

	c = (color*)malloc(sizeof(color));
	c->r = r;
	c->g = g;
	c->b = b;
	return(c);
}

point* raytrace::makePoint(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	point* p;
	/* allocate memory */
	p = (point*)malloc(sizeof(point));
	/* put stuff in it */
	p->x = x; p->y = y; p->z = z; p->w = w;
	return (p);
}
void raytrace::calculateDirection(point* p, point* q, point* v) {
	float length;
	v->x = q->x - p->x;
	v->y = q->y - p->y;
	v->z = q->z - p->z;
	/* a direction is a point at infinity */
	v->w = 0.0;
}
light* raytrace::makeLight(GLfloat x, GLfloat y, GLfloat z) {
	light* l;
	l = (light*)malloc(sizeof(light));
	l->p = makePoint(x, y, z, 0);
	l->c = NULL;
	return(l);
}

light* lights;
void raytrace::shade(point* p, vector* n, material* m, ray* r, color* c, int d) {
	lights = makeLight(0.2, 0.2, 0.0);
	lights->c = makeColor(0.4, 0.4, 0.4);
	vector* s = makePoint(0, 0, 0, 0);
	vector* v = makePoint(r->end->x * -1, r->end->y * -1, r->end->z * -1, 0);
	vector* h = makePoint(0, 0, 0, 0);
	ray* shadowMaker = (ray*)malloc(sizeof(ray));
	shadowMaker->start = makePoint(p->x + .0005 * v->x, p->y + .0005 * v->y, p->z + .0005 * v->z, 0);
	shadowMaker->end = makePoint(0, 0, 0, 0);
	c->r = m->amb * m->c.r;
	c->g = m->amb * m->c.g;
	c->b = m->amb * m->c.b;
	GLfloat lambert = 0.0;
	GLfloat phong = 0.0;
	calculateDirection(p, lights->p, s);
	calculateDirection(shadowMaker->start, lights->p, shadowMaker->end);
	if (!shadow(shadowMaker))
	{
		h = makePoint(v->x + s->x, v->y + s->y, v->z + s->z, 0);
		lambert = s->x * n->x + s->y * n->y + s->z * n->z;
		phong = h->x * n->x + h->y * n->y + h->z * n->z / sqrt(h->x * h->x + h->y * h->y + h->z * h->z);
		c->r += lambert * lights->c->r * m->diff * m->c.r;
		c->g += lambert * lights->c->g * m->diff * m->c.g;
		c->b += lambert * lights->c->b * m->diff * m->c.b;

		if (lambert > 0)
		{
			c->r += lambert * lights->c->r * m->diff * m->c.r;
			c->g += lambert * lights->c->g * m->diff * m->c.g;
			c->b += lambert * lights->c->b * m->diff * m->c.b;
		}

		if (phong > 0)
		{
			phong = pow(phong, 5.0);
			c->r += phong * lights->c->r * m->spec * m->c.r;
			c->g += phong * lights->c->g * m->spec * m->c.g;
			c->b += phong * lights->c->b * m->spec * m->c.b;
		}
	}
	if (d < 4)
	{
		GLfloat reflect = (r->end->x * n->x + r->end->y * n->y + r->end->z * n->z);
		color* c2 = makeColor(0, 0, 0);
		ray* r2 = (ray*)malloc(sizeof(ray));
		r2->start = makePoint(p->x + 0.0005 * v->x, p->y + 0.0005 * v->y, p->z + 0.0005 * v->z, 0);
		r2->end = makePoint(r->end->x - 2 * reflect * n->x, r->end->y - 2 * reflect * n->y, r->end->z - 2 * reflect * n->z, 0);
		tracer.trace(r2, p, n, &m);
		if (p->w != 0.0) {
			reflection(p, n, m, r2, c2, d);
		}
		else {
			c2->r = 0.0;
			c2->g = 0.0;
			c2->b = 0.0;
		}
		c->r += m->refl * c2->r;
		c->g += m->refl * c2->g;
		c->b += m->refl * c2->b;
	}
	if (c->r > 1.0) c->r = 1.0;
	if (c->g > 1.0) c->g = 1.0;
	if (c->b > 1.0) c->b = 1.0;
}

void raytrace::reflection(point* p, vector* n, material* m, ray* r, color* c, int d) {
	lights = makeLight(0.2, 0.2, 0.0);
	lights->c = makeColor(0.1, 0.1, 0.1);
	vector* s = makePoint(0, 0, 0, 0);
	vector* v = makePoint(r->end->x * -1, r->end->y * -1, r->end->z * -1, 0);
	vector* h = makePoint(0, 0, 0, 0);
	ray* shadowMaker = (ray*)malloc(sizeof(ray));
	shadowMaker->start = makePoint(p->x + .0005 * v->x, p->y + .0005 * v->y, p->z + .0005 * v->z, 0);
	shadowMaker->end = makePoint(0, 0, 0, 0);

	GLfloat lambert = 0.0;
	GLfloat phong = 0.0;
	calculateDirection(p, lights->p, s);
	calculateDirection(shadowMaker->start, lights->p, shadowMaker->end);
	if (!shadow(shadowMaker))
	{
		h = makePoint(v->x + s->x, v->y + s->y, v->z + s->z, 0);
		lambert = s->x * n->x + s->y * n->y + s->z * n->z;
		phong = h->x * n->x + h->y * n->y + h->z * n->z / sqrt(h->x * h->x + h->y * h->y + h->z * h->z);
		c->r += lambert * lights->c->r * m->diff * m->c.r;
		c->g += lambert * lights->c->g * m->diff * m->c.g;
		c->b += lambert * lights->c->b * m->diff * m->c.b;

		if (lambert > 0)
		{
			c->r += lambert * lights->c->r * m->diff * m->c.r;
			c->g += lambert * lights->c->g * m->diff * m->c.g;
			c->b += lambert * lights->c->b * m->diff * m->c.b;
		}

		if (phong > 0)
		{
			phong = pow(phong, 0.1);
			c->r += phong * lights->c->r * m->spec * m->c.r;
			c->g += phong * lights->c->g * m->spec * m->c.g;
			c->b += phong * lights->c->b * m->spec * m->c.b;
		}
	}
	if (c->r > 1.0) c->r = 1.0;
	if (c->g > 1.0) c->g = 1.0;
	if (c->b > 1.0) c->b = 1.0;
}

