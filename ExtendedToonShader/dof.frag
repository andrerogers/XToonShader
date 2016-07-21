uniform sampler2D Texture;

varying vec3 normal;
varying vec3 lightDir;
varying float D;

void main (void)
{
	vec4 color;
	vec2 index;

	float NdotL;
	NdotL = max(dot(normal, lightDir), 0.0);

	index.x = NdotL;
	index.y = D;
	color = texture2D(Texture, index);

	gl_FragColor = color;
}