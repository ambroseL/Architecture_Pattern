#ifndef _UpgradeBrick_H_
#define _UpgradeBrick_H_

#include "BrickObj.h"

/**
* ����ש����
*
*#include "BrickObj.h" <BR>
*-llib
*
* ש��ʵ��������࣬������������������
*
* @seesomething
*/

class UpgradeBrick :public BrickObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	UpgradeBrick();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	UpgradeBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*��������
	*/
	~UpgradeBrick();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;
};

#endif