#include "Mazequart.h"

Mazequart::Mazequart() : xrot (0.0f), yrot(0.0f), zrot(0.0f), scale(0.5)
{
	//Prepare hedge texture
	texid = Scene::GetTexture("./Hedge.bmp");
	if (texid != NULL)
	{
		toTexture = true;
	}else{
		toTexture = false;
	}
}

Mazequart::~Mazequart()
{
}

void Mazequart::Draw()
{
	glPushMatrix();

		if(toTexture)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texid);
		}		

		glTranslatef(-60.0f, -35.0f, -600.0f);
		
		glDisable(GL_CULL_FACE);

		float mat_colour[]                      // colour reflected by diffuse light
			= { 0.0f, 0.5f, 0.0f, 1.f };        
		float mat_ambient[]                     // ambient colour
			= { 0.0f, 0.333f, 0.0f, 1.f };  
		float mat_spec[]                        // specular colour
			= { 0.0f, 0.125f, 0.0f, 1.f }; 
   
		glPushAttrib(GL_ALL_ATTRIB_BITS);							// save current style attributes (inc. material properties)
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);	// set colour for ambient reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);	// set colour for diffuse reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);		// set colour for specular reflectance


		float r = 5.0f;

		//Create 4 hedges in a rectangle where it's longer than it is wide
		Hedge(r);

		glTranslatef(0, 0, r*30);

		Hedge(r);

		glTranslatef(r*25, 0, 0);

		Hedge(r);

		glTranslatef(0, 0, -r*30);

		Hedge(r);

		if (toTexture)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}

		glPopAttrib();

		glEnable(GL_CULL_FACE);

	glPopMatrix();
}


void Mazequart::Wall(float x, float y, float z)
{
	glBegin(GL_QUADS);

		// Near face
		glNormal3f(0, 0, 1);
		if(toTexture) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, z);
		if(toTexture) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, z);
		if(toTexture) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, z);
		if(toTexture) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, z);

		// Right face
		glNormal3f(1, 0, 0);
		if(toTexture) glTexCoord2f(0.f, 0.f);
		glVertex3f(x, -y, z);
		if(toTexture) glTexCoord2f(0.f, 1.f);
		glVertex3f(x, y, z);
		if(toTexture) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, -z);
		if(toTexture) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, -z);

		// Back face
		glNormal3f(0, 0, -1);
		if(toTexture) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, -z);
		if(toTexture) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, -z);
		if(toTexture) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, -z);
		if(toTexture) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, -z);

		// Left face
		glNormal3f(-1, 0, 0);
		if(toTexture) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, z);
		if(toTexture) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, z);
		if(toTexture) glTexCoord2f(1.f, 1.f);
		glVertex3f(-x, y, -z);
		if(toTexture) glTexCoord2f(1.f, 0.f);
		glVertex3f(-x, -y, -z);

		// Top face
		glNormal3f(0, -1, 0);
		if(toTexture) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, z);
		if(toTexture) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, -y, -z);
		if(toTexture) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, -y, -z);
		if(toTexture) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, z);

		// Bottom face
		glNormal3f(0, 1, 0);
		if(toTexture) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, y, z);
		if(toTexture) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, -z);
		if(toTexture) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, -z);
		if(toTexture) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, y, z);

	glEnd();
}

void Mazequart::Hedge(float r)
{
	//Create tall, square, outer walls
	glPushMatrix();
		Wall(r*5, r*3, r);
		glTranslatef(r*6, 0, -r*9);
		Wall(r, r*3, r*10);
		glTranslatef(-r*6, 0, -r*9);
		Wall(r*5, r*3, r);
		glTranslatef(-r*6, 0, r*9);
		Wall(r, r*3, r*10);
	glPopMatrix();

	//Create middle walls, square, medium height
	glPushMatrix();
		glTranslatef(0, -r, -r*3);
		Wall(r*2, r*2, r);
		glTranslatef(r*3, 0, -r*6);
		Wall(r, r*2, r*7);
		glTranslatef(-r*3, 0, -r*6);
		Wall(r*2, r*2, r);
		glTranslatef(-r*3, 0, r*6);
		Wall(r, r*2, r*7);
	glPopMatrix();	

	//Create centre smallest wall.
	glPushMatrix();
		glTranslatef(0, -r, -r*9);
		Wall(r, r, r*4);
	glPopMatrix();
}