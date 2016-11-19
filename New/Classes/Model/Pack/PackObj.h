#ifndef _PackObj_H_
#define _PackObj_H_

#include "EntityObj.h"

/**
* ����ʵ����
*
*#include "EntityObj.h" <BR>
*-llib
*
* ����pack��Ļ��࣬�洢�����Ļ���������Ϣ
*
* @seesomething
*/

class PackObj :public EntityObj
{
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	PackObj();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*/
	PackObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);
	
	/**
	*��������
	*/
	~PackObj();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;
};
#endif
