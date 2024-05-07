#include "Bezier.h"
#include <math.h>
#include "common.h"

int lm(int n) {
	int ret = 1;
	while (n) {
		ret *= n;
		n--;
	}
	return ret;
}

PointF::PointF() {
	x = 0.0f;
	y = 0.0f;
}

PointF::PointF(float x_, float y_) {
	x = x_;
	y = y_;
}

Bezier::Bezier() {
	m_nSelectedPoint = -1;
	m_nMethod = METHOD_BezPoint;
}

Bezier::Bezier(int n) {
	m_N = n;
	m_nSelectedPoint = -1;
	m_nMethod = METHOD_BezPoint;
}

Bezier::~Bezier() {
}

void Bezier::setDegree(int n) {
	m_N = n;
}

int Bezier::getDegree() {
	return m_N;
}

void Bezier::setControlPoints(std::vector<PointF> points) {
	m_vControlPoints.clear();
	m_vControlPoints = points;
}

std::vector<PointF> Bezier::getControlPoints() {
	return m_vControlPoints;
}

float Bezier::B(int n, int i, float t) {
	return float(lm(n)) / (1.0 * lm(i) * lm(n - i)) * pow(1 - t, n - i) * pow(t, i);
}

void Bezier::BezPoint(int n, float t, PointF& ret) {
	ret.x = 0.0;
	ret.y = 0.0;
	for (int i = 0; i <= n; i++) {
		float p_x = m_vControlPoints[i].x;
		float p_y = m_vControlPoints[i].y;
		ret.x += B(n, i, t) * p_x;
		ret.y += B(n, i, t) * p_y;
	}
}

PointF Bezier::CasteljauPoint(std::vector<PointF>points, float t) {
	if (points.size() == 1) {
		return points[0];
	}
	std::vector<PointF> cp;
	for (int i = 0; i < points.size() - 1; ++i) {
		float x = (1 - t) * points[i].x + t * points[i + 1].x;
		float y = (1 - t) * points[i].y + t * points[i + 1].y;
		cp.push_back(PointF(x, y));
	}
	return CasteljauPoint(cp, t);
}

PointF Bezier::DeCasteljau_(const std::vector<PointF>& points, float t) {
	std::vector<PointF> temp(points);
	int n = temp.size();
	for (int j = n - 1; j > 0; j--) {
		for (int i = 0; i < j; i++) {
			temp[i].x = (1 - t) * temp[i].x + t * temp[i + 1].x;
			temp[i].y = (1 - t) * temp[i].y + t * temp[i + 1].y;
		}
	}
	return temp[0];
}

std::pair<std::vector<PointF>, std::vector<PointF>> Bezier::CasteljauSubdividePoints(const std::vector<PointF> points, float t) {
	std::vector<PointF> curve1, curve2;
	int n = points.size();
	for (int i = 0; i <= n; i++) {
		curve1.push_back(DeCasteljau_(points, i / static_cast<float>(n)));
		curve2.push_back(DeCasteljau_(points, (i + n) / static_cast<float>(n)));
	}
	return { curve1, curve2 };
}

void Bezier::clickMouse(int state, int x, int y) {
	printf("click mouse > state: %d, x: %d, y: %d\n", state, x, y);
	if (state) {
		// release
		if (m_nSelectedPoint != -1) {
			m_vControlPoints[m_nSelectedPoint].x = m_newPoint.x;
			m_vControlPoints[m_nSelectedPoint].y = m_newPoint.y;
			m_nSelectedPoint = -1;
		}
	}
	else {
		// press
		for (int i = 0; i < m_vControlPoints.size(); i++) {
			int pos_x = m_vControlPoints[i].x * (WIN_WIDTH / 2) + WIN_WIDTH / 2;
			int pos_y = WIN_HEIGHT / 2 - m_vControlPoints[i].y * (WIN_HEIGHT / 2);

			int w = WIN_WIDTH * CIRCLE_RADIUS * 2;
			int h = WIN_HEIGHT * CIRCLE_RADIUS * 2;

			if (x >= (pos_x - w / 2) &&
				x <= (pos_x + w / 2) &&
				y >= (pos_y - h / 2) &&
				y <= (pos_y + h / 2)) {
				m_nSelectedPoint = i;
				printf("	select: %d\n", i);
				break;
			}
		}
	}
}

void Bezier::moveMouse(int x, int y) {
	if (m_nSelectedPoint == -1) {
		return;
	}

	int x_ = x - WIN_WIDTH / 2;
	int y_ = WIN_HEIGHT / 2 - y;

	m_newPoint.x = 1.0 * x_ / (WIN_WIDTH / 2);
	m_newPoint.y = 1.0 * y_ / (WIN_HEIGHT / 2);
}

bool Bezier::isMovingPoint() {
	return m_nSelectedPoint != -1;
}

PointF Bezier::newPoint() {
	return m_newPoint;
}

int Bezier::movingPoint() {
	return m_nSelectedPoint;
}

void Bezier::setMethod(int method) {
	m_nMethod = method;
}
int Bezier::getMethod() {
	return m_nMethod;
}
