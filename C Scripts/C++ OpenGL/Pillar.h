#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "Object.h"

class Pillar : public Object
{
public:
	Pillar();
	~Pillar();

	void Draw();

	void cylinder(float h, float r);
	void Pillar_End(float r);
	void Pillar_Body (float r);

private:
    float xrot, yrot, zrot;
    float scale;

	bool toTexture;
	GLuint texid;
};

