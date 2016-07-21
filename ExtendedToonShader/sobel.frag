uniform int Width, Height;
uniform float Thickness;
uniform float Threshold;
uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main (void)
{
	vec2 ox = vec2(Thickness/float(Width), 0.0);
	vec2 oy = vec2(0.0, Thickness/float(Height));
	vec2 uv = gl_TexCoord[0].st;
	mat3 grey;

	int i,j;
	vec2 PP = uv - oy;
	for(i = 0; i < 3; i++) {
		grey[i][0] = dot(texture2D(Texture1, PP - ox).rgb, vec3(0.33333));
		grey[i][1] = dot(texture2D(Texture1, PP).rgb, vec3(0.33333));
		grey[i][2] = dot(texture2D(Texture1, PP + ox).rgb, vec3(0.33333));
		PP += oy;
	}

	mat3 K;
	K[0][0] =-1.0; K[0][1] =-2.0; K[0][2] =-1.0;
	K[1][0] = 0.0; K[1][1] = 0.0; K[1][2] = 0.0;
	K[2][0] = 1.0; K[2][1] = 2.0; K[2][2] = 1.0;

	float sx = 0.0;
	float sy = 0.0;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			sx += grey[i][j] * K[i][j];
			sy += grey[i][j] * K[j][i];
		}
	}
	float dist = sqrt(sx*sx + sy*sy);

	if (dist > Threshold)	
		gl_FragColor = vec4(0.0);
	else
		gl_FragColor = texture2D(Texture0, gl_TexCoord[0].st);
}
