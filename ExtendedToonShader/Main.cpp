#include "Main.h"

void loadTexture(const char *textureName)
{
    GLbyte *pBytes;
    GLint width, height;

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1,&textureID);
	glBindTexture(GL_TEXTURE_2D, textureID); 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	pBytes = utilities.loadTGA(textureName, &width, &height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pBytes);
    free(pBytes);
}

void selectTexture(int choice)
{
	char fileName[100];

	if(selectFeature == DOF)
	{
		sprintf_s(fileName,"Textures/texDof_0%d.tga", choice);
		loadTexture(fileName);
	}
	else if(selectFeature == AERIAL)
	{
		sprintf_s(fileName,"Textures/texDof_0%d.tga", choice);
		loadTexture(fileName);
	}
	else if(selectFeature == SPECULAR)
	{
		sprintf_s(fileName,"Textures/texSpecular_0%d.tga", choice);
		loadTexture(fileName);
	}
	else
	{
		sprintf_s(fileName,"Textures/texBacklighting_0%d.tga", choice);
		loadTexture(fileName);
	}
}

void selectModel(int choice)
{
	switch(choice)
	{
	case 1:modelLoader.loadModel("bunny.obj");
		break;

	case 2:modelLoader.loadModel("terrain.obj");
		break;

	case 3:modelLoader.loadModel("dragon.obj");
		break;

	case 4:modelLoader.loadModel("buddha.obj");
		break;
	}
}

void drawFullscreenQuad()
{ 
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
   
	glTexCoord2f(0,0); 
	glVertex2f(0,0);

	glTexCoord2f(1,0); 
	glVertex2f(1,0);

	glTexCoord2f(1, 1); 
	glVertex2f(1, 1);

	glTexCoord2f(0, 1); 
	glVertex2f(0, 1);

	glEnd();
	glEnable(GL_DEPTH_TEST);
}

void reshapeOrtho(int w, int h)
{
	if (h == 0) h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void createFBO()
{
	glGenFramebuffers(1, &fboXToon);
	glBindFramebuffer(GL_FRAMEBUFFER, fboXToon);

	glGenRenderbuffers(1, &colorBufferXToon);
	glBindRenderbuffer(GL_RENDERBUFFER, colorBufferXToon);

	glGenTextures(1, &texXToon);
	glBindTexture(GL_TEXTURE_2D, texXToon);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_HALF_FLOAT, NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texXToon, 0);

	if(GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER))
	{
		std::cout<<"Unable to create frame buffer..."<<std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	std::cout<<"Frame Buffer created..."<<std::endl;
	std::cout<<" "<<std::endl;
}

void init()
{
	// Setup OpenGL state & scene resources (models, textures etc)
	glClearColor(1.0, 1.0, 1.0, 0.0);
	
	glEnable(GL_DEPTH_TEST);

	camera = Camera(width, height);

	//createFBO();

	modelLoader = ModelLoader();
	modelLoader.loadModel("bunny.obj");

	loadTexture("tex.tga");

	printf("Box Program:\n");
	boxProgram = utilities.loadProgram("textureBox.vert", NULL, "textureBox.frag");
	printf("\nDepth Of Field Program:\n");
	dofProgram = utilities.loadProgram("dof.vert", NULL, "dof.frag");
	printf("\nAerial Perspective Program:\n");
	aerialProgram = utilities.loadProgram("aerial.vert", NULL, "aerial.frag");
	printf("\nSpecular Highlights Program:\n");
	specularProgram = utilities.loadProgram("specularHighlights.vert", NULL, "specularHighlights.frag");
	printf("\nBacklighting Program:\n");	
	backlightingProgram = utilities.loadProgram("backlighting.vert", NULL, "backlighting.frag");

	selectFeature = DOF;

	texIndex = 1;
	modelIndex = 1;
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset Modelview matrix      	
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glGenerateMipmap(GL_TEXTURE_2D);

	glUseProgram(boxProgram);
	utilities.setUniform("BoxTexture", 0);

	glPushMatrix();
	glTranslatef(-5.0, 3.0, -10.0);
	glBegin(GL_QUADS);
   
	glTexCoord2f(0,0); 
	glVertex2f(0,0);

	glTexCoord2f(1,0); 
	glVertex2f(1,0);

	glTexCoord2f(1, 1); 
	glVertex2f(1, 1);

	glTexCoord2f(0, 1); 
	glVertex2f(0, 1);

	glEnd();
	glPopMatrix();
	
	glUseProgram(0);

	camera.RenderCam();
	camera.MoveCamMouse();

	switch(selectFeature)
	{
	case DOF:
		glUseProgram(dofProgram);;
		utilities.setUniform("Texture", 0);
		break;

	case SPECULAR:
		glUseProgram(specularProgram);
		utilities.setUniform("Texture", 0);
		break;

	case BACKLIGHTING:
		glUseProgram(backlightingProgram);
		utilities.setUniform("Texture", 0);
		break;

	case AERIAL:
		glUseProgram(aerialProgram);
		utilities.setUniform("Texture", 0);
		break;

	}

	utilities.setUniform("zFocus", camera.getPosition().z);

	modelLoader.renderModel();

	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// FPS
	frame++;

	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) 
	{
		sprintf(string,"XToon Shader | FPS: %4.2f",frame*1000.0/(time-timebase));
		timebase = time;
		frame = 0;
	}

	glutSetWindowTitle((const char*)&string);

    // Swap double buffer for flicker-free animation
    glutSwapBuffers();
}

