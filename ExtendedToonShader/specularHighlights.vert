varying vec3 normal;
varying vec3 lightDir;
varying vec3 halfVector;

void main()
{
	vec3 v;
	vec3 eye;
	vec3 viewDir;

	eye.x = 0.0;
	eye.y = 0.0;
	eye.z = 0.0;

	v = vec3((gl_ModelViewMatrix * gl_Vertex).xyz);

	lightDir = normalize(vec3(0.0, 0.5, 20.0));
	normal = normalize(gl_NormalMatrix * gl_Normal);
	viewDir = -normalize(eye - v);
	halfVector = normalize(lightDir + viewDir);
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	gl_Position = ftransform();
}