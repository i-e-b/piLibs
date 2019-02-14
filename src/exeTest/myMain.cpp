#include "../libLog/piLog.h"
#include "../libMath/piVecTypes.h"

using namespace piLibs;

//-----------------
void* piMainCrashHandlerFunc(void) { return nullptr; }
void* piMainMissingDLLHandlerFunc(void) { return nullptr; }

// test rotation matrix to quaternion
bool test1(void)
{
	const vec4d p = vec4d(-1.5, 2.5, -3.5, 0.0);
	for (int i = 0; i < 100; i++)
	{
		const mat4x4d m1 = setRotation4( float(i)+1.0, float(i/2)+2.0, float(i/3)+3.0);
		const quatd   q1 = fromMatrix(extractRotation3(m1));
		const vec4d   p1 = m1 * p;
		const vec3d   p2 = q1 * p.xyz();
		if (distance(p1.xyz(), p2) > 0.0001)
			return false;
	}
	return true;
}

// test quaternion to rotation matrix
bool test2(void)
{
	const vec4d p = vec4d(-1.5, 2.5, -3.5, 0.0);
	for (int i = 0; i < 100; i++)
	{
		const mat4x4d m1 = setRotation4(float(i) + 1.0, float(i / 2) + 2.0, float(i / 3) + 3.0);
		const quatd   q1 = fromMatrix(extractRotation3(m1));
		const mat4x4d m2 = setRotation4(q1);
		const vec4d   p1 = m1 * p;
		const vec4d   p2 = m2 * p;
		if (distance(p1.xyz(), p2.xyz()) > 0.0001)
			return false;
	}
	return true;
}

// test matrix to transform
bool test3(void)
{
	const vec4d p = vec4d(-1.5, 2.5, -3.5, 1.0);
	for (int i = 0; i < 100; i++)
	{
		const mat4x4d m1 = setTranslation(1.0, 2.0, 3.0+0.01*float(i)) * setRotation4(float(i) + 1.0, float(i / 2) + 2.0, float(i / 3) + 3.0) * setScale4(4.0+float(i));
		const trans3d t1 = fromMatrix(m1);
		const vec4d   p1 = m1 * p;
		const vec4d   p2 = t1 * p;
		if (distance(p1.xyz(), p2.xyz()) > 0.0001)
			return false;
	}
	return true;
}

// test transform to matrix
bool test4(void)
{
	const vec4d p = vec4d(-1.5, 2.5, -3.5, 1.0);
	for (int i = 0; i < 100; i++)
	{
		const mat4x4d m1 = setTranslation(1.0, 2.0, 3.0 + 0.01*float(i)) * setRotation4(float(i) + 1.0, float(i / 2) + 2.0, float(i / 3) + 3.0) * setScale4(4.0 + float(i));
		const trans3d t1 = fromMatrix(m1);
		const mat4x4d m2 = toMatrix(t1);
		const vec4d   p1 = m1 * p;
		const vec4d   p2 = m2 * p;
		if (distance(p1.xyz(), p2.xyz()) > 0.0001)
			return false;
	}
	return true;
}

// test concatenate quaterions
bool test5(void)
{
	const vec3d p = vec3d(-1.5, 2.5, -3.5);
	for (int i = 0; i < 100; i++)
	{
		const mat4x4d m1 = setRotation4(float(i) + 1.0, float(i / 2) + 2.0, float(i / 3) + 3.0);
		const mat4x4d m2 = setRotation4(float(i * 2) + 3.0, float(i) + 1.0, float(i / 2) + 5.0);
		const quatd   q1 = fromMatrix(extractRotation3(m1));
		const quatd   q2 = fromMatrix(extractRotation3(m2));
		const quatd   q21 = q2*q1;

		const vec3d   p1 = q2*(q1*p);
		const vec3d   p2 = q21*p;

		if (distance(p1, p2) > 0.0001)
			return false;
	}
	return true;
}

