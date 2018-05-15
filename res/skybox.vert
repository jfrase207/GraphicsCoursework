#version 120

attribute vec3 position;
attribute vec2 texCoord;

uniform mat4 transform;

varying vec3 texcoords;

void main()
{
  texcoords = position;
  gl_Position = transform * vec4(position, 1.0);
}