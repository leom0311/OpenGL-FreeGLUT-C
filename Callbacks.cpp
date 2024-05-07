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

void drawText(const char *text) {
    glRasterPos2f(-0.95, 0.9);
    for (int i = 0; text[i] != 0; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (float t = 0; t < 1; t += 0.01) {
        PointF pos;
        if (g_Bezier.getMethod() == METHOD_BezPoint) {
            g_Bezier.BezPoint(g_Bezier.getDegree(), t, pos);
        }
        else if (g_Bezier.getMethod() == METHOD_CasteljauPoint) {
            pos = g_Bezier.CasteljauPoint(g_Bezier.getControlPoints(), t);
        }
        glVertex2f(pos.x, pos.y);
    }
    glEnd();

    // draw control points
    glColor3f(1.0f, 0.0f, 0.0f);
    std::vector<PointF> positions = g_Bezier.getControlPoints();
    for (int i = 0; i < positions.size(); i++) {
        // skip current selecting control point
        if (g_Bezier.isMovingPoint() && g_Bezier.movingPoint() == i) {
            continue;
        }
        drawCircle(positions[i].x, positions[i].y, CIRCLE_RADIUS, 32);
    }
    
    // draw current selecting control point
    if (g_Bezier.isMovingPoint()) {
        glColor3f(1.0f, 1.0f, 1.0f);
        drawCircle(g_Bezier.newPoint().x, g_Bezier.newPoint().y, CIRCLE_RADIUS, 32);
    }

    // draw method text
    if (g_Bezier.getMethod() == METHOD_BezPoint) {
        drawText("BezPoint");
    }
    else if (g_Bezier.getMethod() == METHOD_CasteljauPoint) {
        drawText("CasteljauPoint");
    }
    glFlush();
}

void reshape(int w, int h) {
    glutReshapeWindow(WIN_WIDTH, WIN_HEIGHT);
}

void menu(int value) {
    switch (value) {
    case METHOD_BezPoint:
        g_Bezier.setMethod(METHOD_BezPoint);
        break;
    case METHOD_CasteljauPoint:
        g_Bezier.setMethod(METHOD_CasteljauPoint);
        break;
    }
    glutPostRedisplay();
}


void createMenu() {
    glutCreateMenu(&menu);

    glutAddMenuEntry("BezPoint", METHOD_BezPoint);
    glutAddMenuEntry("CasteljauPoint", METHOD_CasteljauPoint);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

