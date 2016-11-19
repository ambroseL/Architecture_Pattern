#ifndef _WallObj_H_
#define _WallObj_H_

#include "EntityObj.h"

/**
* 墙体类
*
*#include "EntityObj.h" <BR>
*-llib
*
* 构造游戏的边界，存储墙体的基本数据信息
* 
* @seesomething
*/
class WallObj :public EntityObj
{
public:
	
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	WallObj();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*/
	WallObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);

	/**
	*析构函数
	*/
	~WallObj();

	/**
	*克隆函数，深拷贝
	*/
	EntityObj* Clone() override;
};

#endif
