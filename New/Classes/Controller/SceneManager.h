#ifndef  _SceneManager_H_
#define  _SceneManager_H_
#include "cocos2d.h"
using namespace cocos2d;
/**
* ����������
*
* #include "cocos2d.h"
* -llib
* ��������Ĵ������л�
* ��������
*
* @seesomething
*/

class SceneManager
{
public:
	//�����

	/**
	 *������������ķ���
	 */
	void createScene();

	/**
	*ȥ��Ϸ�����ķ���
	*/
	void gogameScene();

	/**
	 *ȥ�ڶ��صķ���
	 */
	void goRound2Scene();

	/**
	 *ȥ�����صķ���
	 */
	void goRound3Scene();

	/**
	 *��һ�����¿�ʼ�ķ���
	 */
	void reStart();

	/**
	 *�ڶ������¿�ʼ�ķ���
	 */
	void reStart2();

	/**
	 *���������¿�ʼ�ķ���
	 */
	void reStart3();

	/**
	 *�ػ�ӭ�����ķ���
	 */
	void goStartScene();

	/**
	 *ȥ��������
	 */
	void goHelpScene();;
};
#endif
