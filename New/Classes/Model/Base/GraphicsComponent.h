#ifndef _GraphicsComponent_H_
#define _GraphicsComponent_H_

#include "cocos2d.h"
#include "Box2D/Common/b2Math.h"


/**
* ͼ�񲿼���
*
*#include "cocos2d.h" <BR>
*
*-llib
*
* EntityObj����ɲ���
* ����������ʾ����Сͼ�������Ⱦ��ص��������
* @seesomething
*/

class GraphicsComponent 
{
	cocos2d::Sprite* dSp;/* ���� */
	cocos2d::ParticleSystem* cps;/* ���� */

public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	GraphicsComponent();

	/**
	*���ι��캯��
	*
	*@param dSp �����࣬cocos�Դ�
	*@param cps �����࣬cocos�Դ�
	*/
	GraphicsComponent(cocos2d::Sprite* dSp, cocos2d::ParticleSystem* cps = nullptr);

	/**
	*�������캯��
	*@param graphics ͼ�񲿼�
	*/
	GraphicsComponent(GraphicsComponent& graphics);

	/**
	*��������
	*/
	~GraphicsComponent();

	/**
	*��¡���������
	*/
	GraphicsComponent* Clone();

	//�����

	/**
	*�������ű�
	*/
	void setSize(float fWidth, float fHeight);

	/**
	*����X�������ű�
	*/
	void setWidth(float fWidth);

	/**
	*����Y�������ű�
	*/
	void setHeight(float fHeight);

	//�����Դ�ȡ

	/**
	*��ȡ����
	*/
	cocos2d::Sprite* getSprite();

	/**
	*���þ���
	*@param dSp �����õľ���
	*/
	void setSprite(cocos2d::Sprite* dSp);

	/**
	*��ȡ������
	*/
	const float getWidth();

	/**
	*��ȡ����߶�
	*/
	const float getHeight();

	/**
	*��ȡ����
	*/
	cocos2d::ParticleSystem* getParticle();

	/**
	*��������
	*@param pParticle �����õ�����
	*/
	void setParticel(cocos2d::ParticleSystem* pParticle);


	/**
	*������ͼ
	*@param texture �����õ���ͼ
	*/
	void setTexture(cocos2d::Texture2D* texture);
	
	/**
	*��������λ��
	*@pos �����õ�����λ��
	*/
	void setPosition(cocos2d::Vec2 pos);

	/**
	*��ȡ����λ��
	*/
	cocos2d::Vec2 getPosition();

};

//��������

/**
*��������
*@param shape ������״
*@param layer ���ڳ���
*@param data ����ȹ�������
*@param pic ����ͼ������·��
*
*/
cocos2d::Sprite* createSprite(int shape, float* data, std::string pic);

/**
*��������
*@param sprite �����࣬cocos�Դ�
*
*/
cocos2d::Sprite* copySprite(cocos2d::Sprite* sprite);


/**
*��������
*@param fScale �������ű�
*@param lifeCircle ��������
*@param pos ����λ��
*/
cocos2d::ParticleSystem* createParticle(float fScale, float lifeCircle, cocos2d::Vec2 pos);

/**
*��������
*@param particle �����࣬cocos�Դ�
*
*/
cocos2d::ParticleSystem* copyParticle(cocos2d::ParticleSystem* particle);

/**
*����ǽ����
*@param data ����ȹ�������
*@param pic ����ͼ������·��
*
*/
cocos2d::Sprite* createWallSprite(float* data, std::string pic);

#endif

