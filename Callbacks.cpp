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
    if (g_Bezier.getMethod() <= METHOD_CasteljauSubdividePoints) {
        g_Bezier.clickMouse(state, x, y);
    }
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
    if (g_Bezier.getMethod() <= METHOD_CasteljauSubdividePoints) {
        g_Bezier.moveMouse(x, y);
        glutPostRedisplay();
    }
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

void uaeFlag() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6, 0.3);
    glVertex2f(0.1, 0.3);
    glVertex2f(0.1, 0.2);
    glVertex2f(-0.6, 0.2);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6, 0.2);
    glVertex2f(0.1, 0.2);
    glVertex2f(0.1, 0.1);
    glVertex2f(-0.6, 0.1);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6, 0.1);
    glVertex2f(0.1, 0.1);
    glVertex2f(0.1, 0.0);
    glVertex2f(-0.6, 0.0);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.1, 0.3);
    glVertex2f(0.3, 0.3);
    glVertex2f(0.3, 0.0);
    glVertex2f(0.1, 0.0);
    
    glEnd();
}

void uaeFlagCurves() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();
    
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < 3; i++) {
            if (i == 0) {
                glColor3f(0.0f, 1.0f, 0.0f);
            }
            else if (i == 1) {
                glColor3f(0.95f, 1.0f, 1.0f);
            }
            else {
                glColor3f(0.0f, 0.0f, 0.0f);
            }
            
            Bezier bezier;
            bezier.setDegree(4);
            std::vector<PointF> points;
            points.push_back(PointF(-0.3, 0.3 - i * 0.2));
            points.push_back(PointF(-0.1, 0.22 - i * 0.2));
            points.push_back(PointF(0.1, 0.3 - i * 0.2));
            points.push_back(PointF(0.3, 0.32 - i * 0.2));
            points.push_back(PointF(0.5, 0.3 - i * 0.2));
            bezier.setControlPoints(points);
            for (float t = 0; t < 1; t += 0.002) {
                PointF pos;
                bezier.BezPoint(bezier.getDegree(), t, pos);
                glVertex2f(pos.x, pos.y);

                Bezier bezier_0;
                bezier_0.setDegree(2);

                std::vector<PointF> points_0;
                points_0.push_back(PointF(pos.x - 0.015 * (t > 0.5 && i == 0), pos.y));
                points_0.push_back(PointF(pos.x + 0.025, pos.y - 0.1));
                points_0.push_back(PointF(pos.x - 0.015 * (t > 0.5 && i == 2), pos.y - 0.2));
                bezier_0.setControlPoints(points_0);

                for (float tt = 0; tt < 1; tt += 0.002) {
                    PointF pos_0;
                    bezier_0.BezPoint(bezier_0.getDegree(), tt, pos_0);
                    glVertex2f(pos_0.x, pos_0.y);
                }
            }
        }
    }
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        Bezier bezier;
        bezier.setDegree(2);
        std::vector<PointF> points;
        points.push_back(PointF(-0.5, 0.3));
        points.push_back(PointF(-0.4, 0.325));
        points.push_back(PointF(-0.3, 0.3));
        bezier.setControlPoints(points);
        for (float t = 0; t < 1; t += 0.005) {
            PointF pos;
            bezier.BezPoint(bezier.getDegree(), t, pos);
            glVertex2f(pos.x, pos.y);

            Bezier bezier_0;
            bezier_0.setDegree(2);

            std::vector<PointF> points_0;
            points_0.push_back(PointF(pos.x, pos.y));
            points_0.push_back(PointF(pos.x + 0.05, pos.y - 0.3));
            points_0.push_back(PointF(pos.x, pos.y - 0.6));
            bezier_0.setControlPoints(points_0);

            for (float tt = 0; tt < 1; tt += 0.005) {
                PointF pos_0;
                bezier_0.BezPoint(bezier_0.getDegree(), tt, pos_0);
                glVertex2f(pos_0.x, pos_0.y);
            }
        }
    }
    glEnd();
}

