

#include <stdlib.h>
#include <GL/glut.h>
#include "Callbacks.h"

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutCreateWindow("GLUT Test");
	glutKeyboardFunc(&keyboard);
	glutMouseFunc(&mouse);
	glutDisplayFunc(&display);

	glutMainLoop();

	return 0;
}
