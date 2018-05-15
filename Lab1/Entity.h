#pragma once
#include "glm/ext.hpp"

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* pi */
#endif

class GameEntity
{
protected:
	glm::vec3 position;
	glm::mat4 rotation;

public:
	GameEntity()
	{
		position = glm::vec3(0, 0, 0);
		rotation = glm::mat4();
	}

	virtual ~GameEntity()
	{

	}

	void translate(const glm::vec3& vec, float delta)
	{
		this->position += vec * delta;		
	}

	void rotate(const glm::vec3& vec, float angleDegrees)
	{
		rotation = glm::rotate(rotation, (float)M_PI/180 * angleDegrees, vec);
		
	}

	void setPosition(const glm::vec3& vec)
	{
		this->position = vec;
	}

	glm::vec3 getPosition()
	{
		return this->position;
	}
};