void uaeFlagSurfaces() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    glBegin(GL_POINTS);
    {
        for (int i = 0; i < 3; i++) {
            if (i == 0) {
                glColor3f(0.0f, 1.0f, 0.0f);
            }
            else if (i == 1) {
                glColor3f(0.95f, 1.0f, 1.0f);
            }
            else {
                glColor3f(0.0f, 0.0f, 0.0f);
            }

            Bezier bezier;
            bezier.setDegree(4);
            std::vector<PointF> points;
            points.push_back(PointF(-0.3, 0.75 - i * 0.2));
            points.push_back(PointF(-0.2, 0.8 - i * 0.2));
            points.push_back(PointF(0.1, 0.6 - i * 0.2));
            points.push_back(PointF(0.2, 0.4 - i * 0.2));
            points.push_back(PointF(0.5, 0.6 - i * 0.2));
            bezier.setControlPoints(points);
            for (float t = 0; t < 1; t += 0.002) {
                PointF pos;
                bezier.BezPoint(bezier.getDegree(), t, pos);
                glVertex2f(pos.x, pos.y);

                Bezier bezier_0;
                bezier_0.setDegree(2);

                std::vector<PointF> points_0;
                points_0.push_back(PointF(pos.x, pos.y));
                points_0.push_back(PointF(pos.x + 0.025, pos.y - 0.1));
                points_0.push_back(PointF(pos.x, pos.y - 0.2));
                bezier_0.setControlPoints(points_0);

                for (float tt = 0; tt < 1; tt += 0.002) {
                    PointF pos_0;
                    bezier_0.BezPoint(bezier_0.getDegree(), tt, pos_0);
                    glVertex2f(pos_0.x, pos_0.y);
                }
            }
        }
    }

    {        
        glColor3f(1.0f, 0.0f, 0.0f);
            
        Bezier bezier;
        bezier.setDegree(2);
        std::vector<PointF> points;
        points.push_back(PointF(-0.55, 0.7));
        points.push_back(PointF(-0.35, 0.77));
        points.push_back(PointF(-0.3, 0.75));
        bezier.setControlPoints(points);
        for (float t = 0; t < 1; t += 0.002) {
            PointF pos;
            bezier.BezPoint(bezier.getDegree(), t, pos);
            glVertex2f(pos.x, pos.y);

            int step = 0;
            for (float _y = pos.y; _y >= pos.y - 0.6; _y -= 0.001) {
                glVertex2f(pos.x + 0.001 * step / 12.0, _y);
                step++;
            }
        }
    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        glColor3f(1.0f, 1.0f, 1.0f);

        Bezier bezier;
        bezier.setDegree(2);
        std::vector<PointF> points;
        points.push_back(PointF(-0.55, 0.7));
        points.push_back(PointF(-0.35,  0.4));
        points.push_back(PointF(-0.55, -0.1));
        bezier.setControlPoints(points);
        for (float t = 0; t < 1; t += 0.002) {
            PointF pos;
            bezier.BezPoint(bezier.getDegree(), t, pos);
            glVertex2f(pos.x, pos.y);
        }
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.3f, 0.05f);
    glVertex2f(-0.57, 0.75);
    glVertex2f(-0.55, 0.75);
    glVertex2f(-0.40, -0.6);
    glVertex2f(-0.42, -0.6);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.35, 1.0);
    glVertex2f(0.6, -1.0);
    glVertex2f(1.0, 1.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glEnd();

}

void drawBez() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (float t = 0; t < 1; t += 0.01) {
        PointF pos;
        if (g_Bezier.getMethod() == METHOD_BezPoint) {
            g_Bezier.BezPoint(g_Bezier.getDegree(), t, pos);
            glVertex2f(pos.x, pos.y);
        }
        else if (g_Bezier.getMethod() == METHOD_CasteljauPoint) {
            pos = g_Bezier.CasteljauPoint(g_Bezier.getControlPoints(), t);
            glVertex2f(pos.x, pos.y);
        }
        else if (g_Bezier.getMethod() == METHOD_CasteljauSubdividePoints) {
            std::pair<std::vector<PointF>, std::vector<PointF>> curves = g_Bezier.CasteljauSubdividePoints(g_Bezier.getControlPoints(), t);
            pos = g_Bezier.CasteljauPoint(curves.first, t);
            glVertex2f(pos.x, pos.y);
        }
    }
    glEnd();

    if (g_Bezier.getMethod() <= METHOD_CasteljauSubdividePoints) {
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
    }
    else if (g_Bezier.getMethod() == METHOD_FlagA) {
        uaeFlag();
    }
    else if (g_Bezier.getMethod() == METHOD_FlagB) {
        uaeFlagCurves();
    }
    else if (g_Bezier.getMethod() == METHOD_FlagC) {
        uaeFlagSurfaces();
    }

    // draw method text
    if (g_Bezier.getMethod() == METHOD_BezPoint) {
        drawText("BezPoint");
    }
    else if (g_Bezier.getMethod() == METHOD_CasteljauPoint) {
        drawText("CasteljauPoint");
    }
    else if (g_Bezier.getMethod() == METHOD_CasteljauSubdividePoints) {
        drawText("CasteljauSubdividePoints");
    }
    else if (g_Bezier.getMethod() == METHOD_FlagA) {
        drawText("FlagA");
    }
    else if (g_Bezier.getMethod() == METHOD_FlagB) {
        drawText("FlagB");
    }
    else if (g_Bezier.getMethod() == METHOD_FlagC) {
        drawText("FlagC");
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
    case METHOD_CasteljauSubdividePoints:
        g_Bezier.setMethod(METHOD_CasteljauSubdividePoints);
        break;
    case METHOD_FlagA:
        g_Bezier.setMethod(METHOD_FlagA);
        break;
    case METHOD_FlagB:
        g_Bezier.setMethod(METHOD_FlagB);
        break;
    case METHOD_FlagC:
        g_Bezier.setMethod(METHOD_FlagC);
        break;
    }
    
    glutPostRedisplay();
}


void createMenu() {
    glutCreateMenu(&menu);

    glutAddMenuEntry("BezPoint", METHOD_BezPoint);
    glutAddMenuEntry("CasteljauPoint", METHOD_CasteljauPoint);
    glutAddMenuEntry("CasteljauSubdividePoints", METHOD_CasteljauSubdividePoints);

    glutAddMenuEntry("FlagA", METHOD_FlagA);
    glutAddMenuEntry("FlagB", METHOD_FlagB);
    glutAddMenuEntry("FlagC", METHOD_FlagC);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

