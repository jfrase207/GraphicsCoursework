#version 400

//uniform mat4 u_pm;
//uniform mat4 u_vm;
uniform vec3 lightDir;
uniform float minDist;
uniform float maxDist;
uniform vec3 fogColor;
uniform vec3 playerPos;
uniform vec3 zposrock;
uniform vec3 _color;
layout( location = 0 ) out vec4 fragcolor;

 
in vec3 normal;
in vec4 v_pos;

vec3 toonShading() {	
	
	float intensity;
	vec4 color;
	intensity = dot(lightDir,normal);

	if (intensity > 0.95)
		color = vec4((_color.r * 0.8),(_color.g * 0.8),(_color.b * 0.8),1.0);
	else if (intensity > 0.5)
		color = vec4((_color.r * 0.5),(_color.g * 0.5),(_color.b * 0.5),1.0);
	else if (intensity > 0.25)
		color = vec4((_color.r * 0.3),(_color.g * 0.3),(_color.b * 0.3),1.0);
	else
		color = vec4((_color.r * 0.1),(_color.g * 0.1),(_color.b * 0.1),1.0);  

  return vec3(color.x,color.y,color.z);
}

void main() {

	float dist = sqrt((playerPos.x-zposrock.x) * (playerPos.x-zposrock.x) + (playerPos.y-zposrock.y) * (playerPos.y-zposrock.y) + (playerPos.z-zposrock.z) * (playerPos.z-zposrock.z));
		

	float fogFactor = (maxDist - dist) / (maxDist - minDist);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );
	vec3 toon = toonShading(); 

	vec3 color = mix( fogColor, toon, fogFactor);
	fragcolor = vec4(color, 1.0);

}
 



