#ifndef _GameManager_H_
#define _GameManager_H_
#include "cocos2d.h"
#include "GameLayer.h"
#include "SceneManager.h"
#include "UIController.h"
#include "MyJoints.h"
#include "ObjManager.h"
#include "globalObj.h"

/**
* ��Ϸ������
*
* #include "GameManager.h"
* #include "SceneManager.h"
* #include "GameLayer.h"
* -llib
*
* ������Ϸ����ʱ�������߼��������û����룬��������
* Э����ϸ������ദ���ۺ�ҵ��
*
* @seesomething
*/

class GameManager
{
	ObjManager* objManager;					/* model������ */
	
	SceneManager* sceneManager;			/* ���������� */

	UIController* UIcontroller;				/* UI������ */

	int HP;									/* �������ֵ */

	bool isWin = false;						/* ���ؿ��Ƿ�ʤ�� */
	
	bool isPausable = false;				/* ��ͣ�˵��ܲ����� */

	bool isPause = false;					/* �Ƿ���ͣ�ı�� */			

	bool keyright = false;					/* �Ҽ��Ƿ񱻰�ס */

	bool keyleft = false;					/* ����Ƿ񱻰�ס */

	MyMouseJoint* mj;						/* ���ؽ� */

	GameLayer* layer;						/* ����ĵ�ǰlayer */

public:
	// ����������ڿ��ƺ������������������	

	/**
	*Ĭ�Ϲ��캯��
	*/
	GameManager();

	/**
	*��������
	*/
	~GameManager();

	//�����

	/**
	 *��ʼ������Ա
	 */
	void init();									

	/**
	*��ʼ����ָ����������������
	*@parameter layer ����ʼ���ĳ���
	*@parameter world ����ʼ������������
	*/
	void initLayer(GameLayer* layer, b2World* world);	//���������е����뵲��

	/**
	 *����ָ��������ש��
	 *@parameter layer ������ש��ĳ���
	 *@parameter world ������ש�����������
	 */
	void createLayerBricks(GameLayer* layer, b2World* world) const; //���������е�ש��

	/**
	 *����¼�����
	 *@parameter touch ������
	 *@parameter event �����¼�
	 */
	bool myOnTouchBegan(Touch *touch, Event *event); //��ʼ�����¼��Ĵ�����
	void myOnTouchMoved(Touch *touch, Event *event); //�����ƶ��¼��Ĵ�����
	void myOnTouchEnded(Touch *touch, Event *event); //���ؽ����¼��Ĵ�����
	void myOnTouchCancelled(Touch *touch, Event *event); //������ֹ�¼��Ĵ�����

	/**
	 *�����¼�����
	 *@parameter keycode ���̰���
	 *@parameter event �����¼�
	 */
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//���¼���ʱ�Ĵ�����
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);//�ɿ�����ʱ�Ĵ�����

	/**
	 *��ͣ��Ϸ
	 */
	void toPause();

	/**
	*�˵���ͣ
	*/
	void menuePause();

	/**
	*������һ��Ϸ�ؿ�
	*/
	void goNext();

	/**
	*�˵�����
	*/
	void menueReset();

	/**
	*���׷�����ǿ���л�����һ��Ϸ�ؿ�
	*/
	void toNext();

	/**
	*�˵�����
	*/
	void menueBack();

	/**
	*�˵�����
	*/
	void menueContinue();

	/**
	*�˵�ǰ����һ��
	*/
	void menueNext();

	/**
	*������Ϸ
	*/
	void restartGame();

	/**
	*��Ϸ����
	*/
	void Update();

	/**
	*��������
	*/
	void playSound();

	/**
	*�������ԭ�����б�
	*/
	void clearResetPack(char sid);

	/**
	*�����¼�����
	*/
	void handelEventQueue();

	/**
	*�����Ͱ�����ԭ������delegate��objManger���
	*/
	void resetAcceleratePack();

	void resetDeacceleratePack();

	void resetImagePack();

	void resetLengthenPack();

	void resetPermeatPack();

	void resetReversalPack();

	void resetShortenPack();

	void resetUpgradePack();

	//�����Դ�ȡ

	/**
	 *��ȡ���������
	 */
	ObjManager* getObjManager() const { return this->objManager; }//���������е�ש��

	/**
	 *���ó���������
	 *@parameter manager �����õĳ���������
	 */
	void setSceneManager(SceneManager* manager);//���������е�ש��

	/**
	 *��ȡ���徫�飬delegate��objManager����
	 */
	Sprite* getPaddelSprite() const;
};
#endif

