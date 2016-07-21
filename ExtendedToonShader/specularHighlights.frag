uniform sampler2D Texture;

varying vec3 normal;
varying vec3 lightDir;
varying vec3 halfVector;

void main()
{
	vec4 color;
	vec2 index;
	float s = 2.0;
	float NdotL, NdotHV;
	float D;

	NdotL = max(dot(normal, lightDir), 0.0);
	NdotHV = max(dot(normal, halfVector),0.0);
	
	D = pow(NdotHV,s);

	index.x = NdotL;
	index.y = D;
	
	color = texture2D(Texture, index);
	
	gl_FragColor = color;
}