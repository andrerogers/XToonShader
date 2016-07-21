uniform sampler2D Texture;

varying vec3 normal;
varying vec3 lightDir;
varying vec3 v;

void main()
{
	vec4 color;
	vec2 index;
	float r = 2.0;
	float NdotL;
	float NdotV;
	float D;

	NdotL = max(dot(normal, lightDir), 0.0);
	NdotV = max(dot(normal, v), 0.0);
	
	D = pow(NdotV,r);

	index.x = NdotL;
	index.y = D;
	
	color = texture2D(Texture, index);
	
	gl_FragColor = color;
}