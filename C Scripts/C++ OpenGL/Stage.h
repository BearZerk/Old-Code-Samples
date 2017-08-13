#pragma once

#include "Object.h"

class Stage : public Object
{
public:
	Stage();
	~Stage();
	
	void Draw();
	
	void setTextures(GLuint* _texids);

private:
	void drawStage();
	float xrot, yrot, zrot;
    float scale;

	bool toTexture;
	GLuint* texids;
};

