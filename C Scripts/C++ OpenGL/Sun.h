#pragma once

#include "Object.h"

class Sun : public Object
{
public:
	Sun();
	~Sun();

	void Update(const double& deltaTime);

	float runtime();

private:
    float xrot, yrot, zrot;
    float scale;
	float aT;
	int modaT;

	bool sun;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
};

