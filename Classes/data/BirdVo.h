#pragma once
#ifndef _BIRD_VO_
#define _BIRD_VO_
class BirdVo
{
public:
	BirdVo(void);
	~BirdVo(void);
	//����
	void update();
private:
	//�ٶ�
	float vx;
	float vy;
	//����
	float x;
	float y;
	//���ٶ�
	float angleSpeed;
	//���ٶȼ�ֵ
	float angleSpeedAdd;
};

#endif // !1
