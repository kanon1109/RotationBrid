#pragma once
#ifndef _MATH_UTIL_
#define _MATH_UTIL_
#include <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#ifndef CC_PLATFORM_WIN32
#include <math.h>
#endif
namespace bird
{
class MathUtil
{
public:
	MathUtil();
	~MathUtil();
	/**
	* �������� ��һ����Χ��
	* @param	num     ��Ҫ����������
	* @param	min     ��С�ķ�Χ
	* @param	range   ���Χ
	* @return  �����������
	*/
	static float fixNumber(float num, float min, float range);

	/**
	* ��׼���Ƕ�ֵ��������ĽǶ�ֵ���س�һ��ȷ������ 0 ~ 360 ֮������֡�
	*
	* <pre>
	* MathUtil::fixAngle(380); // ���� 20
	* MathUtil::fixAngle(-340); // ���� 20
	* </pre>
	*
	* �÷�������ɲ鿴 ��Flash MX ����봴��ʵ�֡��ĵ�69ҳ��
	*/
	static float fixAngle(float angle);

	/**
	* ��ȡ�׳�
	* @param	num     ��ײ��ֵ
	*/
	static unsigned int getFactorial(unsigned int num);

	/**
	* б�ʹ�ʽ
	* @param	x1 �����
	* @param	y1
	* @param	x2
	* @param	y2
	* @return  ��Ӧ��б��
	*/
	static float getSlope(float x1, float x2, float y1, float y2);

	/**
	* ����ת���ɽǶ�  radians -> degrees
	*
	* @param radians ����
	* @return ��Ӧ�ĽǶ�
	*/
	static float rds2dgs(float radians);

	/**
	* �Ƕ�ת���ɻ��� degrees -> radians
	*
	* @param degrees �Ƕ�
	* @return ��Ӧ�Ļ���
	*/
	static float dgs2rds(float degrees);

	/**
     * ��֪һ���Ƕ��Լ��Ƕȶ�Ӧ�ı߳� ��������������Բ�뾶R��2��
	 * ���ҹ�ʽ
	 * a/sinA=b/sinB=c/sinC=2R
     * @param	angle               �Ƕ�
     * @param	line                �Ƕ�Ӧ�ı䳤
     * @return  �������Բ�뾶R
     */
	static float sineLaw(float angle, float line);

	/**
     * ���ֱ������ϵ �����ε�����
     * @param	a      �����ζ���a
     * @param	b      �����ζ���b
     * @param	c      �����ζ���c
     * @return  �����ε�����
     */
	static Point triangleCentroid(Point a, Point b, Point c);

	/**
     * ���ֱ������ϵ ���������Բ��������
     * x = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) - 
     *      (y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) / 
     *      (2 * (x3 - x1) * (y2 - y1) - 2 * ((x2 - x1) * (y3 - y1))); 
     * 
     * y = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) - 
     *      (x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) / 
     *      (2 * (y3 - y1) * (x2 - x1) - 2 * ((y2 - y1) * (x3 - x1)));
     * @param	a      �����ζ���a
     * @param	b      �����ζ���b
     * @param	c      �����ζ���c
     * @return  ���Բ��������
     */
	static Point triangleCircumscribedCircleCenter(Point a, Point b, Point c);
	
	/**
	* ��֪3�����ĳ�߶�Ӧ�ĽǵĽǶ�
	* CosC=(a^2+b^2-c^2)/2ab
	* CosB=(a^2+c^2-b^2)/2ac
	* CosA=(c^2+b^2-a^2)/2bc
	*
	* @param	vect ���������Ӧ�ĽǶȵ�vect
	* @param	a ��
	* @param	b ��
	* @param	c ��
	*/
	static void MathUtil::threeSidesMathAngle(vector<float>&vect, float a, float b, float c);

	/**
	* ������ת��ʽ
	* @param	vect		����vect
	* @param	cx			���ĵ�x����
	* @param	cy			���ĵ�y����
	* @param	tx			��Ҫ��ת�������x����
	* @param	ty			��Ҫ��ת�������y����
	* @param	angle		��ת�Ƕ�
	* @param	reverse		�Ƿ���ʱ����ת
	*/
	static void MathUtil::rotate(vector<float>&vect, float cx, float cy,
									float tx, float ty,
									float angle, bool reverse);

	/**
	 * ���������͹�������Ȳ�������������Ӧ��ֵ 
	 * @param	sn  n��ĺ�
	 * @param	d   ����
	 * @return  ��������Ӧ��ֵ
	 */
	static float arithmeticSequenceIndexValue(unsigned int sn, unsigned int d);

	/**
	 * �������еĺ�����Ȳ�������Ĵ���
	 * @param	sn  n��ĺ�
	 * @param	d   ����
	 * @return  ��Ĵ���
	 */
	static unsigned int arithmeticSequenceIndex(unsigned int sn, unsigned int d);

	/**
	 * �������
	 * @param	x1	��1��x����
	 * @param	y1	��1��y����
	 * @param	x2	��2��x����
	 * @param	y2	��2��y����
	 * @return	2��֮��ľ���
	 */
	static float distance(float x1, float y1, float x2, float y2);

	/**
	 * ��ȡ������λ��	
	 * MathUtil::getIntLength(1000)  4;
	 * @param	num	����
	 * @return	λ��
	 */
	static unsigned int getIntLength(unsigned int num);

	
	//************************************
	// Method:    isInsideTriangle	�жϵ��Ƿ��������������ڲ�
	// Parameter: Point a			�����ε�a
	// Parameter: Point b			�����ε�b
	// Parameter: Point c			�����ε�c
	// Parameter: Point p			�����ε�p
	// Returns:   bool				�Ƿ����������ڲ�
	//************************************
	static bool isInsideTriangle(Point a, Point b, Point c, Point p);

	//************************************
	// Method:    triangleArea	�����������
	// Parameter: Point a		��a
	// Parameter: Point b		��b
	// Parameter: Point c		��c
	// Returns:   float			���
	//************************************
	static float triangleArea(Point a, Point b, Point c);

	//************************************
	// Method:    isInsideSquare	�жϵ��Ƿ���һ�����η�Χ�ڣ����ο���ת���������˳ʱ��
	// Parameter: Point a			��a
	// Parameter: Point b			��b
	// Parameter: Point c			��c
	// Parameter: Point d			��d
	// Parameter: Point p			������
	// Returns:   bool				�Ƿ���һ�����η�Χ��
	//************************************
	static bool isInsideSquare(Point a, Point b, Point c, Point d, Point p);

private:
	static int sign(float n);
};
}
#endif
