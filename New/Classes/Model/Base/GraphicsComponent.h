#ifndef _GraphicsComponent_H_
#define _GraphicsComponent_H_

#include "cocos2d.h"


/**
* 图像部件类
*
*#include "cocos2d.h" <BR>
*
*-llib
*
* EntityObj的组成部分
* 负责物体显示，大小图像等与渲染相关的事务管理
* @seesomething
*/

class GraphicsComponent 
{
	cocos2d::Sprite* dSp;/* 精灵 */
	cocos2d::ParticleMeteor* cps;/* 粒子 */

public:
	// 类的生命周期控制函数，包括构造和析构	

	/**
	*默认构造函数
	*/
	GraphicsComponent();

	/**
	*含参构造函数
	*
	*@param dSp 精灵类，cocos自带
	*@param cps 粒子类，cocos自带
	*/
	GraphicsComponent(cocos2d::Sprite* dSp, cocos2d::ParticleMeteor* cps = nullptr);

	/**
	*拷贝构造函数
	*@param graphics 图像部件
	*/
	GraphicsComponent(GraphicsComponent& graphics);

	/**
	*析构函数
	*/
	~GraphicsComponent();

	/**
	*克隆函数，深拷贝
	*/
	GraphicsComponent* Clone();

	//类操作

	/**
	*设置缩放比
	*/
	void setSize(float fWidth, float fHeight);

	/**
	*设置X方向缩放比
	*/
	void setWidth(float fWidth);

	/**
	*设置Y方向缩放比
	*/
	void setHeight(float fHeight);

	//类属性存取

	/**
	*获取精灵
	*/
	cocos2d::Sprite* getSprite();

	/**
	*设置精灵
	*@param dSp 待设置的精灵
	*/
	void setSprite(cocos2d::Sprite* dSp);

	/**
	*获取精灵宽度
	*/
	const float getWidth();

	/**
	*获取精灵高度
	*/
	const float getHeight();

	/**
	*获取粒子
	*/
	const cocos2d::ParticleMeteor* getParticle();

	/**
	*设置粒子
	*/
	void setParticel(cocos2d::ParticleMeteor* pParticle);
	
};

//辅助函数

/**
*创建精灵
*@param shape 物体形状
*@param layer 所在场景
*@param data 长宽等构建数据
*@param pic 物体图像所在路径
*
*/
cocos2d::Sprite* createSprite(int shape, cocos2d::Layer *layer,float* data, std::string pic);

/**
*拷贝精灵
*@param sprite 精灵类，cocos自带
*
*/
cocos2d::Sprite* copySprite(cocos2d::Sprite* sprite);


/**
*创建粒子
*@param fScale 粒子缩放比
*@param lifeCircle 生命周期
*@param layer 粒子所在图像层
*@param data 长宽等构建数据
*/
cocos2d::ParticleMeteor* createParticle(float fScale, float lifeCircle, cocos2d::Layer *layer, float* data);

/**
*拷贝粒子
*@param particle 粒子类，cocos自带
*
*/
cocos2d::ParticleMeteor* copyParticle(cocos2d::ParticleMeteor* particle);

#endif