// test concatenate transforms
bool test6(void)
{
	const vec4d p = vec4d(-1.5, 2.5, -3.5, 1.0);
	for (int i = 0; i < 100; i++)
	{
		const mat4x4d m1 = setTranslation(1.0, 2.0, 3.0 + 0.01*float(i)) * setRotation4(float(i) + 1.0, float(i / 2) + 2.0, float(i / 3) + 3.0) * setScale4(4.0 + float(i));
		const mat4x4d m2 = setTranslation(4.0, 1.0 - float(i), 2.0 + 0.01*float(i)) * setRotation4(float(i)*0.52 + 0.5, float(i)*1.1 + 1.0, float(i)*3.1 + 1.0) * setScale4(1.0 + float(i)*0.2);
		const trans3d t1 = fromMatrix(m1);
		const trans3d t2 = fromMatrix(m2);
		const trans3d t21 = t2*t1;

		const vec4d   p1 = t2*(t1*p);
		const vec4d   p2 = t21*p;

		if (distance(p1.xyz(), p2.xyz()) > 0.0001)
			return false;
	}
	return true;
}

// test inverse quaterions
bool test7(void)
{
	const vec3d p = vec3d(-1.5, 2.5, -3.5);
	for (int i = 0; i < 100; i++)
	{
		const mat4x4d m1 = setRotation4(float(i) + 1.0, float(i / 2) + 2.0, float(i / 3) + 3.0);
		const quatd   q1 = fromMatrix(extractRotation3(m1));
		const quatd   q2 = invert(q1);
		const quatd   q21 = q2*q1;

		const vec3d   p1 = q2*(q1*p);
		const vec3d   p2 = q21*p;

		if (distance(p1, p) > 0.0001)
			return false;
		if (distance(p2, p) > 0.0001)
			return false;
	}
	return true;
}


// test inverse transforms
bool test8(void)
{
	const vec4d p = vec4d(-1.5, 2.5, -3.5,1.0);
	for (int i = 0; i < 100; i++)
	{
		const mat4x4d m1 = setTranslation(1.0, 2.0, 3.0 + 0.01*float(i)) * setRotation4(float(i) + 1.0, float(i / 2) + 2.0, float(i / 3) + 3.0) * setScale4(4.0 + float(i));
		const trans3d q1 = fromMatrix(m1);
		const trans3d q2 = invert(q1);
		const trans3d q21 = q2*q1;

		const vec4d   p1 = q2*(q1*p);
		const vec4d   p2 = q21*p;

		if (distance(p1.xyz(), p.xyz()) > 0.0001)
			return false;
		if (distance(p2.xyz(), p.xyz()) > 0.0001)
			return false;
	}
	return true;
}

int piMainFunc(const wchar_t* path, const wchar_t** args, int numArgs, void* instance)
{
	piLog mLog;

	if (!mLog.Init(L"debug.txt", PILOG_STDOUT, nullptr))
	{
		mLog.End();
		return 0;
	}

	bool res;

	res = test1(); if (res) mLog.Printf(LT_MESSAGE, L"OK"); else  mLog.Printf(LT_ERROR, L"Failed");
	res = test2(); if (res) mLog.Printf(LT_MESSAGE, L"OK"); else  mLog.Printf(LT_ERROR, L"Failed");
	res = test3(); if (res) mLog.Printf(LT_MESSAGE, L"OK"); else  mLog.Printf(LT_ERROR, L"Failed");
	res = test4(); if (res) mLog.Printf(LT_MESSAGE, L"OK"); else  mLog.Printf(LT_ERROR, L"Failed");
	res = test5(); if (res) mLog.Printf(LT_MESSAGE, L"OK"); else  mLog.Printf(LT_ERROR, L"Failed");
	res = test6(); if (res) mLog.Printf(LT_MESSAGE, L"OK"); else  mLog.Printf(LT_ERROR, L"Failed");
	res = test7(); if (res) mLog.Printf(LT_MESSAGE, L"OK"); else  mLog.Printf(LT_ERROR, L"Failed");
	res = test8(); if (res) mLog.Printf(LT_MESSAGE, L"OK"); else  mLog.Printf(LT_ERROR, L"Failed");

	mLog.End();
	return 1;
}
