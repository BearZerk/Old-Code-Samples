#include "Building.h"

Building::~Building()
{
}

Building::Building() : xrot (0.0f), yrot(0.0f), zrot(0.0f), scale(0.5)
{
	//Set up the 3 dfferent textures that's going to be used
	tex_wall_id = Scene::GetTexture("./Brick.bmp");
	if (tex_wall_id != NULL)
	{
		toTexture_wall = true;
	}else{
		toTexture_wall = false;
	}

	tex_roof_id = Scene::GetTexture("./Terracotta.bmp");
	if (tex_roof_id != NULL)
	{
		toTexture_roof = true;
	}else{
		toTexture_roof = false;
	}

	tex_floor_id = Scene::GetTexture("./Gravel.bmp");
	if (tex_floor_id != NULL)
	{
		toTexture_floor = true;
	}else{
		toTexture_floor = false;
	}
}

void Building::Draw()
{
	//Standard set up of attributes and matrix
	glPushMatrix();

		if(toTexture_wall)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tex_wall_id);
		}

		float r = 25.0f;

		glTranslatef(0.0f, 0.0f, -r*16);

		glDisable(GL_CULL_FACE);

		//Set materials for lighting values.
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
		
		//Actually start drawing
		glPushMatrix();
			//head backwards, draw the front wall, go back a little more draw the back wall
			//come toward camera & down, draw floor
			//Store current point
			glTranslatef(0, 0, -r*20);
			glNormal3f(0, 0, 1);
			Wall(r*10, r*2, 1);
			glTranslatef(0, 0, -r*2);
			glNormal3f(0, 0, -1);
			Wall(r*10, r*2, 1);
			glTranslatef(0, -r*2, r);
			glNormal3f(0, -1, 0);
			Wall(r*10, 1, r);
			glPushMatrix();
				//Go Left & Up, draw wall, head further up, draw triangluar wall head for roof to rest upon.
				//pop matrix and do this all again but go the right hand side.
				glTranslatef(-r*10, r*2, 0);
				glNormal3f(-1, 0, 0);
				Wall(1, r*2, r);
				glTranslatef(0, r*2, 0);
				glRotatef(90.0f, 0, 1.0f, 0);
				glNormal3f(-1, 0, 0);
				Wall_Top(r, r, 1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(r*10, r*2, 0);
				glNormal3f(1, 0, 0);
				Wall(1, r*2, r);
				glTranslatef(0, r*2, 0);
				glRotatef(90.0f, 0, 1.0f, 0);
				glNormal3f(1, 0, 0);
				Wall_Top(r, r, 1);
			glPopMatrix();
		glPopMatrix();

		//Create the building off shoots left & right
		glPushMatrix();
			Building_Side(r*10, r, 1);
		glPopMatrix();
		glPushMatrix();
			Building_Side(-r*6, r, -1);
		glPopMatrix();

		//Switch over to drawing the roof by changing the texture buffer
		if (toTexture_roof)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tex_roof_id);
		}

		//From original starting point
		//Move back and up, rotate to draw more easily
		//Draw nearest roofing, translate re-rotate and do the right hand side for the middle building
		glPushMatrix();
			glTranslatef(0, r*2, -r*20);
			glNormal3f(0, 1, 1);
			glRotatef(-45.0f, 1.0f, 0, 0);
			Roof(r*10, r*1.5f, 1);
			glRotatef(45.0f, 1.0f, 0, 0);
			glTranslatef(0, 0, -r*2);
			glRotatef(45.0f, 1.0f, 0, 0);
			glNormal3f(0, 1, -1);
			Roof(r*10, r*1.5f, 1);
		glPopMatrix();
		//From original point, move right & up.
		//Translate, rotate, rotate again so that it's perpendicular to the x axis
		//Draw roof, move more to the right, re-rotate and draw the far side roof on the right hand side building
		glPushMatrix();
			glTranslatef(r*7, r*0.5f, -r*10);
			glRotatef(90.0f, 0, 1.0f, 0);
			glRotatef(65.0f, 1.0f, 0, 0);
			glNormal3f(-1, 1, 0);
			Roof(r*10, r*1.25f, 1);
			glRotatef(-65.0f, 1.0f, 0, 0);
			glTranslatef(0, 0, r*2);
			glRotatef(-65.0f, 1.0f, 0, 0);
			glNormal3f(0, 1, 1);
			Roof(r*10, r*1.25, 1);
		glPopMatrix();
		//Do everything from the last push/pop but on the left hand side instead
		glPushMatrix();
			glTranslatef(-r*9, r*0.5f, -r*10);
			glRotatef(90.0f, 0, 1.0f, 0);
			glRotatef(65.0f, 1.0f, 0, 0);
			glNormal3f(-1, 1, 0);
			Roof(r*10, r*1.25f, 1);
			glRotatef(-65.0f, 1.0f, 0, 0);
			glTranslatef(0, 0, r*2);
			glRotatef(-65.0f, 1.0f, 0, 0);
			glNormal3f(0, 1, 1);
			Roof(r*10, r*1.25, 1);
		glPopMatrix();

		//Change to floor texture
		if (toTexture_floor)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tex_floor_id);
		}

		//Create 2 floor quads, 1 looks TOO stetched, 2 is reasonable
		glPushMatrix();
			glTranslatef(0, -r*2, -r*15);
			Floor(r*6);
			glTranslatef(0, 0, r*12);
			Floor(r*6);
		glPopMatrix();

		//Pop all values, enable cull facing again, disable texturing
		glPopAttrib();

		glEnable(GL_CULL_FACE);

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Building::Wall(float x, float y, float z)
{
	glBegin(GL_QUADS);

		// Near face
		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, z);
		if(toTexture_wall) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, z);

		// Right face
		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(x, -y, z);
		if(toTexture_wall) glTexCoord2f(0.f, 1.f);
		glVertex3f(x, y, z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, -z);

		// Back face
		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, -z);
		if(toTexture_wall) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, -z);

		// Left face
		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, z);
		if(toTexture_wall) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(-x, y, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(-x, -y, -z);

		// Top face
		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, z);
		if(toTexture_wall) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, -y, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, -y, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, z);

		// Bottom face
		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, y, z);
		if(toTexture_wall) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, y, z);

