#pragma once
#ifndef _RANDOM_INIT_
#define _RANDOM_INIT_
#include "cocos2d.h"
USING_NS_CC;
#define min(a,b)            (((a) < (b)) ? (a) : (b))
class Random
{
public:
	Random(void);
	~Random(void);

	/**
	* ��ʼ���������
	*/
	static void initRandomSeed();

	/**
	* ��ʼ���������
	* @param seed	���Ӳ�����2����ͬ���ӿɴ�����ͬ������У�ÿ�α������ɶ���ͬһ�����С�
	*/
	static void initRandomSeed(unsigned int seed);

	 /**
     * ���� a - b֮����������������  max(a, b)
     * @param a
     * @param b
     * @return ���� a < b, [a, b)
     */
	static float randomFloat(float a, float b);

	/**
     * ����a �� bֱ���������������� a �� b
     * @param a
     * @param b
     * @return [a, b] ֱ�ӵ��������
     */
	static int randomInt(int a, int b);

	/**
     * �� start �� stop֮��ȡһ�����������������stepָ������� ���������ϴ�Ķ˵㣨start��stop�ϴ��һ����
     * �� 
     * Random::randrange(1, 10, 3) 
     * �򷵻صĿ�����   1 ��  4 ��  7  , ע�� �����治�᷵��10����Ϊ��10�Ǵ�˵�
     * 
     * @param start
     * @param stop
     * @param step
     * @return ���� start < stop,  [start, stop) �����ڵ��������
     */
	static int randrange(int start, int stop, unsigned int step=1);

	/**
	 * �������
	 * @param	chance ����
	 * @return	�����Ƿ���
	 */
	static bool boolean(float chance=.5f);
};
#endif
