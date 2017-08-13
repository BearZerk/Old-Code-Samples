
/*
Use this as the starting point to your work. Include the header file for each object in your scene, then add it to the scene using AddObjectToScene().
*/

#include "MyScene.h"
#include "Building.h"
#include "Pillar.h"
#include "Mazequart.h"
#include "Firepit.h"
#include "Sun.h"
#include "Stage.h"

// Constructor creates your CourseworkScene and initialises the base class Scene
MyScene::MyScene( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight ) : Scene(argc, argv, title, windowWidth, windowHeight)
{
}

// Initialise your scene by adding all the objects you want to be in the scene here
void MyScene::Init()
{
    // set background colour
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	float r = 25.0f;

    // for example: create and add a new triangle to the scene
	Stage *st = new Stage();
	Building *b = new Building();
	Pillar *p = new Pillar();
	Firepit *f = new Firepit();
	Mazequart *m = new Mazequart();
	Sun *s = new Sun();

	AddObjectToScene(st);
	AddObjectToScene(b);
	AddObjectToScene(s);
	AddObjectToScene(p);
	AddObjectToScene(f);
	AddObjectToScene(m);
}