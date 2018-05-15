#pragma once

#include "GameObject.h"

class Skybox : GameObject
{
public:
	Skybox();
	~Skybox();

	bool initialise();

	void draw();

private:
	GLuint texSkybox;
	GLuint vao;
	void GenerateSkyboxMesh();
	void CreateSkyboxTexture(const std::string & filePrefix, const std::string & fileType);
	bool LoadSkyboxSides(GLuint texture, GLenum side_target, const std::string &file_name);
};