#include <windows.h>
#include <mmsystem.h>
#include <GL\GL.h>
#include <GL\glut.h>
#include <math.h>

#include <glm\glm.hpp>

class Camera 
{
public:
	// Constructor
	Camera();
	Camera(int width, int height);

	// Destructor
	~Camera();

	// Methods
	void RenderCam();
	void UpdateCam();
	void MoveCam(float distance);							// Move camera forward, or backward
	void StrafeCam(float distance);							// Strafe camera left or right
	void MoveCamKeyboard();		
	void CamMouse(int b, int s, int x, int y);
	void CamMotion(int x, int y);
	void MoveCamMouse();

	inline void setPosition(glm::vec3 p) { position = p; }
	inline glm::vec3 getPosition() { return position; }
	inline void setView(glm::vec3 v) { view = v; }
	inline glm::vec3 getView() { return view; }
	inline void setUp(glm::vec3 u) { up = u; }
	inline glm::vec3 getUp() { return up; }

private:
	glm::vec3 position;
	glm::vec3 view;
	glm::vec3 up;		
	glm::vec3 strafe;	
	int screenWidth;
	int screenHeight;

	// For Mouse
	float zoom;
	float rotx;
	float roty;
	float tx;
	float ty;
	int lastx;
	int lasty;
	unsigned char Buttons[3];
};
