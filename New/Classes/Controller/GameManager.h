#ifndef _GameManager_H_
#define _GameManager_H_
#include "cocos2d.h"
#include "ObjManager.h"
#include "GameSceneManager.h"
#include "Joints.h"

class GameManager
{
	ObjManager* objManager;
	
	GameSceneManager* sceneManager;
	int HP;									/* �������ֵ */

	int brickcount;							/* ��Ҫ�����ש������ */
	
	float speed;							/* ����ٶȵȼ� */

	//std::vector<ObjEvent*> eventQueue;	/* �¼����� */

	bool isWin = false;						/* ���ؿ��Ƿ�ʤ�� */

	static int level;						/* �ؿ��� */

	bool isPause = false;					/* �Ƿ���ͣ�ı�� */

	bool isPauseEnble = true;				/* ��ͣ�˵��ܲ����� */

	bool keyright = false;					/* �Ҽ��Ƿ񱻰�ס */

	bool keyleft = false;					/* ����Ƿ񱻰�ס */

	MouseJoint* mj;							/* ���ؽ� */

public:
	GameManager();
	~GameManager();

	//����¼�����
	bool myOnTouchBegan(Touch *touch, Event *event); //��ʼ�����¼��Ĵ�����
	void myOnTouchMoved(Touch *touch, Event *event); //�����ƶ��¼��Ĵ�����
	void myOnTouchEnded(Touch *touch, Event *event); //���ؽ����¼��Ĵ�����
	void myOnTouchCancelled(Touch *touch, Event *event); //������ֹ�¼��Ĵ�����

	//�����¼�����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//���¼���ʱ�Ĵ�����
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//�ɿ�����ʱ�Ĵ�����

	void Update(float delta);

};
#endif

