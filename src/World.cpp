#include "World.hpp"
#include "Cube.hpp"
#include "Cup.hpp"

using namespace std;

World::World() {
	reset();
}

World::~World(){
	Shape *obj;
	while (!objlist.empty()) {
		obj = objlist.front();
		objlist.pop_front();
		free(obj);
	}
}

void lineSegment(float x1, float y1, float z1, float x2, float y2, float z2) {
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void drawTable()
{
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,8);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-10.0f,-10.0f,0.0f);
	glTexCoord2f(2.0, 0.0); glVertex3f( 10.0f,-10.0f,0.0f);
	glTexCoord2f(2.0, 2.0); glVertex3f( 10.0f, 10.0f,0.0f);
	glTexCoord2f(0.0, 2.0); glVertex3f(-10.0f, 10.0f,0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void World::draw() {
//	glColor3f(1.0, 0.0, 0.0);
//	lineSegment(-2, 0, 0, 4, 0, 0); /* x-axis in red */
// 	glColor3f(0.0, 1.0, 0.0);
//	lineSegment(0, -2, 0, 0, 4, 0); /* y-axis in green */
//	glColor3f(0.0, 0.0, 1.0);
//	lineSegment(0, 0, -2, 0, 0, 4); /* z-axis in blue */

	drawTable();

	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  (*it)->draw();
    }


}

void World::reset(){

	Shape *obj;
	while (!objlist.empty()) {
		obj = objlist.front();
		objlist.pop_front();
		free(obj);
	}

	obj = NULL;

	obj = new Cup();
	obj->setId(1);
	obj->translate(1.5, -1.5, 0.0);
	objlist.push_back(obj);

	obj = new Cup();
	obj->setId(2);
	objlist.push_back(obj);

	obj = new Cup();
	obj->setId(3);
	obj->translate(-1.5, 1.5, 0.0);
	objlist.push_back(obj);

}

Shape* World::searchById(GLint i) {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  if ((*it)->getId() == i) return *it;
    }
	return NULL;
}

