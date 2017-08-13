#include "Firepit.h"
#include <cmath>

Firepit::Firepit() : xrot (0.0f), yrot(0.0f), zrot(0.0f), scale(0.5), sun(true), aT(0.0f)
{
	//Set up textures going to be used
	texid = Scene::GetTexture("./Stone.bmp");
	if (texid != NULL)
	{
		toTexture = true;
	}else{
		toTexture = false;
	}

	tex_floor_id = Scene::GetTexture("./Ash.bmp");
	if (tex_floor_id != NULL)
	{
		toTexture_floor = true;
	}else{
		toTexture_floor = false;
	}


	//Set up LIGHT1 values and fall off point
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	GLfloat location[] = {57.5f, -20.0f, -350.0f, 1.f};
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1/5);
	glLightfv(GL_LIGHT1, GL_POSITION, location);
}

Firepit::~Firepit()
{
}

void Firepit::Draw()
{
	glPushMatrix();
		
		glTranslatef(0, -47.5, -825.0f);

		float mat_colour[]                      // colour reflected by diffuse light
			= { 0.5f, 0.5f, 0.0f, 1.f };        
		float mat_ambient[]                     // ambient colour
			= { 0.333f, 0.333f, 0.0f, 1.f };  
		float mat_spec[]                        // specular colour
			= { 0.125f, 0.125f, 0.0f, 1.f }; 
   
		glPushAttrib(GL_ALL_ATTRIB_BITS);							// save current style attributes (inc. material properties)
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);	// set colour for ambient reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);	// set colour for diffuse reflectance
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);		// set colour for specular reflectance

		float r = 25.0f * 0.125f;

		glDisable(GL_CULL_FACE);

		float res = 0.1f*M_PI;          // resolution (in radians: equivalent to 18 degrees)
		float x,z;                      // define x and z coordinates
		float rad = 10.0f;

		if(toTexture)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texid);
		}

        for (float t = 0.f; t <= 2 * M_PI; t += res)
		{  
            // Equation of a circle
            x = rad*cos(t);           // x = radius*cos(angle);
            z = rad*sin(t);           // z = radius*sin(angle);
           glTranslatef(x, 0.0f, z);

			glBegin(GL_QUADS);

				// Near face
				glNormal3f(0, 0, 1);
				if(toTexture) glTexCoord2f(0.f, 0.f);
				glVertex3f(-r, -r, r);
				if(toTexture) glTexCoord2f(0.f, 1.f);
				glVertex3f(-r, r, r);
				if(toTexture) glTexCoord2f(1.f, 1.f);
				glVertex3f(r, r, r);
				if(toTexture) glTexCoord2f(1.f, 0.f);
				glVertex3f(r, -r, r);

				// Right face
				glNormal3f(1, 0, 0);
				if(toTexture) glTexCoord2f(0.f, 0.f);
				glVertex3f(r, -r, r);
				if(toTexture) glTexCoord2f(0.f, 1.f);
				glVertex3f(r, r, r);
				if(toTexture) glTexCoord2f(1.f, 1.f);
				glVertex3f(r, r, -r);
				if(toTexture) glTexCoord2f(1.f, 0.f);
				glVertex3f(r, -r, -r);

				// Back face
				glNormal3f(0, 0, -1);
				if(toTexture) glTexCoord2f(0.f, 0.f);
				glVertex3f(-r, -r, -r);
				if(toTexture) glTexCoord2f(0.f, 1.f);
				glVertex3f(-r, r, -r);
				if(toTexture) glTexCoord2f(1.f, 1.f);
				glVertex3f(r, r, -r);
				if(toTexture) glTexCoord2f(1.f, 0.f);
				glVertex3f(r, -r, -r);

				// Left face
				glNormal3f(-1, 0, 0);
				if(toTexture) glTexCoord2f(0.f, 0.f);
				glVertex3f(-r, -r, r);
				if(toTexture) glTexCoord2f(0.f, 1.f);
				glVertex3f(-r, r, r);
				if(toTexture) glTexCoord2f(1.f, 1.f);
				glVertex3f(-r, r, -r);
				if(toTexture) glTexCoord2f(1.f, 0.f);
				glVertex3f(-r, -r, -r);

				// Top face
				glNormal3f(0, -1, 0);
				if(toTexture) glTexCoord2f(0.f, 0.f);
				glVertex3f(-r, -r, r);
				if(toTexture) glTexCoord2f(0.f, 1.f);
				glVertex3f(-r, -r, -r);
				if(toTexture) glTexCoord2f(1.f, 1.f);
				glVertex3f(r, -r, -r);
				if(toTexture) glTexCoord2f(1.f, 0.f);
				glVertex3f(r, -r, r);

				// Bottom face
				glNormal3f(0, 1, 0);
				if(toTexture) glTexCoord2f(0.f, 0.f);
				glVertex3f(-r, r, r);
				if(toTexture) glTexCoord2f(0.f, 1.f);
				glVertex3f(-r, r, -r);
				if(toTexture) glTexCoord2f(1.f, 1.f);
				glVertex3f(r, r, -r);
				if(toTexture) glTexCoord2f(1.f, 0.f);
				glVertex3f(r, r, r);

			glEnd();
		}
        
		if (toTexture_floor)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tex_floor_id);
		}

		glTranslatef(r*2, -r*2, r*10);
		Floor(r*10, r*3);
   
		glPopAttrib();

		glEnable(GL_CULL_FACE);

	glPopMatrix();
}

