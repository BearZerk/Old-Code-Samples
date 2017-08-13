#include "Sun.h"
#include <cmath>

using namespace std;

Sun::Sun(void) : 
	xrot (0.0f), yrot(0.0f), zrot(0.0f), scale(0.5), sun(true), aT(0.0f)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

Sun::~Sun(void)
{
}

void Sun::Update(const double& deltaTime)
{
	aT += deltaTime;
	modaT = (int) aT % 120;

	if(modaT < 6 || modaT > 114)
	{
		float ambient[]  = { 0.2f, 0.2f, 0.2f, 1.f };      // ambient light (20% white)
		float diffuse[]  = { 0.5f, 0.5f, 0.5f, 1.f };      // diffuse light (50% white)
		float specular[] = { 1.f, 1.f, 1.f, 1.f };      // specular light (100% white)
		float position[] = { 1.f, .5f, 1.f, 0.f };      // directional light (w = 0)

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
		glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	}
	
	else if(modaT < 12 || modaT > 108)
	{
		float ambient[]  = { 0.18f, 0.18f, 0.18f, 1.f };      
		float diffuse[]  = { 0.45f, 0.45f, 0.45f, 1.f };     
		float specular[] = { 0.9f, 0.9f, 0.9f, 1.f };      
		float position[] = { 1.f, .5f, 1.f, 0.f };      
	
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
		glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	}

	else if(modaT < 18 || modaT > 102)
	{
		float ambient[]  = { 0.16f, 0.16f, 0.16f, 1.f };      
		float diffuse[]  = { 0.4f, 0.4f, 0.4f, 1.f };      
		float specular[] = { 0.8f, 0.8f, 0.8f, 1.f };     
		float position[] = { 1.f, .5f, 1.f, 0.f };    
	
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
		glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	}

	else if(modaT < 24 || modaT > 96)
	{
		float ambient[]  = { 0.14f, 0.14f, 0.14f, 1.f };      
		float diffuse[]  = { 0.35f, 0.35f, 0.35f, 1.f };     
		float specular[] = { 0.7f, 0.7f, 0.7f, 1.f };     
		float position[] = { 1.f, .5f, 1.f, 0.f };      

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
		glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	}

	else if(modaT < 30 || modaT > 90)
	{
		float ambient[]  = { 0.12f, 0.12f, 0.12f, 1.f };     
		float diffuse[]  = { 0.3f, 0.3f, 0.3f, 1.f };      
		float specular[] = { 0.6f, 0.6f, 0.6f, 1.f };      
		float position[] = { 1.f, .5f, 1.f, 0.f };      

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
		glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light sourc
	}

	else if(modaT < 36 || modaT > 84)
	{
		float ambient[]  = { 0.1f, 0.1f, 0.1f, 1.f };      
		float diffuse[]  = { 0.25f, 0.25f, 0.25f, 1.f };     
		float specular[] = { 0.5f, 0.5f, 0.5f, 1.f };     
		float position[] = { 1.f, .5f, 1.f, 0.f };     

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
		glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	}

	else if(modaT < 42 || modaT > 78)
	{
		float ambient[]  = { 0.08f, 0.08f, 0.08f, 1.f };    
		float diffuse[]  = { 0.2f, 0.2f, 0.2f, 1.f };      
		float specular[] = { 0.4f, 0.4f, 0.4f, 1.f };    
		float position[] = { 1.f, .5f, 1.f, 0.f };     

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
		glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	}

	else if(modaT < 48 || modaT > 72)
	{
		float ambient[]  = { 0.06f, 0.06f, 0.06f, 1.f };     
		float diffuse[]  = { 0.15f, 0.15f, 0.15f, 1.f };      
		float specular[] = { 0.3f, 0.3f, 0.3f, 1.f };     
		float position[] = { 1.f, .5f, 1.f, 0.f };      

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
		glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	}

	else if(modaT < 54 || modaT > 66)
	{
		float ambient[]  = { 0.04f, 0.04f, 0.04f, 1.f };      
		float diffuse[]  = { 0.1f, 0.1f, 0.1f, 1.f };     
		float specular[] = { 0.2f, 0.2f, 0.2f, 1.f };      
		float position[] = { 1.f, .5f, 1.f, 0.f };     

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
		glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	}

	else if(modaT < 60)
	{
		float ambient[]  = { 0.02f, 0.02f, 0.02f, 1.f };      
		float diffuse[]  = { 0.05f, 0.05f, 0.05f, 1.f };      
		float specular[] = { 0.1f, 0.1f, 0.1f, 1.f };     
		float position[] = { 1.f, .5f, 1.f, 0.f };      

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
		glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	}
}
