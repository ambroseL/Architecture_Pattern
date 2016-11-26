#ifndef _PermeatBrick_H_
#define _PermeatBrick_H_

#include "BrickObj.h"

/**
* 速度砖块类
*
*#include "BrickObj.h" <BR>
*-llib
*
* 砖块实体类的子类，被击碎后产生速度包裹
*
* @seesomething
*/

class SpeedBrick :public BrickObj
{
	bool isFasten;/* 速度属性值，为true表示加速砖块，否则为减速砖块 */

public:

	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	SpeedBrick();

	/**
	*析构函数
	*/
	~SpeedBrick();

	/**
	*克隆函数，深拷贝
	*/
	EntityObj* Clone() override;

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*@param fasten 速度属性值，默认为true
	*@param iHP 砖块生命值，默认为1
	*/
	SpeedBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool fasten = true, int iHP = 1);
	
	//类属性存取

	/**
	*获取砖块速度属性值
	*/
	const bool getFasten();

	/**
	*设置砖块速度属性值
	*/
	void setFasten(bool isFasten);
};
#endif