# Break & Breaks: Design Patterns Course Project 
## Introduction
Our project is to refactor a bricks game based on Cocos-2dx game engine, written in C++ in Jun, 2015.
As the diagram shown below, we have made a hard work to achieve an overall redesign of the program’s architecture and interfaces. The total number of the committed lines is about 30,000+. 

![](https://github.com/ambroseL/Architecture_Pattern/tree/master/Images/contribution.png)

## Implemntation
The main goal of our project is to realize abstraction and decoupling. Several design patterns are taken into consideration, including MVC, component, prototype, delegate, observer, strategy , event queue, game update and loop. The implementations of these patterns are described as follows.

### MVC
The greatest mistake we have make in our previous version is putting all logics into one view class - _BeginLayer_. So the very solution we take first is to apply Model-view-controller(MVC) in our system. It divides a given software application into three interconnected parts: model, view and controller, so as to separate internal representations of information from the ways that information is presented to or accepted from the user. Our other design patterns are mainly used on the base of MVC.

### Component & Decorator
Due to the feature of our game that graphics components have a strong connect with physics ones, we utilize component pattern to composite both components into one entity object. By doing so, when game model object needs to be created, update or destroyed, the tasks can be handled with one function, which is actually handled by calling graphics and physics functions provided by its components. Here is an example of such high coherence design:
![](https://github.com/ambroseL/Architecture_Pattern/tree/master/Images/component.png)

b2Body and Sprite are physics and graphics model classes provided by Cocos-2dx engine, but we do not add them to the _entityObj_ class directly, instead, we use PhysicsComponent and GraphicsComponent to do such work, as a simple implementation of decorator pattern. The benefit is that there would be no more concern about the details of the engine’s API. For all the API functions we would call in the other part of the program, component classes decorate them like this:

```
const b2Vec2 PhysicsComponent::getSpeed() 
{
b2Vec2 vec2(0, 0);
vec2 = body->GetLinearVelocity();
return vec2;
}
Then if the API change in future update, we just need to fix those details in our component classes, not everywhere in the program.
```

### Prototype
As our game produces a large amount of objects at the beginning, computer’s CPU and memory would be under much pressure during the time, and it may break down accordingly. One solution is to use prototype pattern, a more suitable strategy to create many classes at once than factory pattern for C++. The reason is that in C++, it does not have a base class like object in Java, and such base class is the key of factory pattern implementation. To finish production tasks, we first have to declare a _Clone()_ function in the base model class. 

```
EntityObj* EntityObj::Clone()											
{	
return new EntityObj(this->physicsComponent->Clone(), this->graphicsComponent->Clone(),new std::string(this->id->c_str()));
}
Then every model class inherited from it would have a _Clone()_ function as well, though it may override it as necessary when it has extra members besides the inherited ones. Now we need a _spawner_ to spawn our objects. In _ObjSpawner.cpp_, we define:
EntityObj* ObjSpawner::spawnEntity()
{
return prototype->Clone();
}
```

When we need to create objects, first we construct an ObjSpawner by setting its prototype, an EntityObj pointer. Then each time we need a new object like its prototype, we call _spawnEntity()_. By avoiding frequent object constructor callings, a lot of CPU’s work can be saved.

### Delegate
_Layer_ is a special view class in Cocos-2dx engine, it contains all Sprites -the graphics class, and is responsible for scene rendering and update. However, as the game loops to update, such works are not merely for view class, controllers have to play a role, too. It is irrational to add the controller’s logic directly to the view, instead, we delegate it, for example:
```
void GameLayer::update(float delta)
{
gameManager->Update();
step();
}
```
Now, the tasks are done by controller _gameManager_, making the line between view and controller clear.

### Observer
If there is MVC, observer pattern follows. As an indispensable part for view class - it ensures that controller would notify view classes to update when there is a change in model. In our codes, it is used in our _update()_ function, more details are mentioned in the update pattern description.

### Strategy
The core of our game is physics contact - ball to wall, ball to ground, ball to paddle, ball to brick and pack to paddle. We take advantage of different strategies to deal with different situations, and most of these strategies can be abstracted as algorithms. When _ContactListener_ notices there is a contact, it creates corresponding strategy class _EventHandler_, then eventHandler would  _doStrategy()_, last a new event  would be pushed to the _eventQueue_, a queue designed for Event Queue pattern. 

```
void PaddleToBall::doStrategy()
{
b2Vec2 ball_vec;
if (bodyA->GetUserData() == NULL || bodyB->GetUserData() == NULL)
return;
std::string* aid = (std::string*)bodyA->GetUserData();

eventObj* newEvent = new eventObj(SOUND, 0, NULL, contact);
eventQueue.push_back(newEvent);
//thisLayer->playSound();
b2WorldManifold* pos = new b2WorldManifold();
contact->GetWorldManifold(pos);
//thisLayer->playSound();
if (aid->at(0) != 'P')
{

b2Body* temp1 = bodyA;
bodyA = bodyB;
bodyB = temp1;

}
float x = bodyA->GetPosition().x, y = bodyA->GetPosition().y, d;
if (pos->points->y < y + objManager->getPaddleInitialHeight() / pixToMeter - 3.0f)
{
bodyB->SetLinearVelocity(b2Vec2(0, -20.0f));
return;
}
ball_vec = bodyB->GetLinearVelocity();
d = objManager->getPaddleInitialHeight() * 2;
x = abs(pos->points->x - x);
int flag = 1;
if (ball_vec.y > 0)
flag = -1;
if (pos->points->x > bodyA->GetPosition().x)
{
ball_vec.x = x / d * (-ball_vec.y) * 1.8f;
ball_vec.y = sqrt(objManager->getBallSpeed().y * objManager->getBallSpeed().y - ball_vec.x * ball_vec.x) * flag;	
}
else
{
ball_vec.x = -x / d * (-ball_vec.y) * 1.8f;
ball_vec.y = sqrt(objManager->getBallSpeed().y * objManager->getBallSpeed().y - ball_vec.x * ball_vec.x) * flag;
}
bodyB->SetLinearVelocity(ball_vec);
}
```
Codes shown above are how a strategy class _PaddleToBall_ works. And  the class diagram below explains the structure of this mechanism:
![](https://github.com/ambroseL/Architecture_Pattern/tree/master/Images/Strategy.png)

### Event Queue
As mentioned before, _EventHandler_ would add an _eventObj_ to the _eventQueue_ when  it calls _doStrategy()_. The _eventObj_ structure contains the contact event type as well as the ID of the contact object. In every game loop, _GameManager_ checks the _eventQueue_, takes the _eventObj_ out and works according to its data value. Here is the code:
```
void GameManager::handelEventQueue()
{
vector<eventObj*>::iterator il;
for (il = eventQueue.begin(); il != eventQueue.end();)
{
eventObj* newEvent = *il;
if (newEvent == nullptr)
continue;
switch (newEvent->eventType)
{
case PACK://碰撞物体为包裹
{
objManager->packWork(newEvent->Id->at(1));
if (newEvent->Id->at(1) != 'G')
{
objManager->addPack2Reset(newEvent->Id->at(1), newEvent->Id);//将包裹加入到待还原队列
clearResetPack(newEvent->Id->at(1));//将包裹还原函数定时
}
break;
}
case BRICK://碰撞物体为砖块
objManager->updateBrickObj(newEvent->Id, newEvent->contact, newEvent->attack);//更新对应砖块
break;
case SOUND://仅需播放碰撞声音
layer->playSound();
break;
}
il = eventQueue.erase(il);
}
}
```

### Game Loop & Update 
Almost every game has a Game Loop, and relatively few programs outside of games use them. It is the central axle that the clock spins on. Objects hear its ticking through Update Methods. The very first key part of a real game loop: it processes user input, but does not wait for it. The loop always keeps spinning like this:
```
while (true)

{

processInput();

update();

render();

}
```
_processInput()_ handles any user input that has happened since the last call. Then, _update()_ advances the game simulation one step. It runs AI and physics Finally, _render()_ draws the game so the player can see what happened. Thanks to Cocos-2dx engine, we do not need to concern about the how _render()_ actually works. And the _scheduleUpdate()_ API ensures the _Update()_ function would be called in each loop. We have already shown how our _Update()_ in _GameLayer_ is delegated to _GameManager_, and the logic inside is:
```
void GameManager::Update()
{
if (isPause == true)//暂停时不更新
{
return;
}

if (keyleft == true)											//如果左键被按住
objManager->applyForce2Paddle(b2Vec2(-500.0f, 0.0f));
if (keyright == true)											//如果右键被按住
objManager->applyForce2Paddle(b2Vec2(500.0f, 0.0f));

b2Vec2 pos = objManager->getBallPos();
if (pos.y * pixToMeter < -405.0)//如果球掉落屏幕底部
{
HP--;	
if (HP > 0)
{
UIcontroller->updateLifeSprite(HP);
objManager->stickyPackWork(); //等效于粘黏包裹
}
else //无生命值为0，游戏重新开始
{
layer->restartGame();
}

}//球掉落屏幕底部

//处理消息队列
handelEventQueue();	
//删除待删除物体										
objManager->deleteObj();								
//更新各物体
objManager->updateObj();	
//无剩余砖块，进入下一关
if (objManager->getBrickCount() == 0)
layer->toNext();									
}
```

The order inside the _Update()_ method is strictly made, we handle user input in the first place, next we check if the ball is out of screen: the user HP would subtract one, game is over when it is zero. If not, work continues. We handle the eventQueue, then delete objects, update their positions and go to next level if no bricks left. 
Besides the update sequence, the interval between each loop also has a strong influence on the game performance. If it is too short, the game responds more rapidly, though much more burden for computation. If it is too long, the user may find the game lag behind his input and probably lose interests, bad news for a game. Most of the game engines now take flexible length of interval, that means the time depends on how much work we do in one frame. When transplanting the old game version to my Mac, I find the game objects move too fast that results in a splash screen. This is probably because of the computation variance between computers. We also made a misunderstanding of the update mechanism, and game looped at both regular and flexible interval, mixing two strategies together. Now we only call _ScheduleUpdate()_, an API for updating game at each frame so that more users on different platforms would have the same game experience.  

## Distribution
**Liu Lidong**
Team leader, overall architecture design, detailed design and implementation of MVC, Observer, Prototype, Component, Decorator, Delegate, Game Loop & Update patterns, presentation PPT,  project document.

**Yang Zhichao**
Team member, detailed design and implementation of Strategy, Event Queue, Game Loop & Update patterns.
