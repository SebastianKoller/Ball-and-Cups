/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2021-10-15 (update)
 */
#include "Light.hpp"
#include "Matrix.hpp"
#include <stdio.h>

Light::Light(){
	reset();
}

void Light::reset(){
	mc.mat[0][3] = 0.0;
	mc.mat[1][3] = 0.0;
	mc.mat[2][3] = 4.0;
	I = 0.1;
	Rd = 1.0;
	size = 0.2;
	on = true;
}

void Light::Increment(GLfloat p, GLfloat ra, GLfloat rd){
	I += p;
	if (I < 0.03) I = 0.01;
	else if (I > 0.97 ) I = 1;
}

void Light::draw(){
	if(on == true){
		glPushMatrix();
		this->ctmMultiply();
		glColor3f(I, I, I);
		glutSolidSphere(size, 20, 20);
		glPopMatrix();

		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);

		// Create light
		GLfloat litePos[] = {mc.mat[0][3],mc.mat[0][3],mc.mat[0][3],1};
		glLightfv(GL_LIGHT1, GL_POSITION, litePos);

		// Light values
		GLfloat amb0[ ] = {0.0, 0.0, 0.0, 1.0};
		GLfloat diff0[ ] = {0.8, 0.8, 0.8, 1.0};
		GLfloat spec0[ ] = {1.0, 1.0, 1.0, 1.0};
		// Attach light values
		glLightfv(GL_LIGHT1, GL_AMBIENT, amb0);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diff0);
		glLightfv(GL_LIGHT1, GL_SPECULAR, spec0);

		glEnable(GL_LIGHT1);

	}
}
