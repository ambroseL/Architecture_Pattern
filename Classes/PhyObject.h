#ifndef _PhyObeject_H_
#define _PhyObject_H_
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <vector>
using namespace cocos2d;
#define pixToMeter 5     //含义为几个像素为1米

class PhyObject
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle){};
	virtual void Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle) {};
	virtual void HPchange(PhyObject* ) {};
	std::string* poId;  //指向物体id的指针
	Sprite* dSp;        //指向描绘物体用的精灵对象的指针
	b2Body* body;       //指向物体对应刚体对象的指针
	int attack;
	int HP;
	PhyObject(
		std::string* id,    //指向物体id的指针
		Layer *layer,         //指向布景层的指针
		b2World* world,        //指向世界类的指针
		std::string pic,      //精灵所需图片的路径
		float* data,          //物体数据
		float density,        //物体密度
		float friction,       //物体摩擦系数
		float restitution);    //物体恢复系数
	~PhyObject();
	virtual void refresh();   //更新精灵位置、姿态信息的方法
};

//墙
class Wall : public PhyObject
{
public:
	Wall
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
		);
	static int index;
};

//球
class Ball : public PhyObject
{
public:
	Ball
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int attack
		);
	static float radius;
	static float speed;//球的实时速度
	static float s_speed;//球的初始速度
	static bool isFast;

	virtual void refresh();
	CCParticleSystem *cps;//粒子效果

	static int index;
};


//挡板
class Paddle : public PhyObject
{
public:
	Paddle
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int i_HP
		);
	b2Body* body_ball;
	b2Body* body_paddle;
	Sprite* dSp_ball;
	Sprite* dSp_paddle;

	virtual void refresh();//挡板的更新方法
	void Is_Sticky(b2World* world, Layer* layer, float* data);//让球粘黏挡板的函数

	bool isSticky;
	bool isReversal;
	bool isImage;

	static float ball_x;//当球跟挡板粘在一起时球相对于挡板的x坐标偏移量
	static float ball_y;//当球跟挡板粘在一起时球相对于挡板的y坐标偏移量
	static float length;//挡板的实时半长度
	static float width;//挡板的实时半宽度
	static float s_length;//挡板的初始半长度
	static float s_width;//挡板的初始半宽度

	static int index;
};

//物理和绘制封装类——砖块
class Common_Brick : public PhyObject//普通砖块
{
public:
	virtual void HPchange(PhyObject* po);
	Common_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int HP
		);
	static int index;
};

class Hard_Brick : public PhyObject//钢铁砖块
{
public:
	Hard_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int i_HP
		);
	static int index;
};

class Sticky_Brick : public PhyObject//粘黏砖块
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void HPchange(PhyObject* po);
	Sticky_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int HP
		);
	static int index;
};

class Reversal_Brick : public PhyObject//颠倒砖块
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void HPchange(PhyObject* po);
	Reversal_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int HP
		);
	static int index;
};

class Image_Brick : public PhyObject//镜像砖块
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void HPchange(PhyObject* po);
	Image_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int HP
		);
	static int index;
};

class Lengthen_Brick : public PhyObject//伸长砖块
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void HPchange(PhyObject* po);
	Lengthen_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int i_HP
		);
	static int index;
};

class Shorten_Brick : public PhyObject//缩短砖块
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void HPchange(PhyObject* po);
	Shorten_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int i_HP
		);
	static int index;
};

class Accelerate_Brick : public PhyObject//加速砖块
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void HPchange(PhyObject* po);
	Accelerate_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int i_HP
		);
	static int index;
};

class Decelerate_Brick : public PhyObject//减速砖块
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void HPchange(PhyObject* po);
	Decelerate_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int i_HP
		);
	static int index;
};

class Upgrade_Brick : public PhyObject//升级砖块
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void HPchange(PhyObject* po);
	Upgrade_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int i_HP
		);
	static int index;
};

class Transmit_Brick : public PhyObject//传送砖块
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	Transmit_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int i_HP
		);
	static int index;
};

class Fast_Brick : public PhyObject//穿透砖块
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void HPchange(PhyObject* po);
	Fast_Brick
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution,
		int i_HP
		);
	static int index;
};

//物理和绘制封装类——包裹
class Sticky_Pack : public PhyObject//粘黏包裹
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	Sticky_Pack
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
		);
	static int index;
};

class Reversal_Pack : public PhyObject//颠倒包裹
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle);
	Reversal_Pack
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
		);
	static int index;
};

class Image_Pack : public PhyObject//镜像包裹
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle);
	Image_Pack
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
		);
	static int index;
};

class Fast_Pack : public PhyObject//穿透包裹
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle);
	Fast_Pack
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
		);
	static int index;
};


class Lengthen_Pack :public PhyObject//伸长包裹
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle);
	Lengthen_Pack
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
		);
	static int index;
};

class Shorten_Pack :public PhyObject//缩短包裹
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle);
	Shorten_Pack
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
		);
	static int index;
};

class Accelerate_Pack :public PhyObject//加速包裹
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle);
	Accelerate_Pack
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
		);
	static int index;
};

class Decelerate_Pack :public PhyObject//减速包裹
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle);
	Decelerate_Pack
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
		);
	static int index;
};

class Upgrade_Pack :public PhyObject//升级包裹
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle);
	virtual void Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle);
	Upgrade_Pack
		(
		std::string* id,
		Layer* layer,
		b2World* world,
		std::string pic,
		float* data,
		float density,
		float friction,
		float restitution
		);
	static int index;
};


#endif