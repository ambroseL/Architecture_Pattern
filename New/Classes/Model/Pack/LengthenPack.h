#ifndef _LengthenPack_H_
#define _LengthenPack_H_

#include "PackObj.h"

/**
* ���Ȱ�����
*
*#include "PackObj.h" <BR>
*-llib
*
* ����ʵ��������࣬�������ס�󣬽�ʹ��������������
*
* @seesomething
*/
class LengthenPack :public PackObj
{
public:

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	LengthenPack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param isLengthen ������������ֵ��Ĭ��Ϊtrue
	*/
	LengthenPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*��������
	*/
	~LengthenPack();

	
};
#endif
