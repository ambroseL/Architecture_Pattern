#ifndef _PermeatPack_H_
#define _PermeatPack_H_

#include "PackObj.h"

/**
* ��͸������
*
*#include "PackObj.h" <BR>
*-llib
*
* ����ʵ��������࣬�������ס�󣬽�ʹ�����ʱ���ڴ����޵�״̬��
* ���ƻ�������ײ��ש�飬�Ҳ���������
*
* @seesomething
*/

class PermeatPack :public PackObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	PermeatPack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*/
	PermeatPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*��������
	*/
	~PermeatPack();
};
#endif
