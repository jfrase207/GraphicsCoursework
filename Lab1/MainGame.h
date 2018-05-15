#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Player.h"
#include "transform.h"
#include "Rocks.h"
#include "Skybox.h"
#include "Grid.h"
#include "Audio.h"

enum class GameState{LOAD,PLAY,DIE,EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void reset();
	void processInput();
	void gameLoop();
	void drawGame();
	void DrawRocks();
	bool CollisionCheck(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void playAudio(unsigned int Source, glm::vec3 pos);
	void CalculateDeltaTime();

	Display _gameDisplay;
	GameState _gameState;

	Audio audioDevice;
	Player player;
	Grid terrain;

	std::vector<Rock *> rocks;
	std::vector<glm::vec3> randomSpin;

	int playerMovingDirection;
	Skybox skybox;
	float explosionCounter;
	unsigned int backGroundMusic;

	

	float deltaTime;
	float oldTimeSinceStart;
	float explosionRate;
	float randX, randY, randZ;

	glm::vec3 randomVec;
};

