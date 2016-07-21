#pragma once

#include <windows.h>	
#include <mmsystem.h>	
#include <iostream>		
#include <GL\glew.h>
#include <GL\glext.h>
#include <GL\GL.h>
#include <GL\glut.h>
#include <GL\glui.h>

#include "Camera.h"
#include "Utilities.h"
#include "ModelLoader.h"

#define DOF 1
#define SPECULAR 2
#define BACKLIGHTING 3
#define AERIAL 4
#define MAX_TEXTURE_INDEX 6
#define MAX_MODEL_INDEX 4

// Main Window
void init();
void updateScene();
void renderScene();
void keypress(unsigned char key, int x, int y);
void motion(int x,int y);
void mouse(int b,int s,int x,int y);
void setViewport(int width, int height);

// Misc
void createFBO();
void loadTexture(const char *textureName);
void selectTexture(int choice);
void selectModel(int choice);
void reshapeOrtho(int w, int h);
void drawFullscreenQuad();
void exitScene();


// Window
int windowId;
int width;
int height;

// Camera
Camera camera;

// Utilities
Utilities utilities;

// Model Loader
ModelLoader modelLoader;
int modelIndex;

// Compute FPS
int frame = 0;
long time = 0;
long timebase = 0;
char string[50];

// Textures
GLuint textureID;
int texIndex;

// Frame Buffer Objects
GLuint fboXToon;
GLuint colorBufferXToon;
GLuint texXToon;

// Shader
GLuint boxProgram;
GLuint dofProgram;
GLuint aerialProgram;
GLuint specularProgram;
GLuint backlightingProgram;

// Misc
int selectFeature;
float rotAngle;
