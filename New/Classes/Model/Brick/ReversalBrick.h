#ifndef _ReversalBrick_H_
#define _ReversalBrick_H_

#include "BrickObj.h"

/**
* �ߵ�ש����
*
*#include "BrickObj.h" <BR>
*-llib
*
* ש��ʵ��������࣬�����������ߵ�����
*
* @seesomething
*/
class ReversalBrick :public BrickObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	ReversalBrick();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	ReversalBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*��������
	*/
	~ReversalBrick();
};
#endif
