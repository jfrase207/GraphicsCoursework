#pragma once
#include "GameObject.h"



class Grid : public GameObject
{
public:

	struct Vert
	{
		float x, y, z;
	};
	
	Grid();
	~Grid();
	bool init();	
	void drawGrid();	
	void InitiateBuffers();
	bool getIndices(int width, int height);
	bool createVertices(int width, int height);
	int getVerticesCount(int width, int height);
	int getIndicesCount(int width, int height);

	GLuint VAO;
	GLuint vbo;
	GLuint ibo;

	

};