void Firepit::Update(const double& deltaTime)
{
	aT += deltaTime;
	modaT = (int) aT % 120;

	if(modaT < 6 || modaT > 114)
	{
		float ambient[]  = { 0.02f, 0.0f, 0.0f, 1.f };      
		float diffuse[]  = { 0.05f, 0.0f, 0.0f, 1.f };    
		float specular[] = { 0.1f, 0.0f, 0.0f, 1.f };     

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);    // set specular parameter of light source
	}
	
	else if(modaT < 12 || modaT > 108)
	{
		float ambient[]  = { 0.04f, 0.0f, 0.0f, 1.f };     
		float diffuse[]  = { 0.1f, 0.0f, 0.0f, 1.f };     
		float specular[] = { 0.2f, 0.0f, 0.0f, 1.f };     

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);    // set specular parameter of light source
	}

	else if(modaT < 18 || modaT > 102)
	{
		float ambient[]  = { 0.06f, 0.0f, 0.0f, 1.f };      
		float diffuse[]  = { 0.15f, 0.0f, 0.0f, 1.f };     
		float specular[] = { 0.3f, 0.0f, 0.0f, 1.f };      

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);    // set specular parameter of light source
	}

	else if(modaT < 24 || modaT > 96)
	{
		float ambient[]  = { 0.08f, 0.0f, 0.0f, 1.f };     
		float diffuse[]  = { 0.2f, 0.0f, 0.0f, 1.f };      
		float specular[] = { 0.4f, 0.0f, 0.0f, 1.f };      

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);    // set specular parameter of light source
	}

	else if(modaT < 30 || modaT > 90)
	{
		float ambient[]  = { 0.1f, 0.0f, 0.0f, 1.f };      
		float diffuse[]  = { 0.25f, 0.0f, 0.0f, 1.f };     
		float specular[] = { 0.5f, 0.0f, 0.0f, 1.f };      

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);    // set specular parameter of light source
	}

	else if(modaT < 36 || modaT > 84)
	{
		float ambient[]  = { 0.12f, 0.02f, 0.0f, 1.f };    
		float diffuse[]  = { 0.3, 0.05f, 0.0f, 1.f };     
		float specular[] = { 0.6f, 0.1f, 0.0f, 1.f };   

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);    // set specular parameter of light source
	}

	else if(modaT < 42 || modaT > 78)
	{
		float ambient[]  = { 0.14f, 0.04f, 0.0f, 1.f };     
		float diffuse[]  = { 0.35f, 0.1f, 0.0f, 1.f };    
		float specular[] = { 0.7f, 0.2f, 0.0f, 1.f };   

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);    // set specular parameter of light source
	}

	else if(modaT < 48 || modaT > 72)
	{
		float ambient[]  = { 0.16f, 0.06f, 0.0f, 1.f };      
		float diffuse[]  = { 0.4f, 0.15f, 0.0f, 1.f };   
		float specular[] = { 0.8f, 0.3f, 0.0f, 1.f };      

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);    // set specular parameter of light source
	}

	else if(modaT < 54 || modaT > 66)
	{
		float ambient[]  = { 0.18f, 0.08f, 0.0f, 1.f };    
		float diffuse[]  = { 0.45f, 0.20f, 0.0f, 1.f };     
		float specular[] = { 0.9f, 0.4f, 0.0f, 1.f }; 

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);    // set specular parameter of light source
	}

	else if(modaT < 60)
	{
		float ambient[]  = { 0.2f, 0.1f, 0.0f, 1.f };     
		float diffuse[]  = { 0.5f, 0.25f, 0.0f, 1.f };    
		float specular[] = { 1.0f, 0.5f, 0.0f, 1.f };  

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);    // set specular parameter of light source
	}
}

void Firepit::Floor(float x, float y)
{
	glPushMatrix();
		
		glRotatef(-90.0f, 1.0f, 0, 0);

		glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);

			if(toTexture_floor) glTexCoord2f(0.f, 0.f);
			glVertex3f(0, 0, y);
			if(toTexture_floor) glTexCoord2f(0.f, 1.f);
			glVertex3f(0, x, 0);
			if(toTexture_floor) glTexCoord2f(1.f, 1.f);
			glVertex3f(x, x, 0);
			if(toTexture_floor) glTexCoord2f(1.f, 0.f);
			glVertex3f(x, 0, 0);

			if(toTexture_floor) glTexCoord2f(0.f, 0.f);
			glVertex3f(0, 0, y);
			if(toTexture_floor) glTexCoord2f(0.f, 1.f);
			glVertex3f(0, -x, 0);
			if(toTexture_floor) glTexCoord2f(1.f, 1.f);
			glVertex3f(x, -x, 0);
			if(toTexture_floor) glTexCoord2f(1.f, 0.f);
			glVertex3f(x, 0, 0);

			if(toTexture_floor) glTexCoord2f(0.f, 0.f);
			glVertex3f(0, 0, y);
			if(toTexture_floor) glTexCoord2f(0.f, 1.f);
			glVertex3f(0, x, 0);
			if(toTexture_floor) glTexCoord2f(1.f, 1.f);
			glVertex3f(-x, x, 0);
			if(toTexture_floor) glTexCoord2f(1.f, 0.f);
			glVertex3f(-x, 0, 0);

			if(toTexture_floor) glTexCoord2f(0.f, 0.f);
			glVertex3f(0, 0, y);
			if(toTexture_floor) glTexCoord2f(0.f, 1.f);
			glVertex3f(0, -x, 0);
			if(toTexture_floor) glTexCoord2f(1.f, 1.f);
			glVertex3f(-x, -x, 0);
			if(toTexture_floor) glTexCoord2f(1.f, 0.f);
			glVertex3f(-x, 0, 0);

		glEnd();

	glPopMatrix();
}