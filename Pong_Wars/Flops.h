
#pragma once
#ifndef FLOPS_H_INCLUDED
#define FLOPS_H_INCLUDED

#include <cmath>


const float MY_PI = 3.14159265359;

static bool floatsAlmostEqual(float f0, float f1)
{
	if (abs(f1 - f0) < 0.00000007)
	{
		return true;
	}
	return false;
}

static float degreesToRadians(float deg)
{
	return (deg * MY_PI) / 180.0;
}

static float radiansToDegrees(float rad)
{
	return (rad * 180.0) / MY_PI;
}

// Basic Curving Stuff
static float linearHalf(float x)
{
	return 0.5f*x;
}

float inline lerp(float start, float end, float alpha)
{
	return start + alpha *(end - start); //(1 - alpha) * start + alpha * end;
}

float inline quadBezier(float start, float mid, float end, float alpha)
{
	float mid1 = lerp(start, mid, alpha);

	float mid2 = lerp(mid, end, alpha);

	return lerp(lerp(start, mid, alpha), 
				lerp(mid, end, alpha), 
				alpha);
}

static float hermiteSpline(float start, float end, float tangent0, float tangent1, float alpha)
{
	float a_squr = alpha*alpha;
	float a_cube = alpha*a_squr;

	float h00 = 2 * a_cube - 3 * a_squr + 1;
	float h01 = -2 * a_cube + 3 * a_squr;
	float h10 = a_cube - 2 * a_squr + alpha;
	float h11 = a_cube - a_squr;

	return h00 * start + h10 * tangent0 + h01 * end + h11 * tangent1;
}


static float cardinalSpline(float start, float mid, float end, float tightness, float alpha)
{
	float tangent0 = (mid - start) * tightness;
	float tangent1 = (end - mid) * tightness;

	float a_squr = alpha*alpha;
	float a_cube = alpha*a_squr;

	float h00 = 2 * a_cube - 3 * a_squr + 1;
	float h01 = -2 * a_cube + 3 * a_squr;
	float h10 = a_cube - 2 * a_squr + alpha;
	float h11 = a_cube - a_squr;

	return h00 * start + h10 * tangent0 + h01 * mid + h11 * tangent1;
}

static float catRomSpline(float start, float end, float alpha)
{
	return 0;
}


#endif