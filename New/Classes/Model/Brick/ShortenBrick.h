#ifndef _ShortenBrick_H_
#define _ShortenBrick_H_

#include "BrickObj.h"
/**
* ����ש����
*
*#include "BrickObj.h" <BR>
*-llib
*
* ש��ʵ��������࣬�������������̰���
*
* @seesomething
*/

class ShortenBrick :public BrickObj
{
public:

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	ShortenBrick();
	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	ShortenBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*��������
	*/
	~ShortenBrick();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;

};
#endif