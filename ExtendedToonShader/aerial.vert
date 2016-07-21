varying vec3 normal;
varying vec3 lightDir;
varying float D;

uniform float zFocus;

void main()
{
	vec3 v;
	vec3 eye;

	float r = 30000000.0;
	float zmin = 0.000001;
	float zc = zFocus;
	//zc = 45.0;

	float z;
	float zmax = r * zmin;
	float zminm = zc - zmin;
	float zminp = zc + zmin;
	float zmaxm = zc - zmax;
	float zmaxp = zc + zmax;

	eye.x = 0.0;
	eye.y = 0.0;
	eye.z = 0.0;

	v = vec3((gl_ModelViewMatrix * gl_Vertex).xyz);

	z = abs(v.z);

	lightDir = normalize(vec3(0.0, 0.5, 20.0));
	normal = normalize(gl_NormalMatrix * gl_Normal);

	if (z < zminm)
	{
		D = 1.0 - (log(z / zminm) / log(zmaxm / zminm));
	}
	else if (z > zminp)
	{
		D = (log(z / zmaxp) / log(zminp / zmaxp));
	}
	else
	{
		D = 0.0;
	}

	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	gl_Position = ftransform();
}
