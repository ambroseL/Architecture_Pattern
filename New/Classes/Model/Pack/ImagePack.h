#ifndef _ImagePack_H_
#define _ImagePack_H_
#include "PackObj.h"

/**
* 镜像包裹类
*
*#include "PackObj.h" <BR>
*-llib
*
* 包裹实体类的子类，被挡板接住后，将产生一个镜像挡板
*
* @seesomething
*/

class ImagePack :public PackObj
{
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	ImagePack();

	/**
	*含参构造函数
	*
	*@param physicsComponent 物理部件
	*@param graphicsComponent 图像部件
	*@param id 物体ID
	*/	
	ImagePack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*析构函数
	*/
	~ImagePack();
};
#endif