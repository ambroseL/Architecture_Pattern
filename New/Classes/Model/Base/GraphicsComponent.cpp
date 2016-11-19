#include "GraphicsComponent.h"// class implemented
#include "cocos2d.h"

/////////////// PUBLIC///////////////////////

//================= 构造函数 ====================

GraphicsComponent::GraphicsComponent():dSp(nullptr),cps(nullptr)
{
}// GraphicsComponent

GraphicsComponent::GraphicsComponent(cocos2d::Sprite* dSp, cocos2d::ParticleMeteor* cps):dSp(dSp),cps(cps)
{
}// GraphicsComponent

GraphicsComponent::GraphicsComponent(GraphicsComponent& graphics)
{
	this->dSp = graphics.dSp;
	this->cps = graphics.cps;
}// GraphicsComponent

GraphicsComponent::~GraphicsComponent()
{
}// ~GraphicsComponent

GraphicsComponent* GraphicsComponent::Clone()
{
	return new GraphicsComponent(copySprite(this->dSp), copyParticle(this->cps));
}


 //==============类的操作 =====================

void GraphicsComponent::setSize(float fWidth, float fHeight)
{
	cocos2d::Size size = dSp->getContentSize();
	float scaleX = fWidth / size.width;
	float scaleY = fHeight / size.height;
	dSp->setScale(scaleX, scaleY);
}

void GraphicsComponent::setWidth(float fWidth)
{
	cocos2d::Size size = dSp->getContentSize();
	float scaleX = fWidth * 2 / size.width;
	dSp->setScaleX(scaleX);
}

void GraphicsComponent::setHeight(float fHeight)
{
	cocos2d::Size size = dSp->getContentSize();
	float scaleY = fHeight * 2 / size.height;
	dSp->setScaleY(scaleY);
}

 //==============属性存取 =====================
cocos2d::Sprite* GraphicsComponent::getSprite()
{
	return this->dSp;
}

void GraphicsComponent::setSprite(cocos2d::Sprite* dSp)
{
	this->dSp = dSp;
}

const float GraphicsComponent::getWidth()								//获取精灵的半长
{
	float width = 0.0;
	cocos2d::Size size = dSp->getContentSize();                        //获取精灵尺寸
	float scaleX = dSp->getScaleX();								   //获取纵向缩放比
	width = size.width * scaleX / 2;								   //返回当前半宽度
	return width;
}

const float GraphicsComponent::getHeight()								//获取精灵的半高
{
	float height = 0.0;
	cocos2d::Size size = dSp->getContentSize();                        //获取精灵尺寸
	float scaleY = dSp->getScaleY();								   //获取纵向缩放比
	height = size.height * scaleY / 2;								   //返回当前半宽度
	return height;
}

const cocos2d::ParticleMeteor* GraphicsComponent::getParticle()
{
	cocos2d::ParticleMeteor* particle = new cocos2d::ParticleMeteor();
	particle = this->cps;
	return particle;
}

void GraphicsComponent::setParticel(cocos2d::ParticleMeteor* pParticle)
{
	this->cps = pParticle;
}

//==============辅助函数 =====================

cocos2d::Sprite* createSprite(int shape, cocos2d::Layer *layer, float* data, std::string pic)
{
	cocos2d::Sprite* dSp = cocos2d::Sprite::create(pic);               //创建精灵
	layer->addChild(dSp, 1);                                           //将精灵添加到布景
	cocos2d::Size size = dSp->getContentSize();                        //获取精灵尺寸
	float pw = data[2] * 2;                                            //计算精灵宽度
	float ph;
	if (shape == 1)                                                    //矩形
		ph = data[3] * 2;                                              //计算精灵长度
	else                                                               //圆形
		ph = data[2] * 2;
	float scaleX = pw / size.width;                                    //计算x,y方向缩放比
	float scaleY = ph / size.height;
	dSp->setScaleX(scaleX);                                            //设置x,y方向缩放比
	dSp->setScaleY(scaleY);
	return dSp;
}


cocos2d::Sprite* copySprite(cocos2d::Sprite* sprite)
{

	cocos2d::Sprite* dSp = nullptr;
	dSp->setTexture(sprite->getTexture());               //创建精灵
	//layer->addChild(dSp, 1);                           //将精灵添加到布景，需通过控制类调用场景类
	//dSp->getContentSize();
	dSp->setScale(sprite->getScale());					 //设置缩放比	
	return dSp;
}

cocos2d::ParticleMeteor* createParticle(float fScale, float lifeCircle, cocos2d::Layer *layer, float* data)
{
	cocos2d::ParticleMeteor* cps = cocos2d::ParticleMeteor::create();
	cps->retain();
	cps->setScale(fScale);
	cps->setPosition(cocos2d::ccp(data[0], data[1]));//位置
	cps->setLife(lifeCircle);//每个粒子生命周期
	layer->addChild(cps);//加到精灵图
	return cps;
}

cocos2d::ParticleMeteor* copyParticle(cocos2d::ParticleMeteor* particle)
{
	cocos2d::ParticleMeteor* cps = cocos2d::ParticleMeteor::create();
	cps->retain();
	cps->setScale(particle->getScale());
	cps->setPosition(particle->getPosition());//位置
	cps->setLife(particle->getLife());//每个粒子生命周期
	//layer->addChild(cps);//加到精灵图
	return cps;
}