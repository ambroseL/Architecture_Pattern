#ifndef _TransmitBrick_H_
#define _TransmitBrick_H_

#include "BrickObj.h"

/**
* 传送砖块类
*
*#include "BrickObj.h" <BR>
*-llib
*
* 砖块实体类的子类，被球体击中后会将其传送至另一个传送砖块
*
* @seesomething
*/

class TransmitBrick :public BrickObj
{
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	TransmitBrick();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*@param iHP 砖块生命值，默认为1
	*/
	TransmitBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*析构函数
	*/
	~TransmitBrick();
};

#endif