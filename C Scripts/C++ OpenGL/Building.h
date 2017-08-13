#pragma once

#include "Object.h"

class Building : public Object
{
public:
	~Building();

	Building();

	void Draw();

	void Wall(float x, float y, float z);
	void Roof(float x, float y, float z);
	void Wall_Top (float x, float y, float z);

	void Building_Side (float x, float r, int normal);

	void Floor(float x);

private:
    float xrot, yrot, zrot;
    float scale;

	bool toTexture_wall;
	GLuint tex_wall_id;

	bool toTexture_roof;
	GLuint tex_roof_id;

	bool toTexture_floor;
	GLuint tex_floor_id;
};

