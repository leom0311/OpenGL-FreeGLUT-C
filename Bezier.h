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

	int m_nMethod;

protected:
	PointF DeCasteljau_(const std::vector<PointF>& points, float t);
public:
	Bezier();
	Bezier(int n);
	~Bezier();

	void setMethod(int method);
	int getMethod();
	void setDegree(int n);
	int getDegree();
	void setControlPoints(std::vector<PointF> points);
	std::vector<PointF> getControlPoints();


	float B(int n, int i, float t);

	void BezPoint(int n, float t, PointF& ret);
	PointF CasteljauPoint(std::vector<PointF>points, float t);
	std::pair<std::vector<PointF>, std::vector<PointF>> CasteljauSubdividePoints(const std::vector<PointF> points, float t);

	void clickMouse(int state, int x, int y);
	void moveMouse(int x, int y);

	bool isMovingPoint();
	PointF newPoint();
	int movingPoint();
};

