uniform vec3 lightDir;
uniform vec3 _color;
varying vec3 normal;



void main()
{
	float intensity;
	vec4 color;
	intensity = dot(normalize(lightDir),normal);

	if (intensity > 0.95)
		color = vec4((_color.r * 0.8),(_color.g * 0.8),(_color.b * 0.8),1.0);
	else if (intensity > 0.5)
		color = vec4((_color.r * 0.5),(_color.g * 0.5),(_color.b * 0.5),1.0);
	else if (intensity > 0.25)
		color = vec4((_color.r * 0.3),(_color.g * 0.3),(_color.b * 0.3),1.0);
	else
		color = vec4((_color.r * 0.1),(_color.g * 0.1),(_color.b * 0.1),1.0);


	gl_FragColor = color;

}