#ifndef _ReversalBrick_H_
#define _ReversalBrick_H_

#include "BrickObj.h"

/**
* 颠倒砖块类
*
*#include "BrickObj.h" <BR>
*-llib
*
* 砖块实体类的子类，被击碎后产生颠倒包裹
*
* @seesomething
*/
class ReversalBrick :public BrickObj
{
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	ReversalBrick();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*@param iHP 砖块生命值，默认为1
	*/
	ReversalBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*析构函数
	*/
	~ReversalBrick();
};
#endif