void updateScene()
{
	camera.UpdateCam();

	rotAngle += 0.5;

    glutPostRedisplay();
}

void keypress(unsigned char key, int x, int y)
{
    if(key == 27)
	{
		exitScene();
	}

	if(key == '1')
	{
		selectFeature = DOF;
	}

	if(key == '2')
	{
		selectFeature = SPECULAR;
	}

	if(key == '3')
	{
		selectFeature = BACKLIGHTING;
	}

	if(key == '4')
	{
		selectFeature = AERIAL;
	}

	if(key == 'w' || key == 'W')
	{
		if(texIndex < MAX_TEXTURE_INDEX)
		{
			texIndex++;

			if(texIndex > MAX_TEXTURE_INDEX)
				texIndex = MAX_TEXTURE_INDEX - 1;
			
			selectTexture(texIndex);
		}
	}

	if(key == 's' || key == 'S')
	{
		if(texIndex > 0)
		{
			texIndex--;
			
			if(texIndex < 1)
				texIndex = 1;
			
			selectTexture(texIndex);
		}
	}

	if(key == 'a' || key == 'A')
	{
		if(modelIndex < MAX_MODEL_INDEX)
		{
			modelIndex++;

			if(modelIndex > MAX_MODEL_INDEX)
				modelIndex = MAX_MODEL_INDEX - 1;
			
			selectModel(modelIndex);
		}
	}

	if(key == 'd' || key == 'D')
	{
		if(modelIndex > 0)
		{
			modelIndex--;
			
			if(modelIndex < 1)
				modelIndex = 1;
			
			selectModel(modelIndex);
		}
	}
}

void motion(int x, int y)
{
	camera.CamMotion(x, y);
}

void mouse(int b, int s, int x, int y)
{
	camera.CamMouse(b, s, x, y);
}

void exitScene()
{
    std::cout<<"Exiting scene..."<<std::endl;

    // Close window
    glutDestroyWindow(windowId);

    exit(0);
}

void setViewport(int width, int height) 
{
    // Work out window ratio, avoid divide-by-zero
    if(height==0)height=1;
	float ratio = float(width)/float(height);

	// Fill screen with viewport
	glViewport(0, 0, width, height);

	// Reset projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set a 45 degree perspective
	gluPerspective(45, ratio, .1, 400);
}

int main(int argc, char *argv[])
{
	width = 800;
	height = 600;

    // Initialise OpenGL
    glutInit(&argc, argv); 

    // Set window position, size & create window
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
	windowId = glutCreateWindow("");
    
	glewInit();
	
    // Set GLUT callback functions
    glutReshapeFunc(setViewport);
    glutDisplayFunc(renderScene);
    glutIdleFunc(updateScene);
    glutKeyboardFunc(keypress);
	//glutSpecialFunc()
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

    init();
	
    // Show window & start update loop
    glutMainLoop();    

    return 0;
}
