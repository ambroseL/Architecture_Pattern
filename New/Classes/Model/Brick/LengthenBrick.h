#ifndef _LengthenBrick_H_
#define _LengthenBrick_H_

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

class LengthenBrick: public BrickObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	LengthenBrick();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	LengthenBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, int iHP = 1);
	
	/**
	*��������
	*/
	~LengthenBrick();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;

	//�����Դ�ȡ


};
#endif

