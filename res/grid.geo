#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;;


out vec3 finalcolor;

in vec3 color[];

uniform mat4 transform;


vec3 calculateLighting(vec3 normal){

	float brightness = max(dot(-vec3(0.5,0.5,0.5), normal), 0.0);
	return (vec3(0.5,0.5,0.5) * 1) + (brightness * vec3(0.5,0.5,0.5) * 1);
}

vec3 GetNormal()
{
    vec3 tangent1 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 tangent2 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 normal = cross(tangent1, tangent2);
	return normalize(normal);
}  

void main()
{
	vec3 normal = GetNormal();
	vec3 lighting = calculateLighting(normal);
	vec3 colorCont;

	for(int i=0;i<3;i++){
		gl_Position = transform * gl_in[i].gl_Position;
		
	if(gl_Position.y > -35)
		 colorCont = vec3(0,1,0);
	else if(gl_Position.y < -40)
		colorCont =vec3(0.6,0.8,0.9);
	else if(gl_Position.y > -25)
		colorCont = vec3(1,1,1);
	else
		colorCont = vec3(0.6,0.2,0.1);	

		finalcolor = colorCont * lighting;
		EmitVertex();
	}
	
	EndPrimitive();


}