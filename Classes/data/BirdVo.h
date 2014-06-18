#pragma once
#ifndef _BIRD_VO_
#define _BIRD_VO_
class BirdVo
{
public:
	BirdVo(void);
	~BirdVo(void);
	//更新
	void update();
private:
	//速度
	float vx;
	float vy;
	//坐标
	float x;
	float y;
	//角速度
	float angleSpeed;
	//角速度加值
	float angleSpeedAdd;
};

#endif // !1
