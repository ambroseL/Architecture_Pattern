#ifndef _ObjSpawner_H_
#define _ObjSpawner_H_
#include "EntityObj.h"
/**
* �����������
*
*#include "EntityObj.h"
*-llib
*
* ʵ���������������
*
* @seesomething
*/


class ObjSpawner
{

	EntityObj* prototype;						/* ����ԭ�� */
public:
	// ����������ڿ��ƺ������������������	

	/**
	*���ι��캯��
	*/
	ObjSpawner(EntityObj* prototype);

	/**
	*��������
	*/
	~ObjSpawner();

	//�����
	
	/**
	 * ��������
	 */
	EntityObj* spawnEntity();

	/**
	 *���÷������ķ���ԭ��
	 *@parameter prototype 
	 */
	void setPrototype(EntityObj* prototype);
};
#endif

