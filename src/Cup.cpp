/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2021-10-15 (update)
 */
#include "Cup.hpp"
#include "Camera.hpp"
#include <stdio.h>

extern Camera myCamera;
extern Light myLight;
extern CullMode cullMode;
extern RenderMode renderMode;

Cup::Cup()
{
	smlRadius = 0.5;
	bigRadius = 0.75;
	height = 1.5;
	nSlices = 60;
}


void Cup::draw()
{

	//Temporary
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glPushMatrix();
    this->ctmMultiply();
    glScalef(s, s, s);
    glColor3f(1, 1, 1);

    float angle = 2.0f * M_PI / nSlices;
    double cur_angle = 0.0;

    // Choose texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);

    // Enable OpenGL Culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    // Draw Cylinder Face
    glBegin(GL_QUAD_STRIP);
    cur_angle = 0.0;

    for (int i = 0; i < nSlices + 1; i++)
    {
    	// Get norm for lighting
    	glNormal3f(smlRadius * cos(cur_angle), smlRadius * -sin(cur_angle), height);
    	// Draw texture
    	glTexCoord2f(cur_angle/(2*M_PI),1.0);
    	glVertex3f(smlRadius * cos(cur_angle), smlRadius * -sin(cur_angle), height);
    	glTexCoord2f(cur_angle/(2*M_PI),0.0);
    	glVertex3f(bigRadius * cos(cur_angle), bigRadius * -sin(cur_angle), 0.0);
    	cur_angle += angle;
	}
    glEnd();

    // Change texture
    glBindTexture(GL_TEXTURE_2D,7);

    //Disable Culling
    glDisable(GL_CULL_FACE);

    // Draw Top Circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0.0,0.0,height);
    glTexCoord2f(0,0);
    cur_angle = 0.0;
    for (int i = 0; i < nSlices + 1; i++)
    {
    	glTexCoord2f(1,1);
        glVertex3d(smlRadius * cos(cur_angle), smlRadius * sin(cur_angle), height);
        cur_angle += angle;
	}
    glEnd();

    // Disable Texturing
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
