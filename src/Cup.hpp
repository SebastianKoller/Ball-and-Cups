/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2021-10-06
 */
#ifndef CCUP_H
#define CCUP_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

#include "Camera.hpp"
#include "Light.hpp"

class Cup: public Shape {

protected:
	GLfloat smlRadius;
	GLfloat bigRadius;
	GLfloat height;
	GLint nSlices;

public:
	Cup();
	void draw();
};

#endif
