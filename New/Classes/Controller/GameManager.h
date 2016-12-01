#ifndef _GameManager_H_
#define _GameManager_H_
#include "cocos2d.h"
#include "GameLayer.h"
#include "SceneManager.h"
#include "UIController.h"
#include "MyJoints.h"
#include "ObjManager.h"

class GameLayer;

class GameManager
{
	ObjManager* objManager;					/* model������ */
	
	SceneManager* sceneManager;			/* ���������� */

	UIController* UIcontroller;				/* UI������ */

	//EventHandler* eventHandler;			/* �¼������� */

	int HP;									/* �������ֵ */

	int brickcount;							/* ��Ҫ�����ש������ */

	//std::vector<ObjEvent*> eventQueue;	/* �¼����� */

	bool isWin = false;						/* ���ؿ��Ƿ�ʤ�� */
	
	bool isPausable = false;				/* ��ͣ�˵��ܲ����� */

	bool isPause = false;					/* �Ƿ���ͣ�ı�� */			

	bool keyright = false;					/* �Ҽ��Ƿ񱻰�ס */

	bool keyleft = false;					/* ����Ƿ񱻰�ס */

	MyMouseJoint* mj;						/* ���ؽ� */

	GameLayer* layer;						/* ����ĵ�ǰlayer */

public:
	GameManager();
	~GameManager();

	void init();									//��ʼ������Ա

	void createLayerObj(GameLayer* layer, b2World* world);	//���������еĸ�����

	//����¼�����
	bool myOnTouchBegan(Touch *touch, Event *event); //��ʼ�����¼��Ĵ�����
	void myOnTouchMoved(Touch *touch, Event *event); //�����ƶ��¼��Ĵ�����
	void myOnTouchEnded(Touch *touch, Event *event); //���ؽ����¼��Ĵ�����
	void myOnTouchCancelled(Touch *touch, Event *event); //������ֹ�¼��Ĵ�����

	//�����¼�����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//���¼���ʱ�Ĵ�����
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//�ɿ�����ʱ�Ĵ�����

	void toPause();

	void menuePause();

	void goNext();

	void menueReset();

	void toNext();

	void menueBack();

	void menueContinue();

	void menueNext();

	void restartGame();

	void Update();

	void playSound();

	void clearResetPack(char sid);

	Sprite* getPaddelSprite() const;
};
#endif

