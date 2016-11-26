#ifndef _LengthPack_H_
#define _LengthPack_H_

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
class LengthPack :public PackObj
{
	bool isLengthen;	/* ��������ֵ��Ϊtrue��ʾ��������������Ϊ���̰��� */
public:

	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	LengthPack();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param id ����ID
	*@param isLengthen ������������ֵ��Ĭ��Ϊtrue
	*/
	LengthPack(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool isLengthen = true);
	
	/**
	*��������
	*/
	~LengthPack();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;
	
	//�����Դ�ȡ

	/**
	*��ȡ������������ֵ
	*/
	const bool getLengthen();

	/**
	*���ð�����������ֵ
	*/
	void setLengthen(bool isLengthen);
};
#endif
