#include "GraphicsComponent.h"// class implemented
#include "cocos2d.h"

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

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


 //==============��Ĳ��� =====================

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

 //==============���Դ�ȡ =====================
cocos2d::Sprite* GraphicsComponent::getSprite()
{
	return this->dSp;
}

void GraphicsComponent::setSprite(cocos2d::Sprite* dSp)
{
	this->dSp = dSp;
}

const float GraphicsComponent::getWidth()								//��ȡ����İ볤
{
	float width = 0.0;
	cocos2d::Size size = dSp->getContentSize();                        //��ȡ����ߴ�
	float scaleX = dSp->getScaleX();								   //��ȡ�������ű�
	width = size.width * scaleX / 2;								   //���ص�ǰ����
	return width;
}

const float GraphicsComponent::getHeight()								//��ȡ����İ��
{
	float height = 0.0;
	cocos2d::Size size = dSp->getContentSize();                        //��ȡ����ߴ�
	float scaleY = dSp->getScaleY();								   //��ȡ�������ű�
	height = size.height * scaleY / 2;								   //���ص�ǰ����
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

//==============�������� =====================

cocos2d::Sprite* createSprite(int shape, cocos2d::Layer *layer, float* data, std::string pic)
{
	cocos2d::Sprite* dSp = cocos2d::Sprite::create(pic);               //��������
	layer->addChild(dSp, 1);                                           //��������ӵ�����
	cocos2d::Size size = dSp->getContentSize();                        //��ȡ����ߴ�
	float pw = data[2] * 2;                                            //���㾫����
	float ph;
	if (shape == 1)                                                    //����
		ph = data[3] * 2;                                              //���㾫�鳤��
	else                                                               //Բ��
		ph = data[2] * 2;
	float scaleX = pw / size.width;                                    //����x,y�������ű�
	float scaleY = ph / size.height;
	dSp->setScaleX(scaleX);                                            //����x,y�������ű�
	dSp->setScaleY(scaleY);
	return dSp;
}


cocos2d::Sprite* copySprite(cocos2d::Sprite* sprite)
{

	cocos2d::Sprite* dSp = nullptr;
	dSp->setTexture(sprite->getTexture());               //��������
	//layer->addChild(dSp, 1);                           //��������ӵ���������ͨ����������ó�����
	//dSp->getContentSize();
	dSp->setScale(sprite->getScale());					 //�������ű�	
	return dSp;
}

cocos2d::ParticleMeteor* createParticle(float fScale, float lifeCircle, cocos2d::Layer *layer, float* data)
{
	cocos2d::ParticleMeteor* cps = cocos2d::ParticleMeteor::create();
	cps->retain();
	cps->setScale(fScale);
	cps->setPosition(cocos2d::ccp(data[0], data[1]));//λ��
	cps->setLife(lifeCircle);//ÿ��������������
	layer->addChild(cps);//�ӵ�����ͼ
	return cps;
}

cocos2d::ParticleMeteor* copyParticle(cocos2d::ParticleMeteor* particle)
{
	cocos2d::ParticleMeteor* cps = cocos2d::ParticleMeteor::create();
	cps->retain();
	cps->setScale(particle->getScale());
	cps->setPosition(particle->getPosition());//λ��
	cps->setLife(particle->getLife());//ÿ��������������
	//layer->addChild(cps);//�ӵ�����ͼ
	return cps;
}