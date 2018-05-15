#pragma once
#include "GameObject.h"

class Rock : public GameObject
{
	
public:
	Rock()
	{

	}

	virtual ~Rock()
	{

	}

	void init(int rockNum)
	{
		std::string filename = "..\\res\\Asteroid";
		filename += std::to_string(rockNum);
		filename += ".obj";
		ModelMesh = new Mesh();
		ModelMesh->ModelLoader(filename);
		texture = new Texture();
		texture->init("..\\res\\asteroid.jpg");
	    shader = new Shader();		
		shader->init(rock,rock);
		this->rotate(glm::vec3(0, 1, 0), 180);
		sphereRadius = 5.0f;		
		
	   
	}
	
};