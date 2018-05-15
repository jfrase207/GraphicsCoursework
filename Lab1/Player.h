#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player()
	{
		
	}

	void init()
	{
		ModelMesh = new Mesh();
		ModelMesh->ModelLoader("..\\res\\Ship.obj");
		texture = new Texture();
		texture->init("..\\res\\ship.png");
		shader = new Shader();		
		shader->init(player,player);
		sphereRadius = 2.5f;	
		
	}
	virtual ~Player()
	{

	}
};