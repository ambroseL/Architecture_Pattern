#ifndef _BrickObj_H_
#define _BrickObj_H_

#include "EntityObj.h"

/**
* ש��ʵ����
*
*#include "cocos2d.h" <BR>
*include "PhysicsComponent.h" <BR>
*"GraphicsComponent.h" <BR>
*-llib
*
* ����brick��Ļ��࣬�洢ש��Ļ���������Ϣ����������ֵ
*
* @seesomething
*/
class BrickObj :
	public EntityObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	BrickObj();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����id
	*@param iHP �����õ�ש������ֵ��Ĭ��Ϊ1
	*/
	BrickObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*��������
	*/
	~BrickObj();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;

	//�����Դ�ȡ

	/**
	*��ȡש������ֵ
	*/
	const int getHP();

	/**
	*����ש������ֵ
	*/
	void setHP(int iHP);

protected:

	int HP;			/* ש������ֵ */
};

#endif