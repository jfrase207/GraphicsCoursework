#include "Grid.h"
#include "PerlinNoise.h"


//setup variables for terrain
Transform transformer;
int width = 200;
int height = 200;
glm::vec3 scale = glm::vec3(5, 1, 5);
float* vertices = 0;
int* indices = 0;
float seed = 0;
float offset = 0.2;

Grid::Grid()
{

}

Grid::~Grid()
{

}
//initialise arrays and create the mesh and buffers
bool Grid::init()
{
	
	vertices = new float[getVerticesCount(width, height)];
	indices = new int[getIndicesCount(width, height)];

	createVertices(width,height);
	getIndices(width,height);
	InitiateBuffers();
	
	return true;
}

//returns the amount of vertices needed based on grid width and height
int Grid::getVerticesCount(int width, int height) {
	return width * height * 3;
}
//returns the amount of indices needed based on grid width and height
int Grid::getIndicesCount(int width, int height) {
	return (width*height) + (width - 1)*(height - 2);
}

//create the vertices for the mesh
bool Grid::createVertices(int width, int height) 
{
	
	int i = 0;
	//create a random seed value for th perlin noise
	srand(time(NULL));
	seed = rand() % 1000 + 1;

	PerlinNoise pn(seed);
	//create the vertices
	for (int row = 0; row<width; row++) {
		for (int col = 0; col<height; col++) {
			
			double x = (double)row / ((double)width);
			double y = (double)col / ((double)height);
			//call the perlin noise function to create y values
			float n = pn.noise(10 * x, 0.8, 10 * y);
			float yVer = n * 30;
			//create verts
			vertices[i++] = (float)row;
			vertices[i++] = yVer;
			vertices[i++] = (float)col;
		}
	}

	return true;
}
//create the indices based on the grid paramaters
bool Grid::getIndices(int width, int height) 
{	
	int i = 0;
	//loop through the even rows creating indices
	for (int row = 0; row<width - 1; row++) {
		if ((row & 1) == 0) { // even rows
			for (int col = 0; col<height; col++) {
				indices[i++] = col + row * height;
				indices[i++] = col + (row + 1) * height;
			}
		}//loop through the odd rows to create odd indices
		else { // odd rows
			for (int col = height - 1; col>0; col--) {
				indices[i++] = col + (row + 1) * height;
				indices[i++] = col - 1 + +row * height;
			}
		}
	}//degenerate the triangles
	if ((height & 1) && height > 2) {
		indices[i++] = (height - 1) * width;
	}

	return true;
}


//generate, fill and bind opengl buffers with the vertices and indices
void Grid::InitiateBuffers()
{
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, getVerticesCount(width, height) * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesCount(width, height) * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);		

	shader = new Shader();
	shader->init(grid,grid);
}
//draw the grid
void Grid::drawGrid()
{
	transformer.SetPos(glm::vec3(-200, -20, -200));
	transformer.SetRot(this->rotation);
	transformer.SetScale(scale);

	if (shader)
	{
		shader->BindProgram();
		shader->UpdateMVP(transformer, Camera::getSingleton());
	}
	

	glCullFace(GL_FRONT);	
	
	glBindVertexArray(VAO);	
	
	glDrawElements(GL_TRIANGLE_STRIP, getIndicesCount(width, height), GL_UNSIGNED_INT, 0);

	glCullFace(GL_BACK);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	

}


