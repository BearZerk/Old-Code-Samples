#include "Stage.h"
#include <iostream>

using namespace std;

Stage::Stage(void) : xrot (0.0f), yrot(0.0f), zrot(0.0f), scale(0.5)
{
	//Create skybox array which'll pass to setTextures
	GLuint* skybox = new GLuint[6];

	skybox[0] = Scene::GetTexture("./skybox_left.bmp");
	skybox[1] = Scene::GetTexture("./skybox_right.bmp");
	skybox[2] = Scene::GetTexture("./skybox_front.bmp");
	skybox[3] = Scene::GetTexture("./skybox_back.bmp");
	skybox[4] = Scene::GetTexture("./skybox_down.bmp");
	skybox[5] = Scene::GetTexture("./skybox_up.bmp");

	setTextures(skybox);
}


Stage::~Stage(void)
{
}

void Stage::Draw()
{
	glPushMatrix();

		glPushAttrib(GL_ALL_ATTRIB_BITS);
		// Project from Object Space to World Space
		glTranslatef(0, -50.01f, -650.0f);               // Position
		glScalef(400, 400, 400);
		glRotatef(yrot, 0.f, 1.f, 0.f);              // Set orientation (Y)
		glRotatef(zrot, 0.f, 0.f, 1.f);              // Set orientation (Z)
		glRotatef(xrot, 1.f, 0.f, 0.f);              // Set orientation (X)
	
		glDisable(GL_CULL_FACE);

		drawStage();

		glEnable(GL_CULL_FACE);

		glPopAttrib();

	glPopMatrix();
}

void Stage::drawStage()
{
	glDisable(GL_LIGHTING);                 // Disable lighting just for skybox
    if (toTexture) glEnable(GL_TEXTURE_2D); // Enable 2D texturing

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[0]); // skybox_left.bmp
    glBegin(GL_QUADS);
    // LEFT SIDE
        if (toTexture) glTexCoord2f(1.f, 1.f);  
        glVertex3f(-1.f, 1.f, -1.f);
        if (toTexture) glTexCoord2f(0.f, 1.f);  
        glVertex3f(-1.f, 1.f, 1.f);
        if (toTexture) glTexCoord2f(0.f, 0.f);  
        glVertex3f(-1.f, 0.f, 1.f);
        if (toTexture) glTexCoord2f(1.f, 0.f); 
        glVertex3f(-1.f, 0.f, -1.f);
    glEnd();

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[1]); // skybox_right.bmp
    glBegin(GL_QUADS);
    // RIGHT SIDE
        if (toTexture) glTexCoord2f(1.f, 1.f);  
        glVertex3f(1.f, 1.f, 1.f);
        if (toTexture) glTexCoord2f(0.f, 1.f);  
        glVertex3f(1.f, 1.f, -1.f);
        if (toTexture) glTexCoord2f(0.f, 0.f);  
        glVertex3f(1.f, 0.f, -1.f);
        if (toTexture) glTexCoord2f(1.f, 0.f);  
            glVertex3f(1.f, 0.f, 1.f);
    glEnd();

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[2]); // skybox_front.bmp
    glBegin(GL_QUADS);
    //  FAR SIDE
        if (toTexture) glTexCoord2f(1.f, 1.f);  
        glVertex3f(1.f, 1.f, -1.f);
        if (toTexture) glTexCoord2f(0.f, 1.f);  
        glVertex3f(-1.f, 1.f, -1.f);
        if (toTexture) glTexCoord2f(0.f, 0.f);  
        glVertex3f(-1.f, 0.f, -1.f);
        if (toTexture) glTexCoord2f(1.f, 0.f); 
            glVertex3f(1.f, 0.f, -1.f);
    glEnd();

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[3]); // skybox_back.bmp
    glBegin(GL_QUADS);
    // NEAR SIDE
        if (toTexture) glTexCoord2f(1.f, 1.f);  
        glVertex3f(-1.f, 1.f, 1.f);
        if (toTexture) glTexCoord2f(0.f, 1.f);  
        glVertex3f(1.f, 1.f, 1.f);
        if (toTexture) glTexCoord2f(0.f, 0.f);  
        glVertex3f(1.f, 0.f, 1.f);
        if (toTexture) glTexCoord2f(1.f, 0.f);  
        glVertex3f(-1.f, 0.f, 1.f);
    glEnd();

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[4]); // skybox_down.bmp
    glBegin(GL_QUADS);
    // BOTTOM SIDE
        if (toTexture) glTexCoord2f(1.f, 1.f);  
        glVertex3f(-1.f, 0.f, 1.f);
        if (toTexture) glTexCoord2f(0.f, 1.f);  
        glVertex3f(1.f, 0.f, 1.f);
        if (toTexture) glTexCoord2f(0.f, 0.f);  
        glVertex3f(1.f, 0.f, -1.f);
        if (toTexture) glTexCoord2f(1.f, 0.f); 
        glVertex3f(-1.f, 0.f, -1.f);
    glEnd();

    if (toTexture) glBindTexture(GL_TEXTURE_2D, texids[5]); // skybox_up.bmp
    glBegin(GL_QUADS);
    // TOP SIDE
        if (toTexture) glTexCoord2f(1.f, 1.f); 
        glVertex3f(1.f, 1.f, 1.f);
        if (toTexture) glTexCoord2f(0.f, 1.f);  
        glVertex3f(-1.f, 1.f, 1.f);
        if (toTexture) glTexCoord2f(0.f, 0.f);  
        glVertex3f(-1.f, 1.f, -1.f);
        if (toTexture) glTexCoord2f(1.f, 0.f);  
        glVertex3f(1.f, 1.f, -1.f);
    glEnd();

    if (toTexture) glDisable(GL_TEXTURE_2D);    // Disable texturing until reenabled
    glEnable(GL_LIGHTING);                      // Reenable lighting after drawing skybox
}

void Stage::setTextures(GLuint* _texids)
{
	//Check for if textures exist, if not cancel the whole thing
	texids = _texids;
	toTexture = true;
	for(int i = 0; i<6; i++)
	{
		if(texids[i] == NULL) 
		{	
			cerr << "No texture found" ;
			toTexture = false;
	
		}
	}
}