#ifndef _ReversalPack_H_
#define _ReversalPack_H_

#include "PackObj.h"

/**
* 颠倒包裹类
*
*#include "PackObj.h" <BR>
*-llib
*
* 包裹实体类的子类，被挡板接住后，短时间内使挡板移动方向与鼠标控制方向相反
*
* @seesomething
*/
class ReversalPack:public PackObj 
{
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	ReversalPack();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*/
	ReversalPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);

	/**
	*析构函数
	*/
	~ReversalPack();
};
#endif
