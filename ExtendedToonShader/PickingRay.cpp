#include "PickingRay.h"

#include <windows.h>
#include <GL\glut.h>

PickingRay::PickingRay()
{
}

PickingRay::~PickingRay()
{
}

bool PickingRay::isRayIntersect(objLoader *model, glm::vec3 *hit)
{
	glm::vec3 T1, T2, T3;

	float u, v, w;

	GLfloat modelViewMat[16];
	float cameraPos[3];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMat);
	cameraPos[0] = -(modelViewMat[0] * modelViewMat[12] + modelViewMat[1] * modelViewMat[13] + modelViewMat[2] * modelViewMat[14]);
	cameraPos[1] = -(modelViewMat[4] * modelViewMat[12] + modelViewMat[5] * modelViewMat[13] + modelViewMat[6] * modelViewMat[14]);
	cameraPos[2] = -(modelViewMat[8] * modelViewMat[12] + modelViewMat[9] * modelViewMat[13] + modelViewMat[10] * modelViewMat[14]);

	rayStart.x = cameraPos[0];
	rayStart.y = cameraPos[1];
	rayStart.z = cameraPos[2];

	for(int i=0; i<model->faceCount; i++)
	{
		obj_face *o = model->faceList[i];

		T1 = glm::vec3(model->vertexList[ o->vertex_index[0]]->e[0],
						model->vertexList[ o->vertex_index[0]]->e[1],
						model->vertexList[ o->vertex_index[0]]->e[2]);

		T2 = glm::vec3(model->vertexList[ o->vertex_index[0]]->e[0],
						model->vertexList[ o->vertex_index[0]]->e[1],
						model->vertexList[ o->vertex_index[0]]->e[2]);

		T3 = glm::vec3(model->vertexList[ o->vertex_index[0]]->e[0],
						model->vertexList[ o->vertex_index[0]]->e[1],
						model->vertexList[ o->vertex_index[0]]->e[2]);

		glm::vec3 PQ = rayStop - rayStart;
		glm::vec3 PA = T1 - rayStart;
		glm::vec3 PB = T2 - rayStart;
		glm::vec3 PC = T3 - rayStart;

		u = glm::dot(PQ, glm::cross(PC, PB));
		if(u < 0.0)
			return false;

		v = glm::dot(PQ, glm::cross(PA, PC));
		if(v < 0.0)
			return false;

		w = glm::dot(PQ, glm::cross(PB, PA));
		if(w < 0.0)
			return false;

		float denom = 1.0 / (u + v + w);
		u *= denom;
		v *= denom;
		w *= denom;

		return true;
	}
	return false;
}
