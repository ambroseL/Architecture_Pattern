#ifndef _PermeatBrick_H_
#define _PermeatBrick_H_

#include "BrickObj.h"

/**
* ��͸ש����
*
*#include "BrickObj.h" <BR>
*-llib
*
* ש��ʵ��������࣬������������͸����
*
* @seesomething
*/

class PermeatBrick :public BrickObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	PermeatBrick();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	PermeatBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*��������
	*/
	~PermeatBrick();
};
#endif