glEnd();
}

void Building::Roof(float x, float y, float z)
{
	glBegin(GL_QUADS);

		// Near face
		if(toTexture_roof) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, z);
		if(toTexture_roof) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, z);
		if(toTexture_roof) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, z);
		if(toTexture_roof) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, z);

		// Right face
		if(toTexture_roof) glTexCoord2f(0.f, 0.f);
		glVertex3f(x, -y, z);
		if(toTexture_roof) glTexCoord2f(0.f, 1.f);
		glVertex3f(x, y, z);
		if(toTexture_roof) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, -z);
		if(toTexture_roof) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, -z);

		// Back face
		if(toTexture_roof) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, -z);
		if(toTexture_roof) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, -z);
		if(toTexture_roof) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, -z);
		if(toTexture_roof) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, -z);

		// Left face
		if(toTexture_roof) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, z);
		if(toTexture_roof) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, z);
		if(toTexture_roof) glTexCoord2f(1.f, 1.f);
		glVertex3f(-x, y, -z);
		if(toTexture_roof) glTexCoord2f(1.f, 0.f);
		glVertex3f(-x, -y, -z);

		// Top face
		if(toTexture_roof) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, z);
		if(toTexture_roof) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, -y, -z);
		if(toTexture_roof) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, -y, -z);
		if(toTexture_roof) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -y, z);

		// Bottom face
		if(toTexture_roof) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, y, z);
		if(toTexture_roof) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, y, -z);
		if(toTexture_roof) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, y, -z);
		if(toTexture_roof) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, y, z);

glEnd();
}

void Building::Wall_Top(float x, float y, float z)
{
	glBegin(GL_TRIANGLES);
		
		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, 0, z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, 0, z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(0, y, z);

		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, 0, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, 0, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(0, y, -z);

	glEnd();

	glBegin(GL_QUADS);

		//Left 
		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, 0, z);
		if(toTexture_wall) glTexCoord2f(0.f, 1.f);
		glVertex3f(0, y, z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(0, y, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(-x, 0, -z);

		//Right
		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(x, 0, z);
		if(toTexture_wall) glTexCoord2f(0.f, 1.f);
		glVertex3f(0, y, z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(0, y, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, 0, -z);

		//Bottom
		if(toTexture_wall) glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, 0, z);
		if(toTexture_wall) glTexCoord2f(0.f, 1.f);
		glVertex3f(-x, 0, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 1.f);
		glVertex3f(x, 0, -z);
		if(toTexture_wall) glTexCoord2f(1.f, 0.f);
		glVertex3f(x, 0, z);

	glEnd();
}

void Building::Building_Side(float x, float r, int normal)
{

	int p;

	glTranslatef(x, -r, -r*10);
	glRotatef(90.0f, 0, 1.0f, 0);

	p = (normal == 1) ? 1 : -1;
	glNormal3f(p, 0, 0);

	Wall(r*10, r, 1);
	glTranslatef(0, 0, -r*4);

	p = (normal == 1) ? -1 : 1;
	glNormal3f(p, 0, 0);

	Wall(r*10, r, 1);
	glTranslatef(0, -r, r*2);
	glNormal3f(0, 1, 0);
	Wall(r*10, 1, r*2);
	glTranslatef(-r*10, r, 0);
	glNormal3f(0, 0, 1);
	Wall(1, r, r*2);
	glTranslatef(0, r, 0);
	glRotatef(90.0f, 0, 1.0f, 0);
	glNormal3f(0, 0, -1);
	Wall_Top(r*2, r, 1);
}

void Building::Floor(float x)
{
	glPushMatrix();

		glRotatef(90.0f, 1.0f, 0, 0);
		
		glBegin(GL_QUADS);
			glNormal3f(0, 0, -1);
			if(toTexture_floor) glTexCoord2f(0.f, 0.f);
			glVertex3f(-x, -x, 0);
			if(toTexture_floor) glTexCoord2f(0.f, 1.f);
			glVertex3f(-x, x, 0);
			if(toTexture_floor) glTexCoord2f(1.f, 1.f);
			glVertex3f(x, x, 0);
			if(toTexture_floor) glTexCoord2f(1.f, 0.f);
			glVertex3f(x, -x, 0);
		glEnd();

	glPopMatrix();
}