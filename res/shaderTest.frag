#version 400

uniform float exposure;
layout( location = 0 ) out vec4 fragcolor;


void main()
{             
    const float gamma = 2.2;
    vec3 hdrColor = vec3(1,0,0);
	vec3 bloomColor = vec3(0.7,0,0);
	

	hdrColor += bloomColor;
  
    // Exposure tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColor * 10);
    // Gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    fragcolor = vec4(mapped, 1.0);    
}  
