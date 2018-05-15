#version 130

attribute vec3 position;
attribute vec2 texCoord;

varying vec3 texcoords;

out vec3 normal;

out vec3 color;


void main()
{
    gl_Position = vec4(position.x,position.y,position.z, 1.0);	

}

	