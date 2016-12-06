#ifndef  _globalObj_H_
#define  _globalObj_H_
#include <vector>
#include "Box2D/Dynamics/Contacts/b2Contact.h"
using namespace std;
/**
* ȫ�ֱ���
*
*#include <vector>
*#include "Box2D/Dynamics/Contacts/b2Contact.h"
*"GraphicsComponent.h" <BR>
*-llib
*
* ȫ�ֱ���������Ϣ���У����а�����Ϣ�ṹ��
*
* @seesomething
*/

#define PACK 1
#define BRICK 2
#define SOUND 3


extern struct eventObj
{
	eventObj() {}
	eventObj(int eventtype, int _attack, std::string* id, b2Contact* _contact)
	{
		eventType = eventtype;
		attack = _attack;
		Id = id;
		contact = _contact;
	}
	int eventType;
	int attack;
	string* Id;
	b2Contact* contact;
};//�Զ�����Ϣ�ṹ��

extern vector<eventObj*> eventQueue;//��Ϣ����

#endif