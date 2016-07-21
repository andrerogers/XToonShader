#include "ModelLoader.h"

#include <GL\glut.h>

ModelLoader::ModelLoader(void)
{
	model = new objLoader();
}

ModelLoader::~ModelLoader(void)
{
}

void ModelLoader::loadModel(const char *fileName)
{
	model->load((char *)fileName);
}

void ModelLoader::renderModel()
{
	glTranslatef(0.0,-2.5,0.0);
	glScalef(0.7,0.7,0.7);
	glBegin(GL_TRIANGLES);
		for(int i=0; i<model->faceCount; i++)
		{
			obj_face *o = model->faceList[i];
			for(int j=0; j<3; j++)
			{
				//glTexCoord3f(model->textureList[o->texture_index[j]]->e[0],
				//			 model->textureList[o->texture_index[j]]->e[1],
				//			 model->textureList[o->texture_index[j]]->e[2]);

				glNormal3f(model->normalList[o->normal_index[j]]->e[0],
						   model->normalList[o->normal_index[j]]->e[1],
						   model->normalList[o->normal_index[j]]->e[2]);

				glVertex3f(model->vertexList[ o->vertex_index[j]]->e[0],
						   model->vertexList[ o->vertex_index[j]]->e[1],
						   model->vertexList[ o->vertex_index[j]]->e[2]);
			}
		}
	glEnd();
}