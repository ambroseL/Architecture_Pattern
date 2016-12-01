#ifndef  _globalObj_H_
#define  _globalObj_H_
#include <vector>
using namespace std;

typedef struct EventObj
{
	EventObj() {}
	EventObj(int eventtype, int hp, std::string* id)
	{
		eventType = eventtype;
		HP = hp;
		Id = id;
	}
	int eventType;
	int HP;
	string* Id;
}eventObj;

vector<eventObj*> eventQueue;

#endif