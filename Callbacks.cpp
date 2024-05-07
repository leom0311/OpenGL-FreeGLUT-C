#include "common.h"
#include <stdlib.h>
#include <GL/glut.h>
#include "Callbacks.h"
#include <stdio.h>
#include <math.h>
#include "Bezier.h"

#define PI (3.14f)

extern Bezier g_Bezier;

void mouse(int button, int state, int x, int y) {
    if (button != 0) {
        return;
    }

    // when clicked left button
    g_Bezier.clickMouse(state, x, y);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '\x1B': {
        exit(0);
        break;
    }
    }
}

void motion(int x, int y) {
    g_Bezier.moveMouse(x, y);
    glutPostRedisplay();
}

void drawCircle(float cx, float cy, float r, int step) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < step; i++) {
        float theta = 2.0f * PI * float(i) / float(step);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (float t = 0; t < 1; t += 0.01) {
        PointF pos;
        g_Bezier.BezPoint(g_Bezier.getDegree(), t, pos);
        glVertex2f(pos.x, pos.y);
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    std::vector<PointF> positions = g_Bezier.getControlPoints();
    for (int i = 0; i < positions.size(); i++) {
        if (g_Bezier.isMovingPoint() && g_Bezier.movingPoint() == i) {
            continue;
        }
        drawCircle(positions[i].x, positions[i].y, CIRCLE_RADIUS, 32);
    }

    
    if (g_Bezier.isMovingPoint()) {
        glColor3f(1.0f, 1.0f, 1.0f);
        drawCircle(g_Bezier.newPoint().x, g_Bezier.newPoint().y, CIRCLE_RADIUS, 32);
    }
    glFlush();

    
}

void reshape(int w, int h) {
    glutReshapeWindow(WIN_WIDTH, WIN_HEIGHT);
}

