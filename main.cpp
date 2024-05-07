#include "common.h"
#include <stdlib.h>
#include <GL/glut.h>
#include "Callbacks.h"
#include "Bezier.h"

Bezier g_Bezier;

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	
	g_Bezier.setDegree(3);
	std::vector<PointF> points;
	points.push_back(PointF(0.0f, 0.0f));
	points.push_back(PointF(0.8f, 0.0f));
	points.push_back(PointF(0.8f, 0.8f));
	points.push_back(PointF(0.0f, 0.8f));
	g_Bezier.setControlPoints(points);

	glutCreateWindow("FreeGLUT");
	glutKeyboardFunc(&keyboard);
	glutMouseFunc(&mouse);
	glutDisplayFunc(&display);
	glutMotionFunc(&motion);
	glutReshapeFunc(&reshape);

	createMenu();
	glutMainLoop();

	return 0;
}
