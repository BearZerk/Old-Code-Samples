#include "Pillar.h"


Pillar::Pillar() : xrot (0.0f), yrot(0.0f), zrot(0.0f), scale(0.5)
{
	//Set up white marble texture
	texid = Scene::GetTexture("./Marble.bmp");
	if (texid != NULL)
	{
		toTexture = true;
	}else{
		toTexture = false;
	}
}


Pillar::~Pillar()
{
}

void Pillar::Draw()
{
	glPushMatrix();

		if(toTexture)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texid);
		}

		float r = 25.0f;
		
		glTranslatef(-r*4.5, r*0.75f, -r*35);
		
		glDisable(GL_CULL_FACE);

		float mat_colour[]                      // colour reflected by diffuse light
			= { 0.5f, 0.5f, 0.5f, 1.f };        
		float mat_ambient[]                     // ambient colour
			= { 0.333f, 0.333f, 0.333f, 1.f };  
		float mat_spec[]                        // specular colour
			= { 0.125f, 0.125f, 0.125f, 1.f }; 
   
		glPushAttrib(GL_ALL_ATTRIB_BITS);							// save current style attributes (inc. material properties)
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);	// set colour for ambient reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);	// set colour for diffuse reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);		// set colour for specular reflectance

		Pillar_Body(r);

		glTranslatef(r*2, 0, 0);

		Pillar_Body(r);

		glTranslatef(r*5, 0, 0);

		Pillar_Body(r);

		glTranslatef(r*2, 0, 0);

		Pillar_Body(r);

		glEnable(GL_CULL_FACE);

		glPopAttrib();

		if (toTexture)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}

	glPopMatrix();
}

void Pillar::cylinder(float h, float r){
    float res = 0.1f*M_PI;           // resolution (in radians: equivalent to 18 degrees)
    float x = r, z = 0.f;           // initialise x and z on right of cylinder centre
    float t = 0.f;                  // initialise angle as 0

    do{
        glBegin(GL_QUADS);          // new QUAD
            // Create first points
			glNormal3f(x, h, z);
			if(toTexture) glTexCoord2f(0.f, 0.f);
            glVertex3f(x, h, z);    // top
			if(toTexture) glTexCoord2f(0.f, 1.f);
            glVertex3f(x, 0.f, z);  // bottom
            // Iterate around circle
            t += res;               // add increment to angle
            x = r*cos(t);           // move x and z around circle
            z = r*sin(t);
            // Close quad
			glNormal3f(x, h, z);
			if(toTexture) glTexCoord2f(1.f, 1.f);
            glVertex3f(x, 0.f, z);  // bottom
			if(toTexture) glTexCoord2f(1.f, 0.f);
            glVertex3f(x, h, z);    // top
        glEnd();                    // end shape

    } while (t <= 2 * M_PI);        // for a full circle (360 degrees)
}

void Pillar::Pillar_End(float r)
{
	float quart = 0.25f;
	float eighth = 0.125f;

	glBegin(GL_QUADS);	

			//Top Cube - Front Face
			glNormal3f(0, 0, 1);
			if(toTexture) glTexCoord2f(0.f, 0.f);
			glVertex3f(-r*quart, -r*eighth, r*quart);
			if(toTexture) glTexCoord2f(0.f, 1.f);
			glVertex3f(-r*quart, r*eighth, r*quart);
			if(toTexture) glTexCoord2f(1.f, 1.f);
			glVertex3f(r*quart, r*eighth, r*quart);
			if(toTexture) glTexCoord2f(1.f, 0.f);
			glVertex3f(r*quart, -r*eighth, r*quart);

			//Top Cube - Right Face
			glNormal3f(1, 0, 0);
			if(toTexture) glTexCoord2f(0.f, 0.f);
			glVertex3f(r*quart, -r*eighth, r*quart);
			if(toTexture) glTexCoord2f(0.f, 1.f);
			glVertex3f(r*quart, r*eighth, r*quart);
			if(toTexture) glTexCoord2f(1.f, 1.f);
			glVertex3f(r*quart, r*eighth, -r*quart);
			if(toTexture) glTexCoord2f(1.f, 0.f);
			glVertex3f(r*quart, -r*eighth, -r*quart);

			//Top Cube - Back face
			glNormal3f(0, 0, -1);
			if(toTexture) glTexCoord2f(0.f, 0.f);
			glVertex3f(-r*quart, -r*eighth, -r*quart);
			if(toTexture) glTexCoord2f(0.f, 1.f);
			glVertex3f(-r*quart, r*eighth, -r*quart);
			if(toTexture) glTexCoord2f(1.f, 1.f);
			glVertex3f(r*quart, r*eighth, -r*quart);
			if(toTexture) glTexCoord2f(1.f, 0.f);
			glVertex3f(r*quart, -r*eighth, -r*quart);

			//Tope Cube - Left face
			glNormal3f(-1, 0, 0);
			if(toTexture) glTexCoord2f(0.f, 0.f);
			glVertex3f(-r*quart, -r*eighth, r*quart);
			if(toTexture) glTexCoord2f(0.f, 1.f);
			glVertex3f(-r*quart, r*eighth, r*quart);
			if(toTexture) glTexCoord2f(1.f, 1.f);
			glVertex3f(-r*quart, r*eighth, -r*quart);
			if(toTexture) glTexCoord2f(1.f, 0.f);
			glVertex3f(-r*quart, -r*eighth, -r*quart);

			//Top Cube - Top face
			glNormal3f(0, 1, 0);
			if(toTexture) glTexCoord2f(0.f, 0.f);
			glVertex3f(-r*quart, -r*eighth, r*quart);
			if(toTexture) glTexCoord2f(0.f, 1.f);
			glVertex3f(-r*quart, -r*eighth, -r*quart);
			if(toTexture) glTexCoord2f(1.f, 1.f);
			glVertex3f(r*quart, -r*eighth, -r*quart);
			if(toTexture) glTexCoord2f(1.f, 0.f);
			glVertex3f(r*quart, -r*eighth, r*quart);

			//Top Cube - Bottom face
			glNormal3f(0, -1, 0);
			if(toTexture) glTexCoord2f(0.f, 0.f);
			glVertex3f(-r*quart, r*eighth, r*quart);
			if(toTexture) glTexCoord2f(0.f, 1.f);
			glVertex3f(-r*quart, r*eighth, -r*quart);
			if(toTexture) glTexCoord2f(1.f, 1.f);
			glVertex3f(r*quart, r*eighth, -r*quart);
			if(toTexture) glTexCoord2f(1.f, 0.f);
			glVertex3f(r*quart, r*eighth, r*quart);

		glEnd();
}

void Pillar::Pillar_Body(float r)
{
	
	float quart = 0.25f;
	float eighth = 0.125f;
	float sixth = 0.1666f;
	
	glPushMatrix();
		Pillar_End(r);

		glTranslatef(0.0f, -r*quart, 0.0f);
		cylinder(r*quart, r*sixth);
	
		glTranslatef(0.0f, -r*2, 0.0f);
		cylinder(r*2, r*eighth);

		glTranslatef(0.0f, -r*quart, 0.0f);
		cylinder(r*quart, r*sixth);
	
		glTranslatef(0.0f, -r*eighth, 0.0f);

		Pillar_End(r);
	glPopMatrix();
}