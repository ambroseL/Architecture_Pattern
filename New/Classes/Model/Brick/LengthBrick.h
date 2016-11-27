#ifndef _LengthBrick_H_
#define _LengthBrick_H_

#include "BrickObj.h"

/**
* 长度砖块类
*
*#include "BrickObj.h" <BR>
*-llib
*
* 砖块实体类的子类，被击碎后产生长度包裹
*
* @seesomething
*/

class LengthBrick: public BrickObj
{
	bool isLengthen;	/* 长度属性值，为true表示增长砖块，否则为缩短砖块 */
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	LengthBrick();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param bLengthen 长度属性值，默认为true
	*@param id 物体ID
	*@param iHP 砖块生命值，默认为1
	*/
	LengthBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool bLengthen = true, int iHP = 1);
	
	/**
	*析构函数
	*/
	~LengthBrick();

	/**
	*克隆函数，深拷贝
	*/
	EntityObj* Clone() override;

	//类属性存取

	/**
	*获取砖块长度属性值
	*/
	const bool getLengthen();

	/**
	*设置砖块长度属性值
	*/
	void setLengthen(bool isLengthen);
};
#endif

