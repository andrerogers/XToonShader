varying vec3 normal;
varying vec3 lightDir;
varying vec3 v;

void main()
{
	vec3 mV;
	vec3 eye;

	eye.x = 0.0;
	eye.y = 0.0;
	eye.z = 0.0;
	
	mV = vec3((gl_ModelViewMatrix * gl_Vertex).xyz);

	v = normalize(eye - mV);
	lightDir = normalize(vec3(0.0, 0.5, 20.0));
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	gl_Position = ftransform();
}