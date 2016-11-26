#include "GraphicsComponent.h"// class implemented
#include "cocos2d.h"
#include "Box2D/Common/b2Math.h"
#include "PhysicsComponent.h"

/////////////// PUBLIC///////////////////////

//================= ���캯�� ====================

GraphicsComponent::GraphicsComponent():dSp(nullptr),cps(nullptr)
{
}// GraphicsComponent

GraphicsComponent::GraphicsComponent(cocos2d::Sprite* dSp, cocos2d::ParticleSystem* cps):dSp(dSp),cps(cps)
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
	float scaleX = fWidth * 2 / size.width;
	float scaleY = fHeight * 2 / size.height;
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

cocos2d::ParticleSystem* GraphicsComponent::getParticle()
{
	return this->cps;
}

void GraphicsComponent::setParticel(cocos2d::ParticleSystem* pParticle)
{
	this->cps = pParticle;
}

void GraphicsComponent::setPosition(cocos2d::Vec2 pos)
{
	this->dSp->setPosition(pos);
}


cocos2d::Vec2 GraphicsComponent::getPosition()
{
	return dSp->getPosition();
}

void GraphicsComponent::setTexture(cocos2d::Texture2D* texture)
{
	if (texture != NULL)
		dSp->setTexture(texture);
}


//==============�������� =====================

cocos2d::Sprite* createSprite(int shape, float* data, std::string pic)
{
	cocos2d::Sprite* dSp = cocos2d::Sprite::create(pic);               //��������
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

cocos2d::ParticleSystem* createParticle(float fScale, float lifeCircle, cocos2d::Vec2 pos)
{
	cocos2d::ParticleSystem* cps = cocos2d::ParticleMeteor::create();
	cps->retain();
	cps->setScale(fScale);
	cps->setPosition(pos);//λ��
	cps->setLife(lifeCircle);//ÿ��������������
	return cps;
}

cocos2d::ParticleSystem* copyParticle(cocos2d::ParticleSystem* particle)
{
	cocos2d::ParticleSystem* cps = cocos2d::ParticleMeteor::create();
	cps->retain();
	cps->setScale(particle->getScale());
	cps->setPosition(particle->getPosition());//λ��
	cps->setLife(particle->getLife());//ÿ��������������
	//layer->addChild(cps);//�ӵ�����ͼ
	return cps;
}

cocos2d::Sprite* createWallSprite(float* data, std::string pic)
{
	cocos2d::Sprite* dSp = cocos2d::Sprite::create(pic);
	cocos2d::Size size = dSp->getContentSize();//��ȡ����ĳߴ�
	b2EdgeShape shape;//�����������������
	float positionX = (data[0] + data[2]) / 2;//�����������λ�õ�X����
	float positionY = (data[1] + data[3]) / 2;//�����������λ�õ�Y����
	shape.Set(b2Vec2((data[0] - positionX) / pixToMeter, (data[1] - positionY) / pixToMeter), b2Vec2((data[2] - positionX) / pixToMeter, (data[3] - positionY) / pixToMeter));//����λ��
	b2Vec2 v1 = shape.m_vertex1;//v1��ֵΪ���ε�һ������
	b2Vec2 v2 = shape.m_vertex2;//v2��ֵΪ���εڶ�������
	b2Vec2 v3 = v2 - v1;
	float scaleX, scaleY;
	if (v3.x == 0)
	{
		scaleX = v3.x / size.height;//���������Y�������ű�
		scaleY = v3.Length()*pixToMeter / size.width;//���������X�������ű�
	}
	else if (v3.y == 0)
	{
		scaleX = v3.Length()*pixToMeter / size.width;//���������X�������ű�
		scaleY = 3 / size.height;//���������Y�������ű�
	}
	dSp->setScaleX(scaleX);//���þ���X�������ű�
	dSp->setScaleY(scaleY);//���þ���Y�������ű�
	return dSp;
}



