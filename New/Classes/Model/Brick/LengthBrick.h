#ifndef _LengthBrick_H_
#define _LengthBrick_H_

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

class LengthBrick: public BrickObj
{
	bool isLengthen;	/* ��������ֵ��Ϊtrue��ʾ����ש�飬����Ϊ����ש�� */
public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	LengthBrick();

	/**
	*���ι��캯��
	*
	*@param physicsComponent ������
	*@param graphicsComponent ͼ�񲿼�
	*@param bLengthen ��������ֵ��Ĭ��Ϊtrue
	*@param id ����ID
	*@param iHP ש������ֵ��Ĭ��Ϊ1
	*/
	LengthBrick(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id, bool bLengthen = true, int iHP = 1);
	
	/**
	*��������
	*/
	~LengthBrick();

	/**
	*��¡���������
	*/
	EntityObj* Clone() override;

	//�����Դ�ȡ

	/**
	*��ȡש�鳤������ֵ
	*/
	const bool getLengthen();

	/**
	*����ש�鳤������ֵ
	*/
	void setLengthen(bool isLengthen);
};
#endif

