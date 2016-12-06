#ifndef _ObjSpawner_H_
#define _ObjSpawner_H_
#include "EntityObj.h"
/**
* 物体孵化器类
*
*#include "EntityObj.h"
*-llib
*
* 实现物体的批量生产
*
* @seesomething
*/


class ObjSpawner
{

	EntityObj* prototype;						/* 孵化原型 */
public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*含参构造函数
	*/
	ObjSpawner(EntityObj* prototype);

	/**
	*析构函数
	*/
	~ObjSpawner();

	//类操作
	
	/**
	 * 生产物体
	 */
	EntityObj* spawnEntity();

	/**
	 *设置孵化器的孵化原型
	 *@parameter prototype 
	 */
	void setPrototype(EntityObj* prototype);
};
#endif

