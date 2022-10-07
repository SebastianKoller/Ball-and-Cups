#include "Curve.hpp"

Curve::Curve() {
	nPts = 0;
}

Curve::~Curve() {
}

void Curve::reset() {
	nPts = 0;
}

void Curve::drawCurve()
{
	GLfloat ctrlpoints[nPts][3];
	for (int i = 0; i < nPts; i++)
	{
		ctrlpoints[i][0] = Pts[i].x;
		ctrlpoints[i][1] = Pts[i].y;
		ctrlpoints[i][2] = Pts[i].z;
	}
	glColor3f(1.0, 1.0, 0.0);


	glEnable(GL_MAP1_VERTEX_3);
	for (int i = 0; i < nPts; i += 1)
	{
		glMap1f(GL_MAP1_VERTEX_3,0.,1.,3,nPts,&ctrlpoints[i][0]);
		glMapGrid1f(30,0.,1.);
		glEvalMesh1(GL_LINE,0,30);
	}
	/*
	for (int i = 0; (i + 3) < nPts; i += 3)
	{
		// The evaluator with a stride of 3 and an order of 4
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[i][0]);

		glMapGrid1f(100, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 100);
	}
	glEnd();
	*/
}

void Curve::set2DView(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(left, right, bottom, top);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	  glColor3f(1.0, 0.0, 0.0);  // x-axis red
	  glVertex2f(left/2, 0.0);
	  glVertex2f(right/2, 0.0);

	  glColor3f(0.0, 1.0, 0.0); // x-axis green
	  glVertex2f(0.0, bottom/2);
	  glVertex2f(0.0, top/2);
	glEnd();
}
