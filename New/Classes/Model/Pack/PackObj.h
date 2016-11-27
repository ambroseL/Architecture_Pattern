#ifndef _PackObj_H_
#define _PackObj_H_

#include "EntityObj.h"

/**
* 包裹实体类
*
*#include "EntityObj.h" <BR>
*-llib
*
* 所有pack类的基类，存储包裹的基本数据信息
*
* @seesomething
*/

class PackObj :public EntityObj
{
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	PackObj();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*/
	PackObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*析构函数
	*/
	~PackObj();

	/**
	*克隆函数，深拷贝
	*/
	EntityObj* Clone() override;
};
#endif
