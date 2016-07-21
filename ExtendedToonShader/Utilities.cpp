#include "Utilities.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

Utilities::Utilities(void)
{
}

Utilities::~Utilities(void)
{
}

char* Utilities::textFileRead(char *fn) 
{
	FILE *fp;
	char *content = NULL;

	int count = 0;

	if (fn != NULL)
	{
		fp = fopen(fn,"rt");

		if (fp != NULL) 
		{      
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) 
			{
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

int Utilities::textFileWrite(char *fn, char *s) 
{
	FILE *fp;
	int status = 0;

	if (fn != NULL) 
	{
		fp = fopen(fn,"w");

		if (fp != NULL) 
		{
			
			if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
				status = 1;
			fclose(fp);
		}
	}
	return(status);
}

GLbyte* Utilities::loadTGA(const char *fileName, GLint *width, GLint *height)
{
	printf("Loading Texture... \n");
	FILE *vfile = fopen(fileName, "rb");
	GLbyte d;
	unsigned short w, h;
	int mode;
	GLbyte *bytes = NULL;

	if(NULL == vfile)
	{
		printf("Error Loading!! Empty file... \n");
		printf("\n");
		return NULL;
	}

	fseek(vfile, 12, SEEK_SET);
	fread(&w, sizeof(unsigned short), 1, vfile);

	fseek(vfile, 14, SEEK_SET);
	fread(&h, sizeof(unsigned short), 1, vfile);

	fseek(vfile, 16, SEEK_SET);
	fread(&d, sizeof(GLbyte), 1, vfile);

	mode = d / 8;
	
	int size = w * h * mode;
	
	*width = w;
	*height = h;

	bytes = (GLbyte*)malloc(size * sizeof(GLbyte));

	if(bytes == NULL)
	{
		printf("Error Loading!! Memory problem... \n");
		printf("\n");
		return NULL;
	}

	fseek(vfile, 18, SEEK_SET);
	fread(bytes, sizeof(GLbyte), size, vfile);
	fclose(vfile);

	if(mode > 3)
	{
		GLbyte temp;

		for(int i = 0; i < size; i += mode)
		{
			temp = bytes[i];
			bytes[i] = bytes[i+2];
			bytes[i+2] = temp;
		}
	}

	printf("Texture Loaded!! %d X %d X %d \n", w, h, mode);
	printf("\n");
	return bytes;
}

GLuint Utilities::loadProgram(char* vsKey, char* gsKey, char* fsKey)
{
	GLuint vertex, geom, frag, program;
	char *vSrc = NULL, *gSrc = NULL, *fSrc = NULL;
	
	GLint compileSuccess;
    GLchar compilerSpew[256];

	program = glCreateProgram();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	vSrc = textFileRead(vsKey);
	glShaderSource(vertex, 1, (GLchar const**)&vSrc, NULL);
	std::free(vSrc);
	glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &compileSuccess);
    glGetShaderInfoLog(vertex, sizeof(compilerSpew), 0, compilerSpew);
	printf("Vertex shader compiled.. \n%s", compilerSpew);
	glAttachShader(program, vertex);

	if(gsKey != NULL)
	{
		geom = glCreateShader(GL_GEOMETRY_SHADER);
		gSrc = textFileRead(gsKey);
		glShaderSource(geom, 1, (GLchar const**)&gSrc, NULL);
		std::free(gSrc);
		glCompileShader(geom);
		glGetShaderiv(geom, GL_COMPILE_STATUS, &compileSuccess);
		glGetShaderInfoLog(geom, sizeof(compilerSpew), 0, compilerSpew);
		printf("Geometry shader compiled.. \n%s", compilerSpew);
		glAttachShader(program, geom);
	}

	if(fsKey != NULL)
	{
		frag = glCreateShader(GL_FRAGMENT_SHADER);
		fSrc = textFileRead(fsKey);
		glShaderSource(frag, 1, (GLchar const**)&fSrc, NULL);
		std::free(fSrc);
		glCompileShader(frag);
		glGetShaderiv(frag, GL_COMPILE_STATUS, &compileSuccess);
		glGetShaderInfoLog(frag, sizeof(compilerSpew), 0, compilerSpew);
		printf("Fragment shader compiled.. \n%s", compilerSpew);
		glAttachShader(program, frag);
	}
	
	glLinkProgram(program);

	printf("\n");

	return program;
}

void Utilities::setUniform(const char* name, int value)
{
    GLuint program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*) &program);
    GLint location = glGetUniformLocation(program, name);
    glUniform1i(location, value);
}

void Utilities::setUniform(const char* name, float value)
{
    GLuint program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*) &program);
    GLint location = glGetUniformLocation(program, name);
    glUniform1f(location, value);
}

void Utilities::setUniformMat4(const char* name, GLfloat *value)
{
    GLuint program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*) &program);
    GLint location = glGetUniformLocation(program, name);
    glUniformMatrix4fv(location, 1, 0, &value[0]);
}

void Utilities::setUniformMat3(const char* name, GLfloat *value)
{
    GLuint program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*) &program);
    GLint location = glGetUniformLocation(program, name);
    glUniformMatrix3fv(location, 1, 0, &value[0]);
}

void Utilities::setUniform(const char* name, glm::vec3 value)
{
    GLuint program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*) &program);
    GLint location = glGetUniformLocation(program, name);
    glUniform3f(location, value.x, value.y, value.z);
}

void Utilities::setUniform(const char* name, glm::vec4 value)
{
    GLuint program;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*) &program);
    GLint location = glGetUniformLocation(program, name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}