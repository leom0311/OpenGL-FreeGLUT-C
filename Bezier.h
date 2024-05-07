#pragma once

#include <vector>


class PointF{
public:
	float x;
	float y;
public:
	PointF();
	PointF(float x_, float y_);
};

class Bezier {

private:
	int m_N;
	int m_nSelectedPoint;
	PointF m_newPoint;
	std::vector<PointF> m_vControlPoints;
public:
	Bezier();
	Bezier(int n);
	~Bezier();

	void setDegree(int n);
	int getDegree();
	void setControlPoints(std::vector<PointF> points);

	std::vector<PointF> getControlPoints();


	float B(int n, int i, float t);

	void BezPoint(int n, float t, PointF& ret);
	void CasteljauPoint(float t);

	void clickMouse(int state, int x, int y);
	void moveMouse(int x, int y);

	bool isMovingPoint();
	PointF newPoint();
	int movingPoint();
};

