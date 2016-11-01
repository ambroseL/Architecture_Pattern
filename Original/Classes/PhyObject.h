#ifndef _PhyObeject_H_
#define _PhyObject_H_
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <vector>
using namespace cocos2d;
#define pixToMeter 5     //����Ϊ��������Ϊ1��

class PhyObject
{
public:
	virtual void Work(std::map<std::string, PhyObject*> &pom, Layer* layer, b2World* world, float x, float y, PhyObject* ball, PhyObject* paddle){};
	virtual void Reset(Layer* layer, b2World* world, PhyObject* ball, PhyObject* paddle) {};
	virtual void HPchange(PhyObject* ) {};
	std::string* poId;  //ָ������id��ָ��
	Sprite* dSp;        //ָ����������õľ�������ָ��
	b2Body* body;       //ָ�������Ӧ��������ָ��
	int attack;
	int HP;
	PhyObject(
		std::string* id,    //ָ������id��ָ��
		Layer *layer,         //ָ�򲼾����ָ��
		b2World* world,        //ָ���������ָ��
		std::string pic,      //��������ͼƬ��·��
		float* data,          //��������
		float density,        //�����ܶ�
		float friction,       //����Ħ��ϵ��
		float restitution);    //����ָ�ϵ��
	~PhyObject();
	virtual void refresh();   //���¾���λ�á���̬��Ϣ�ķ���
};

//ǽ
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

//��
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
	static float speed;//���ʵʱ�ٶ�
	static float s_speed;//��ĳ�ʼ�ٶ�
	static bool isFast;

	virtual void refresh();
	CCParticleSystem *cps;//����Ч��

	static int index;
};


//����
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

	virtual void refresh();//����ĸ��·���
	void Is_Sticky(b2World* world, Layer* layer, float* data);//����ճ𤵲��ĺ���

	bool isSticky;
	bool isReversal;
	bool isImage;

	static float ball_x;//���������ճ��һ��ʱ������ڵ����x����ƫ����
	static float ball_y;//���������ճ��һ��ʱ������ڵ����y����ƫ����
	static float length;//�����ʵʱ�볤��
	static float width;//�����ʵʱ����
	static float s_length;//����ĳ�ʼ�볤��
	static float s_width;//����ĳ�ʼ����

	static int index;
};

//����ͻ��Ʒ�װ�ࡪ��ש��
class Common_Brick : public PhyObject//��ͨש��
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

class Hard_Brick : public PhyObject//����ש��
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

class Sticky_Brick : public PhyObject//ճ�ש��
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

class Reversal_Brick : public PhyObject//�ߵ�ש��
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

class Image_Brick : public PhyObject//����ש��
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

class Lengthen_Brick : public PhyObject//�쳤ש��
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

class Shorten_Brick : public PhyObject//����ש��
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

class Accelerate_Brick : public PhyObject//����ש��
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

class Decelerate_Brick : public PhyObject//����ש��
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

class Upgrade_Brick : public PhyObject//����ש��
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

class Transmit_Brick : public PhyObject//����ש��
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

class Fast_Brick : public PhyObject//��͸ש��
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

//����ͻ��Ʒ�װ�ࡪ������
class Sticky_Pack : public PhyObject//ճ����
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

class Reversal_Pack : public PhyObject//�ߵ�����
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

class Image_Pack : public PhyObject//�������
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

class Fast_Pack : public PhyObject//��͸����
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


class Lengthen_Pack :public PhyObject//�쳤����
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

class Shorten_Pack :public PhyObject//���̰���
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

class Accelerate_Pack :public PhyObject//���ٰ���
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

class Decelerate_Pack :public PhyObject//���ٰ���
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

class Upgrade_Pack :public PhyObject//��������
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