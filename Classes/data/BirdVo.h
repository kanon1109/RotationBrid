#pragma once
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
};

