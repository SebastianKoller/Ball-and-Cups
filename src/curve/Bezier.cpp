#include "Bezier.hpp"

extern GLint winWidth, winHeight;

Bezier::Bezier() {
	reset();
}

void Bezier::reset() {
	nCtrlPts = 0;
	nPts = 26;
}

/*  Compute binomial coefficients C for given value of n, output in GLint C[] */
void Bezier::binomialCoeffs(GLint n, GLint C[]) {
	double u = 1/n;
	double r;
	C[0] = pow(1.0-u, n);
	for (int i=1; i<=n; ++i)
	{
		u = i/n;
		r = u/1-u;
		C[i] = C[i-1] * (n-i+1) / i * r;
	}
}

/*  Compute Bezier point at u, and output in Point *bezPt */
void Bezier::computeBezPt(GLfloat u, GLint nCtrlPts, Point ctrlPts[], GLint C[], Point *bezPt)
{
	double b[nCtrlPts], x=0, y=0, z=0, r;
	int n = nCtrlPts - 1;
	if (u < .00001)
	{
		bezPt->x = ctrlPts[0].x;
		bezPt->y = ctrlPts[0].y;
		bezPt->z = ctrlPts[0].z;
	}
	else if (u > .99999)
	{
		bezPt->x =  ctrlPts[n].x;
		bezPt->y =  ctrlPts[n].y;
		bezPt->z =  ctrlPts[n].z;
	}
	else
	{
		r = u/1-u;
		b[0] = pow(1.0-u, n);
		for (int i=1; i<=n; ++i) {b[i] = b[i-1] * (n-i+1) / i * r;}

		for (int i=0; i<=n; ++i)
		{
			x = x + b[i] * ctrlPts[i].x;
			y = y + b[i] * ctrlPts[i].y;
			z = z + b[i] * ctrlPts[i].z;
		}
		bezPt->x = x; bezPt->y = y; bezPt->z = z;
	}

}

/*  Compute both Bezier point and tangent at u, and output in Point bezPt and Vector bezTan respectively*/
void Bezier::computeBezPtTan(GLfloat u, GLint nCtrlPts, Point ctrlPts[],
		GLint C[], Point *bezPt, Vector *bezTan)
{
	int n = nCtrlPts - 1, n1 = nCtrlPts - 2;
	double b[n], x=0, y=0, z=0, r;
	if (u < .00001)
	{
		bezPt->x = ctrlPts[1].x - ctrlPts[0].x;
		bezPt->y = ctrlPts[1].y - ctrlPts[0].y;
		bezPt->z = ctrlPts[1].z - ctrlPts[0].z;
	}
	else if (u > .99999)
	{
		bezPt->x = ctrlPts[n].x - ctrlPts[n1-1].x;
		bezPt->y = ctrlPts[n].y - ctrlPts[n1-1].y;
		bezPt->z = ctrlPts[n].z - ctrlPts[n1-1].z;
	}
	else
	{
		r = u/1.0-u;
		b[0] = pow(1.0 - u, n1);
		for (int i=1; i<n; ++i) { b[i] = b[i-1] * (n-i) / i * r; }

		for (int i=0; i<n; ++i)
		{
			x = x + b[i]*(ctrlPts[i+1].x-ctrlPts[i].x);
			y = y + b[i]*(ctrlPts[i+1].y-ctrlPts[i].y);
			z = z + b[i]*(ctrlPts[i+1].z-ctrlPts[i].z);
		}
		bezPt->x = x*n; bezPt->y = y*n; bezPt->z = z*n;

	}
	bezTan->x = x*n; bezTan->y = y*n; bezTan->z = z*n;
}


/* call to compute the sequence of points on Bezier curve for drawing Bezier curve */
void Bezier::computeBezCurvePts() {
	GLfloat u = 0;
	GLint C[nCtrlPts];
	binomialCoeffs(nCtrlPts-1, C);
	for (int k = 0; k < nPts; k++) {
		u = GLfloat(k) / GLfloat(nPts-1);
		computeBezPt(u, nCtrlPts, ctrlPts, C, &Pts[k]);
	}
}


/* call to compute the sequence of points and tangents on Bezier curve for mesh of rotating Bezier curve */
void Bezier::computeBezPtTan(GLint npts, Point pts[], Vector tangents[]) {
	GLfloat u = 0;
	GLint C[nCtrlPts];
	binomialCoeffs(nCtrlPts-1, C);
	for (int k = 0; k < npts; k++) {
		u = GLfloat(k) / GLfloat(npts-1);
		computeBezPtTan(u, nCtrlPts, ctrlPts, C, &pts[k],  &tangents[k]);
	}
}


void Bezier::drawCPts() {
	glPointSize(3.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < nCtrlPts; i++) {
		glVertex2f(ctrlPts[i].x, ctrlPts[i].y);
	}
	glEnd();
}

/* display Control points in 2D view */
void Bezier::displayCPts() {
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
}

/* display Control points and curve in 2D view */
void Bezier::display() {
	set2DView(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	drawCPts();
	drawCurve();
}


