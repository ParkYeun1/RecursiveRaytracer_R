#pragma once

#include <glad/glad.h>
#include "raytraceData.h"
#include "lowlevel.h"
#include "shader.h"
#include "tracer.h"

class raytrace {
public:
	raytrace(int w, int h);
	~raytrace();

	GLubyte* display(void);

private:
	void initScene();
	void initCamera(int w, int h);
	void drawScene(void);

	raytraceData::sphere* makeSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r);
	raytraceData::cylinder* makeCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat r);
	raytraceData::cone* makeCone(GLfloat x, GLfloat y, GLfloat z, GLfloat r);
	void rayColor(raytraceData::ray* r, raytraceData::color* c);
	raytraceData::material* makeMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat amb, GLfloat diff, GLfloat spec, GLfloat refl);
	raytraceData::light* makeLight(GLfloat x, GLfloat y, GLfloat z);
	raytraceData::point* makePoint(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	raytraceData::color* makeColor(GLfloat x, GLfloat y, GLfloat z);
	void shade(raytraceData::point* p, raytraceData::vector* n, raytraceData::material* m, raytraceData::ray* r, raytraceData::color* c, int d);
	void reflection(raytraceData::point* p, raytraceData::vector* n, raytraceData::material* m, raytraceData::ray* r, raytraceData::color* c, int d);
	void calculateDirection(raytraceData::point* p, raytraceData::point* q, raytraceData::point* v);
	bool shadow(raytraceData::ray* r);
	int width;     /* width of window in pixels */
	int height;    /* height of window in pixels */
	raytraceData::sphere* s1;	   /* the scene: so far, just one sphere */
	raytraceData::cylinder* s2;
	raytraceData::cylinder* s4;
	raytraceData::cylinder* s5;
	raytraceData::sphere* s6;
	raytraceData::cone* s7;
	raytraceData::sphere* s3;
	raytraceData::sphere* s8;
	raytraceData::sphere* s9;
	raytraceData::sphere* s10;
	raytraceData::sphere* s11;
	raytraceData::sphere* s12;

	/* parameters defining the camera */
	raytraceData::point* viewpoint;
	GLfloat pnear;  /* distance from viewpoint to image plane */
	GLfloat fovx;  /* x-angle of view frustum */
	lowlevel lowlevel;
	shader shader;
	tracer tracer;

};
