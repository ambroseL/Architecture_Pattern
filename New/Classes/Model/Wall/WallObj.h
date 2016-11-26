#ifndef _WallObj_H_
#define _WallObj_H_

#include "EntityObj.h"

/**
* ǽ����
*
*#include "EntityObj.h" <BR>
*-llib
*
* ������Ϸ�ı߽磬�洢ǽ��Ļ���������Ϣ
* 
* @seesomething
*/
class WallObj :public EntityObj
{
public:
	
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	WallObj();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*/
	WallObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id);

	/**
	*��������
	*/
	~WallObj();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;
};

#endif
