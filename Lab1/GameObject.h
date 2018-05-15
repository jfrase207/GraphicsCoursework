#pragma once
#include "Entity.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "transform.h"
#include <vector>
#include <GLFW\glfw3.h>
#include <time.h>

class GameObject : public GameEntity
{
	Transform transform;
protected:
	Mesh *ModelMesh;
	Texture *texture; // Only 1 texture per mesh
	Shader *shader;

	float sphereRadius;

public:

	const std::string& rimToon = "..\\res\\shaderRimToon";
	const std::string& toon = "..\\res\\shaderToon";
	const std::string& fog = "..\\res\\shaderFog";
	const std::string& blur = "..\\res\\shaderBlur";
	const std::string& test = "..\\res\\shaderTest";
	const std::string& player = "..\\res\\playerShader";
	const std::string& rock = "..\\res\\rockShader";
	const std::string& grid = "..\\res\\grid";
	const std::string& skybox = "..\\res\\skybox";


	GameObject()
	{
		ModelMesh = 0;
		texture = 0;
		shader = 0;
		sphereRadius = 1.0f;
		
	}

	virtual ~GameObject()
	{
		if (ModelMesh)
		{
			delete ModelMesh;
			ModelMesh = 0;
		}

		if (texture)
		{
			delete texture;
			texture = 0;
		}

		if (shader)
		{
			delete shader;
			shader = 0;
		}
	}

	virtual void draw()
	{
		//Set transforms
		transform.SetPos(this->position);
		transform.SetRot(this->rotation);
		transform.SetScale(glm::vec3(1, 1, 1));
		//if theres a shader bind and update mvp
		if (shader)
		{
			shader->BindProgram();			
			shader->UpdateMVP(transform, Camera::getSingleton());			
		}
		//if theres a texture bind it
		if (texture)
			texture->Bind(0);
		//if theres a model mesh draw it and update sphere mesh data
		if (ModelMesh)
		{
			ModelMesh->draw();
			ModelMesh->updateSphereData(this->position, sphereRadius);
		}
	}		
	//get the sphere position
	glm::vec3 getSpherePos()
	{
		return ModelMesh->getSpherePos();
	}
	//get sphere radius
	float getSphereRadius()
	{
		return ModelMesh->getSphereRadius();
	}
	//set toon shading uniforms
	void setToon(glm::vec3 lightDir, glm::vec3 _color)
	{		
		shader->setVec3("lightDir", lightDir);
		shader->setVec3("_color", _color);
	}
	//sets the rim shading uniforms
	void setRimToon(glm::vec3 lightDir,glm::vec3 _color)
	{
		
		shader->setVec3("_color", _color);
		shader->setVec3("lightDir", lightDir);
		shader->setMat4("u_vm", Camera::getSingleton().GetView());
		shader->setMat4("u_pm", Camera::getSingleton().GetProjection());
		shader->setMat4("v_pos", transform.GetModel());
	}
	//set rock uniforms
	void RockUniforms(glm::vec3 _zPosPlayer, glm::vec3 _zPosRock, glm::vec3 _color, glm::vec3 _lightDir, float _cullDistance, float mag)
	{			
		shader->setVec3("playerPos", _zPosPlayer);
		shader->setVec3("zposrock", _zPosRock);

		shader->setFloat("cullDistance", _cullDistance);

		shader->setFloat("time", glfwGetTime());
		shader->setFloat("mag", mag);

		shader->setVec3("lightDir", _lightDir);
		shader->setVec3("_color", _color);
				
		shader->setVec3("fogColor", glm::vec3(0.7, 0.7, 0.7));
		shader->setFloat("minDist", 80);
		shader->setFloat("maxDist", 150);
		
		
	}
	//set the blur uniforms
	void setBlur()
	{
		shader->setVec4("OuterColor", glm::vec4(1, 0, 0, 1));
		shader->setVec4("InnerColor", glm::vec4(1, 1, 1, 1));
		shader->setFloat("RadiusInner", 1);
		shader->setFloat("RadiusOuter", 10);

	}	

	//set the player uniforms
	void PlayerUniforms(float mag, glm::vec3 lightDir, glm::vec3 _color)
	{	

		shader->setFloat("time", glfwGetTime());
		shader->setFloat("mag", mag);
		shader->setVec3("_color", _color);
		shader->setVec3("lightDir", lightDir);
	}

	//set the mvp if needed
	void setMvp(Transform transform, Camera camera)
	{
		glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
		shader->setMat4("_mvp", mvp);
	}

};
