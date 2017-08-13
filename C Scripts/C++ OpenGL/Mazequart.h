#pragma once

#include "Object.h"

class Mazequart : public Object
{
public:
	Mazequart();
	~Mazequart();

	void Draw();
	void Wall(float x, float y, float z);
	void Hedge(float r);

private:
    float xrot, yrot, zrot;
    float scale;

	bool toTexture;
	GLuint texid;
};

