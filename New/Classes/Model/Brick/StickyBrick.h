#ifndef _StickyBrick_H_
#define _StickyBrick_H_

#include "BrickObj.h"

/**
* ճ�ש����
*
*#include "BrickObj.h" <BR>
*-llib
*
* ש��ʵ��������࣬������������͸����
*
* @seesomething
*/
class StickyBrick: public BrickObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	StickyBrick();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	StickyBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*��������
	*/
	~StickyBrick();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;
};
#endif
