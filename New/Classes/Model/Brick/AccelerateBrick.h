#ifndef _AccelerateBrick_H_
#define _AccelerateBrick_H_

#include "BrickObj.h"

/**
*����ש����
*
*#include "BrickObj.h" <BR>
*-llib
*
* ש��ʵ��������࣬�����������ٶȰ���
*
* @seesomething
*/

class AccelerateBrick :public BrickObj
{
public:

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	AccelerateBrick();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	AccelerateBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);

	/**
	*��������
	*/
	~AccelerateBrick();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;

};
#endif