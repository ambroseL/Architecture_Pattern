#ifndef _TransmitBrick_H_
#define _TransmitBrick_H_

#include "BrickObj.h"

/**
* ����ש����
*
*#include "BrickObj.h" <BR>
*-llib
*
* ש��ʵ��������࣬��������к�Ὣ�䴫������һ������ש��
*
* @seesomething
*/

class TransmitBrick :public BrickObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	TransmitBrick();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	TransmitBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*��������
	*/
	~TransmitBrick();
};

#endif