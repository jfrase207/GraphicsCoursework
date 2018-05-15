#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Entity.h"

class Camera : public GameEntity
{
private:
	static Camera *singleton;

public:
	Camera()
	{
	}

	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->position = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	inline glm::mat4 GetProjection() const
	{
		return projection;
	}

	inline glm::mat4 GetView() const
	{
		return glm::lookAt(position, position + forward, up);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(this->position, this->position + forward, up);
	}

	static Camera &getSingleton()
	{
		if (!singleton)
		{
			singleton = new Camera();
		}

		return *singleton;
	}

	void setFollowEntity(GameEntity *entity)
	{
		followEntity = entity;
	}

	void update()
	{
		if (followEntity)
		{
			setPosition(followEntity->getPosition() - glm::vec3(0, -4, 15));
		}
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 forward;
	glm::vec3 up;
	GameEntity *followEntity;
};


