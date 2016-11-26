#ifndef _GraphicsComponent_H_
#define _GraphicsComponent_H_

#include "cocos2d.h"
#include "Box2D/Common/b2Math.h"


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
	cocos2d::ParticleSystem* cps;/* 粒子 */

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
	GraphicsComponent(cocos2d::Sprite* dSp, cocos2d::ParticleSystem* cps = nullptr);

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
	cocos2d::ParticleSystem* getParticle();

	/**
	*设置粒子
	*@param pParticle 待设置的粒子
	*/
	void setParticel(cocos2d::ParticleSystem* pParticle);


	/**
	*设置贴图
	*@param texture 待设置的贴图
	*/
	void setTexture(cocos2d::Texture2D* texture);
	
	/**
	*设置物体位置
	*@pos 待设置的物体位置
	*/
	void setPosition(cocos2d::Vec2 pos);

	/**
	*获取物体位置
	*/
	cocos2d::Vec2 getPosition();

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
cocos2d::Sprite* createSprite(int shape, float* data, std::string pic);

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
*@param pos 粒子位置
*/
cocos2d::ParticleSystem* createParticle(float fScale, float lifeCircle, cocos2d::Vec2 pos);

/**
*拷贝粒子
*@param particle 粒子类，cocos自带
*
*/
cocos2d::ParticleSystem* copyParticle(cocos2d::ParticleSystem* particle);

/**
*创建墙精灵
*@param data 长宽等构建数据
*@param pic 物体图像所在路径
*
*/
cocos2d::Sprite* createWallSprite(float* data, std::string pic);

#endif

