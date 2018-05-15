#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;;

uniform float time;
uniform float mag;
out vec3 normal;

//calculate the normal for this fragment
vec3 GetNormal()
{
    vec3 tangent1 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 tangent2 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 normal = cross(tangent1, tangent2);
	return normalize(normal);
}  

//pass in the vertex position and normal and move the fragment along the normal
vec4 explode(vec4 position, vec3 normal)
{    
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * mag; 
    return position + vec4(direction, 0.0);
} 

void main()
{
	
	normal = GetNormal();
	//loop through each vertex and explode
	for(int i; i < 3; i++)
	{
		gl_Position = explode(gl_in[i].gl_Position, normal);  	
		EmitVertex();
	}   
    
    EndPrimitive();
}