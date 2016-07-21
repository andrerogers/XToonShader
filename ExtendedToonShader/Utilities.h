#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

//#pragma comment(lib,"glew32d.lib")

class Utilities
{
public:
	// Constructor
	Utilities(void);

	// Destructor
	~Utilities(void);

	// Methods
	char* textFileRead(char *fn);
	int textFileWrite(char *fn, char *s);
	GLbyte* loadTGA(const char *fileName, GLint *width, GLint *height);

	GLuint loadProgram(char* vsKey, char* gsKey, char* fsKey);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, float value);
	void setUniformMat4(const char* name, GLfloat *value);
	void setUniformMat3(const char* name, GLfloat *value);
	void setUniform(const char* name, glm::vec3 value);
	void setUniform(const char* name, glm::vec4 value);
};

