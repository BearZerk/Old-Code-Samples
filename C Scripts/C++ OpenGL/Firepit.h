#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "Object.h"

class Firepit : public Object
{
public:
	Firepit();
	~Firepit();

	void Draw();
	void Update(const double& deltaTime);
	
	void Floor(float x, float y);


private:
    float xrot, yrot, zrot;
    float scale;
	float aT;
	int modaT;

	bool toTexture;
	GLuint texid;

	bool toTexture_floor;
	GLuint tex_floor_id;

	bool sun;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
};

