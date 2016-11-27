#ifndef _DeaccelerateBrick_H_
#define _DeaccelerateBrick_H_

#include "BrickObj.h"
/**
* ����ש����
*
*#include "BrickObj.h" <BR>
*-llib
*
* ש��ʵ��������࣬�������������Ȱ���
*
* @seesomething
*/
class DeaccelerateBrick: public BrickObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	DeaccelerateBrick();
	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	DeaccelerateBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*��������
	*/
	~DeaccelerateBrick();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;
};
#endif
