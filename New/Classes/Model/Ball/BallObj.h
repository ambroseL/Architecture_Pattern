#ifndef _BallObj_H_
#define _BallObj_H_

#include "EntityObj.h"

/**
* 球体类
*
*#include "EntityObj.h" <BR>
*-llib
*
* 弹球为model类，存储球体的基本数据信息，包括除基类数据之外球体对应的攻击力，速度状态, 穿透状态及初始速度
*
* @seesomething
*/



/* 球体速度的三个状态 */
enum SpeedState
{
	Slow = 0,	/* 减速状态 */
	Fast = 1,	/* 加速状态 */
	Normal = 2	/* 匀速状态 */
};


class BallObj :public EntityObj
{
	int attack;					/* 球体攻击力 */

	SpeedState speedState;		/* 球体运动状态 */

	bool isPermeat;				/* 球体是否处于穿透状态 */

	b2Vec2 initialSpeed;				/* 球体初速度 */

	b2Vec2 constantSpeed;				/* 球体当前匀速度 */

public:

	// 类的生命周期控制函数，包括构造和析构	
	
	/**
	*默认构造函数
	*/
	BallObj();
	
	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*@param attack 球体攻击力，默认值为1
	*@param bSpeed 球体初速度，默认值为0
	*@param speedState 球体运动状态，默认值为slow
	*@param isPermeat 球体是否处于穿透状态，即与砖块碰撞时不反弹，直接将砖块破坏，默认值为false
	*/
	BallObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int attack = 1, 
		b2Vec2 bSpeed = b2Vec2(0,0), SpeedState speedState = Normal, bool isPermeat = false);
	
	/**
	*析构函数
	*/
	~BallObj();
	
	/**
	*克隆函数，深拷贝
	*/
	EntityObj* Clone() override;

	//类操作
	
	/**
	*重置函数，将球体的所有属性值还原为默认值
	*/
	void Reset();

	//类属性存取
	
	/**
	*获取球体的初速度
	*/
	const b2Vec2 getInitialSpeed();

	/**
	*设置球体的初速度
	*/
	void setInitialSpeed(b2Vec2 initialSpeed);

	/**
	*获取球体的攻击力
	*/
	const int getAttack();

	/**
	*设置球体的攻击力
	*@parameter iAttack 待设置的球体攻击力数值
	*/
	void setAttack(int iAttack);

	/**
	*获取球体的半径
	*/
	const float getRadius();

	/**
	*设置球体的半径
	*@param fRadius 待设置的球体半径数值
	*/
	void setRadius(float fRadius);

	/**
	*获取球体的实时匀速度
	*/
	b2Vec2 getConstantSpeed();

	/**
	*设置球体的实时匀速度
	*@param speed 待设置的球体匀速度
	*/
	void setConstantSpeed(b2Vec2 speed);

	//类的状态设置及查询
	
	/**
	*设置球体的速度状态
	*@param speedState 球体运动状态
	*/
	void setSpeedState(SpeedState speedState);

	/**
	*获取球体的当前速度状态
	*/
	const SpeedState getSpeedState();

	/**
	*获取球体是否处于穿透状态
	*/
	const bool getPermeat();

	/**
	*设置球体的穿透状态
	*/
	void setPermeat(bool isPermeat);
	

};

#endif