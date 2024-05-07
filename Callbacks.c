#include <stdlib.h>
#include <GL/glut.h>
#include "Callbacks.h"
#include <stdio.h>
#include <math.h>

void mouse(int button, int state, int x, int y) {
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '\x1B': {
        exit(0);
        break;
    }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    float P0_x = 0, P1_x = 0.8, P2_x = 0.8, P3_x = 0;
    float P0_y = 0, P1_y = 0, P2_y = 0.8, P3_y = 0.0;

    glBegin(GL_POLYGON);
    for (float t = 0; t <= 1; t += 0.001) {
        float B_x = pow((1 - t), 3) * P0_x + 3 * pow((1 - t), 2) * t * P1_x + 3 * (1 - t) * pow(t, 2) * P2_x + pow(t, 3) * P3_x;
        float B_y = pow((1 - t), 3) * P0_y + 3 * pow((1 - t), 2) * t * P1_y + 3 * (1 - t) * pow(t, 2) * P2_y + pow(t, 3) * P3_y;
        glVertex2f(B_x, B_y);
    }
    glEnd();
  
    glFlush();
}
