uniform sampler2D BoxTexture;

void main()
{
	vec4 color = texture2D(BoxTexture, gl_TexCoord[0].st);
	gl_FragColor = color;
}
