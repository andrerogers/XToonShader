#include "Camera.h"

#include <iostream>

Camera::Camera()
{
}

Camera::Camera(int width, int height)
	: screenWidth(width), screenHeight(height)
{
	position = glm::vec3(0.0, 0.0, 0.0);
	view = glm::vec3(0.0, 0.0, -1.0);
	up = glm::vec3(0.0, 1.0, 0.0);
	strafe = glm::vec3(1.0, 0.0, 0.0);

	// Mouse
	zoom = 15.0f;
	rotx = 0;
	roty = 0.001f;
	tx = 0;
	ty = 0;
	lastx = 0;
	lasty = 0;
	Buttons[0] = 0;
	Buttons[1] = 0;
	Buttons[2] = 0;
}

Camera::~Camera()
{
}

void Camera::MoveCam(float distance)
{
	glm::vec3 viewDir = view - position;
	position += viewDir * distance;
	view += viewDir * distance;
}

void Camera::StrafeCam(float distance)
{
	position += strafe * distance;
	view += strafe * distance;
}

void Camera::MoveCamKeyboard()
{
	if(GetKeyState(VK_UP) & 0x80) 
		MoveCam(0.1);				

	if(GetKeyState(VK_DOWN) & 0x80)
		MoveCam(-0.1);				

	if(GetKeyState(VK_LEFT) & 0x80)			
		StrafeCam(-0.1);

	if(GetKeyState(VK_RIGHT) & 0x80)
		StrafeCam(0.1);
}

void Camera::CamMotion(int x, int y)
{
	int diffx = x-lastx;
	int diffy = y-lasty;
	lastx = x;
	lasty = y;

	if( Buttons[0] && Buttons[1] )
	{
		zoom -= (float) 0.05f * diffx;
	}
	else
		if( Buttons[0] )
		{
			rotx += (float) 0.5f * diffy;
			roty += (float) 0.5f * diffx;		
		}
		else
			if( Buttons[1] )
			{
				tx += (float) 0.05f * diffx;
				ty -= (float) 0.05f * diffy;
			}
			glutPostRedisplay();
}

void Camera::CamMouse(int b, int s, int x, int y)
{
	lastx = x;
	lasty = y;
	switch(b)
	{
		case GLUT_LEFT_BUTTON:
			Buttons[0] = ((GLUT_DOWN==s)?1:0);
			break;
		case GLUT_MIDDLE_BUTTON:
			Buttons[1] = ((GLUT_DOWN==s)?1:0);
			break;
		case GLUT_RIGHT_BUTTON:
			Buttons[2] = ((GLUT_DOWN==s)?1:0);
			break;
		default:
			break;		
	}
	glutPostRedisplay();
}

void Camera::MoveCamMouse()
{
	glTranslatef(0,0,-zoom);
	glTranslatef(tx,ty,0);
	glRotatef(rotx,1,0,0);
	glRotatef(roty,0,1,0);	
}

void Camera::RenderCam()
{
	gluLookAt(position.x, position.y, position.z, view.x, view.y, view.z, up.x, up.y, up.z);
}

void Camera::UpdateCam()
{
	MoveCamKeyboard();
}
