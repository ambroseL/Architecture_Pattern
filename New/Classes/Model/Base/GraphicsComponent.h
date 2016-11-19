#ifndef _GraphicsComponent_H_
#define _GraphicsComponent_H_

#include "cocos2d.h"


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
	cocos2d::ParticleMeteor* cps;/* ���� */

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
	GraphicsComponent(cocos2d::Sprite* dSp, cocos2d::ParticleMeteor* cps = nullptr);

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
	const cocos2d::ParticleMeteor* getParticle();

	/**
	*��������
	*/
	void setParticel(cocos2d::ParticleMeteor* pParticle);
	
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
cocos2d::Sprite* createSprite(int shape, cocos2d::Layer *layer,float* data, std::string pic);

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
*@param layer ��������ͼ���
*@param data ����ȹ�������
*/
cocos2d::ParticleMeteor* createParticle(float fScale, float lifeCircle, cocos2d::Layer *layer, float* data);

/**
*��������
*@param particle �����࣬cocos�Դ�
*
*/
cocos2d::ParticleMeteor* copyParticle(cocos2d::ParticleMeteor* particle);

#endif

