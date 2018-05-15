#include "Skybox.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Skybox::Skybox()
{
}

Skybox::~Skybox()
{
}

bool Skybox::initialise()
{
	GenerateSkyboxMesh();
	CreateSkyboxTexture("..\\res\\skybox\\cwd", ".jpg");
	return true;
}

void Skybox::GenerateSkyboxMesh()
{
	//create points for skybox mesh
	float points[] = {
		-10.0f,  10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,

		-10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,

		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,

		-10.0f, -10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,

		-10.0f,  10.0f, -10.0f,
		10.0f,  10.0f, -10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f, -10.0f,

		-10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		10.0f, -10.0f,  10.0f
	};

	//generate, bind and send data to vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);
}

void Skybox::CreateSkyboxTexture(const std::string &filePrefix, const std::string &fileType)
{
	// generate a cube-map texture to hold all the sides
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texSkybox);

	// load each image and copy into a side of the cube-map texture
	LoadSkyboxSides(texSkybox, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, filePrefix + "_ft" + fileType);
	LoadSkyboxSides(texSkybox, GL_TEXTURE_CUBE_MAP_POSITIVE_X, filePrefix + "_bk" + fileType);
	LoadSkyboxSides(texSkybox, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, filePrefix + "_up" + fileType);
	LoadSkyboxSides(texSkybox, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, filePrefix + "_dn" + fileType);
	LoadSkyboxSides(texSkybox, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, filePrefix + "_lf" + fileType);
	LoadSkyboxSides(texSkybox, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, filePrefix + "_rt" + fileType);
	// format cube map texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	shader = new Shader();
	shader->init("..\\res\\skybox");
}

bool Skybox::LoadSkyboxSides(GLuint texture, GLenum side_target, const std::string & file_name)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int x, y, n;
	int force_channels = 4;
	unsigned char*  image_data = stbi_load(file_name.c_str(), &x, &y, &n, force_channels);
	if (!image_data)
	{
		std::cerr << "texture load failed" << file_name << std::endl;
		return false;
	}

	// copy image data into 'target' side of cube map
	glTexImage2D(side_target, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	free(image_data);
	return true;
}

void Skybox::draw()
{
	//set skybox transforms
	Transform transform;
	transform.SetPos(Camera::getSingleton().getPosition());
	transform.SetRot(this->rotation);
	transform.SetScale(glm::vec3(1, 1, 1));


	glDepthMask(GL_FALSE);

	if (shader)
	{
		shader->BindProgram();
		shader->UpdateMVP(transform, Camera::getSingleton());
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texSkybox);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}

