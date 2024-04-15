#pragma once

#include "raytraceData.h"

class tracer {
public:
	tracer();
	~tracer();

	void findPointOnRay(raytraceData::ray* r, float t, raytraceData::point* p);
	int raySphereIntersect(raytraceData::ray* r, raytraceData::sphere* s, float* t);
	int rayCylinderIntersect(raytraceData::ray* r, raytraceData::cylinder* s, float* t);
	int rayConeIntersect(raytraceData::ray* r, raytraceData::cone* s, float* t);
	void findSphereNormal(raytraceData::sphere* s, raytraceData::point* p, raytraceData::vector* n);
	void findCylinderNormal(raytraceData::cylinder* s, raytraceData::point* p, raytraceData::vector* n);
	void findConeNormal(raytraceData::cone* s, raytraceData::point* p, raytraceData::vector* n);
	void trace(raytraceData::ray* r, raytraceData::point* p, raytraceData::vector* n, raytraceData::material** m);
	raytraceData::sphere* s1;
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
};