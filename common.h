#pragma once

#define WIN_WIDTH	(600)
#define WIN_HEIGHT	(600)

#define CIRCLE_RADIUS (0.02)


enum {
	METHOD_BezPoint = 0,
	METHOD_CasteljauPoint,
	METHOD_CasteljauSubdividePoints,
	METHOD_FlagA,
	METHOD_FlagB,
	METHOD_FlagC
};

