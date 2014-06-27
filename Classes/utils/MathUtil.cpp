#include <MathUtil.h>
#include <math.h>

brid::MathUtil::MathUtil()
{
}


brid::MathUtil::~MathUtil()
{
}

float brid::MathUtil::fixNumber(float num, float min, float range)
{
	num = (int)num % (int)range;
	if (num < min)
		return num + range;
	return num;
}

float brid::MathUtil::fixAngle(float angle)
{
	return brid::MathUtil::fixNumber(angle, 0, 360);
}

unsigned int brid::MathUtil::getFactorial(unsigned int num)
{
	if (num == 0) return 1;
	return num * brid::MathUtil::getFactorial(num - 1);
}

float brid::MathUtil::getSlope(float x1, float x2, float y1, float y2)
{
	float slope = (y1 - y2) / (x1 - x2);
	return slope;
}

float brid::MathUtil::rds2dgs(float radians)
{
	return fixAngle(radians * 180 / M_PI);
}

float brid::MathUtil::dgs2rds(float degrees)
{
	return degrees * M_PI / 180;
}

void brid::MathUtil::threeSidesMathAngle(vector<float>&vect, float a, float b, float c)
{
	float cosA = (c * c + b * b - a * a) / (2 * b * c);
	float A = brid::MathUtil::rds2dgs(acos(cosA));

	float cosB = (a * a + c * c - b * b) / (2 * a * c);
	float B = brid::MathUtil::rds2dgs(acos(cosB));

	float cosC = (a * a + b * b - c * c) / (2 * a * b);
	float C = brid::MathUtil::rds2dgs(acos(cosC));

	vect.clear();
	vect.push_back(A);
	vect.push_back(B);
	vect.push_back(C);
}

void brid::MathUtil::rotate(vector<float>&vect, float cx, float cy, 
									float tx, float ty, 
									float angle, bool reverse)
{
	float x;
	float y;
	float dx = tx - cx;
	float dy = ty - cy;
	float c = cos(brid::MathUtil::dgs2rds(angle));
	float s = sin(brid::MathUtil::dgs2rds(angle));
	if (reverse)
	{
		x = dx * c + dy * s + cx;
		y = dy * c - dx * s + cy;
	}
	else
	{
		x = dx * c - dy * s + cx;
		y = dy * c + dx * s + cy;
	}
	vect.clear();
	vect.push_back(x);
	vect.push_back(y);
}

float brid::MathUtil::sineLaw( float angle, float line )
{
	return line / sin(angle) / 2;
}

Point brid::MathUtil::triangleCentroid( Point a, Point b, Point c )
{
	return ccp((a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3);
}

unsigned int brid::MathUtil::arithmeticSequenceIndex( unsigned int sn, unsigned int d )
{
	//前n项和公式为：Sn=n×a1+n×(n-1)×(d/2); 
	//等差数列分解因式公式
	//d/2×n^2-(1-d/2)×n-dis = 0
	//一元二次方程表示法 ax^2+bx+c = 0;
	//一元二次方程 带入公式法  x = -b+Math.sqrt(b^2-4ac)/2a;
	float hd = d * .5;
	float a = hd;
	float b = 1 - hd;
	int c = -(int)sn;
	return ( -b + sqrt(b * b - (4 * a * c))) / (2 * a);
}

float brid::MathUtil::arithmeticSequenceIndexValue( unsigned int sn, unsigned int d )
{
	unsigned int n = brid::MathUtil::arithmeticSequenceIndex(sn, d);
	return (n + 1) * d - (d - 1);
}

Point brid::MathUtil::triangleCircumscribedCircleCenter( Point a, Point b, Point c )
{
	float axp =  pow(a.x, 2);
	float bxp =  pow(b.x, 2);
	float cxp =  pow(c.x, 2);

	float ayp =  pow(a.y, 2);
	float byp =  pow(b.y, 2);
	float cyp =  pow(c.y, 2);

	float x = ((b.y - a.y) * (cyp - ayp + cxp - axp) - (c.y - a.y) * (byp - ayp + bxp - axp)) / 
		(2 * (c.x - a.x) * (b.y - a.y) - 2 * ((b.x - a.x) * (c.y - a.y)));

	float y = ((b.x - a.x) * (cxp - axp + cyp - ayp) - (c.x - a.x) * (bxp - axp + byp - ayp)) / 
		(2 * (c.y - a.y) * (b.x - a.x) - 2 * ((b.y - a.y) * (c.x - a.x)));
	return ccp(x, y);
}

float brid::MathUtil::distance( float x1, float y1, float x2, float y2 )
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

unsigned int brid::MathUtil::getIntLength( unsigned int num )
{
	return log10(num) + 1;
}

bool brid::MathUtil::isInsideTriangle( Point a, Point b, Point c, Point p )
{
	float planeAB = (a.x - p.x) * (b.y - p.y) - (b.x - p.x) * (a.y - p.y);
	float planeBC = (b.x - p.x) * (c.y - p.y) - (c.x - p.x) * (b.y - p.y);
	float planeCA = (c.x - p.x) * (a.y - p.y) - (a.x - p.x) * (c.y - p.y);
	return sign(planeAB) == sign(planeBC) && sign(planeBC) == sign(planeCA);
}

int brid::MathUtil::sign( float n )
{
	return abs(n) / n;
}

float brid::MathUtil::triangleArea( Point a, Point b, Point c )
{
	return (c.x * b.y - b.x * c.y) - (c.x * a.y - a.x * c.y) + (b.x * a.y - a.x * b.y);
}

bool brid::MathUtil::isInsideSquare( Point a, Point b, Point c, Point d, Point p )
{
	if (triangleArea(a, b, p) > 0 || 
		triangleArea(b, c, p) > 0 || 
		triangleArea(c, d, p) > 0 || 
		triangleArea(d, a, p) > 0) 
		return false;
	return true;
}









