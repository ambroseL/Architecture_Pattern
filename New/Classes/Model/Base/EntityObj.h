#ifndef _EntityObj_H_
#define _EntityObj_H_
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

/**
* ʵ�������
*
*#include "cocos2d.h" <BR>
*#include "PhysicsComponent.h"
*#include "GraphicsComponent.h"
*-llib
*
* ����model��Ļ��࣬�洢����Ļ���������Ϣ����������������ͼ�񲿼�
* ������������������ײ���ٶȱ仯�������¼�������������
* ͼ�񲿼�����������ʾ����Сͼ�������Ⱦ��ص��������
*
* @seesomething
*/
class EntityObj
{

public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	EntityObj();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ��������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*/
	EntityObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);

	/**
	*�������캯��
	*@param entityObj ʵ�����
	*/
	EntityObj(const EntityObj& entityObj);

	/**
	*��������
	*/
	virtual ~EntityObj();

	/**
	*��¡���������
	*/
	virtual EntityObj* Clone();

	//�����

	/**
	*����ʵ������
	*/
	virtual void Update();

	//�����Դ�ȡ

	/**
	*��ȡͼ�񲿼�
	*/
	GraphicsComponent* getGraphicsComponent();

	/**
	*��ȡ��������
	*/
	PhysicsComponent* getPhysicsComponent();

	/**
	*��ȡ����߶�
	*ͼ�񲿼�������������ֱ�����
	*/
	const float getHeight();

	/**
	*��ȡ�������
	*ͼ�񲿼�������������ֱ�����
	*/
	const float getWidth();

	/**
	*��������߶�
	*ͼ�񲿼�������������ֱ�����
	*@param fHeight �����õ�����߶�
	*/
	void setHeight(float fHeight);

	/**
	*�����������
	*ͼ�񲿼�������������ֱ�����
	*@param fWidth �����õ��������
	*/
	void setWidth(float fWidth);

	/**
	*��ȡ����ʵʱ�ٶ�
	*����������ʵ��
	*/
	const b2Vec2 getSpeed();

	/**
	*��������ʵʱ�ٶ�
	*����������ʵ��
	*@param fSpeed �����õ������ٶ�
	*/
	void setSpeed(b2Vec2 fSpeed);

	/**
	*������������
	*��ͼ�񲿼�ʵ��
	*@param cps �����õ�����
	*/
	void setParticle(cocos2d::ParticleMeteor* cps);

	/**
	*��ȡ��������
	*��ͼ�񲿼�ʵ��
	*/
	const cocos2d::ParticleMeteor* getParticle();

	/**
	*��ȡ����ID
	*/
	const std::string* getID();

	/**
	*��������ID
	*/
	void setID(std::string* id);

protected:

	PhysicsComponent* physicsComponent;				/* �������� */

	GraphicsComponent* graphicsComponent;			/* ͼ�񲿼� */

	std::string* id;								/* ����idֵ */
};

#endif