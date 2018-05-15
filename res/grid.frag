#version 330 core

out vec4 FragColor;
in vec3 finalcolor;
in vec3 color;

void main()
{
    
	gl_FragColor = vec4(finalcolor,1.0);
	

} 