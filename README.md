# Break & Breaks: Design Patterns Course Project 
## Introduction

![](https://github.com/ambroseL/Architecture_Pattern/raw/master/Images/demo.png)

Our project is to refactor a bricks game based on Cocos-2dx game engine, written in C++ in Jun, 2015.<br />
As the diagram shown below, we work hard to achieve an overall redesign of the program’s architecture and interfaces. The total number of the committed lines is about 30,000+. 

![](https://github.com/ambroseL/Architecture_Pattern/raw/master/Images/contribution.png)

## Implementation
The main goal of our project is to realize abstraction and decoupling. Several design patterns are taken into consideration, including `MVC`, `component`, `prototype`, `delegate`, `observer`, `strategy` , `event queue`, `game update and loop`. The implementation of these patterns are described as follows.

### MVC
The biggest shortcoming of our old version is putting all the logics into one view class - `BeginLayer`, making it so hard to maintain the whole project. The very solution we take is to apply `MVC(Model-view-controller)pattern`, which divides a given software application into three interconnected parts: model, view and controller, so as to separate internal representations of information from the ways that information is presented to or accepted from the user. Our other design patterns are mainly based of MVC.
Here is the overall architecture of our game:

![](https://github.com/ambroseL/Architecture_Pattern/raw/master/Images/Overall.png)

### Component & Decorator
Due to the feature of our game that graphics components have a strong connection with physics ones, we utilize `component pattern` to composite them into one `EntityObj`. By doing so, when an `EntityObj` needs to be created, update or destroyed, we can just call graphics and physics functions provided by its components. Here is an example of such high coherence design:

![](https://github.com/ambroseL/Architecture_Pattern/raw/master/Images/component.png)

b2Body and Sprite are physics and graphics model classes provided by Cocos-2dx engine, but we do not add them to the `entityObj` directly, instead, we use PhysicsComponent and GraphicsComponent to do so, as an implementation of `decorator pattern`. The benefit is that there would be no more concern about the details of the engine’s API. For all the API functions we would call in other parts of the program, component classes decorate them like this:

```C++
const b2Vec2 PhysicsComponent::getSpeed() 
{
  b2Vec2 vec2(0, 0);
  vec2 = body->GetLinearVelocity();
  return vec2;
}
```
Then if the API change in future update, we just need to fix them in our component classes, not everywhere in the program.

### Prototype
At the beginning of each scene, initializing a large amount of objects is such a big burden for computer’s CPU and memory,even brings about break down. One solution is to use `prototype pattern`, a more suitable way for mass production than `factory pattern` in C++. The reason is that C++ does not have a base class like `Object` in Java, and such base class is the key of `factory pattern` implementation. To accomplish such tasks, we declare a `Clone()` function in the base model class. 

```C++
EntityObj* EntityObj::Clone()											
{	
  return new EntityObj(this->physicsComponent->Clone(), this->graphicsComponent->Clone(),new std::string(this->id->c_str()));
}
```
Then every model class inherited from it would have a `Clone()` function as well, though it may override it as necessary when there are extra members besides the inherited ones. Now we need a `spawner` to spawn our objects. In `ObjSpawner.cpp`, we define:

```C++
EntityObj* ObjSpawner::spawnEntity()
{
  return prototype->Clone();
}
```

When it comes to create objects, first we construct an ObjSpawner by setting its prototype, an `EntityObj` pointer. Then each time we need a new object like its prototype, we call `spawnEntity()`. By avoiding frequent object constructor callings, a lot of CPU’s work could be saved.
To make it more clear, class diagram is shown below:

![](https://github.com/ambroseL/Architecture_Pattern/raw/master/Images/prototype.png)

### Delegate
`Layer` is a special view class in Cocos-2dx engine, it contains all Sprites - the graphics class, and is responsible for scene rendering and update. However, more complicated things happen during the update looping, and such works are beyond view class responsibilities. Controllers have to play a role, too. It is irrational to add all the controller’s logic directly to the view, instead, we delegate it, for example:

```C++
void GameLayer::update(float delta)
{
  gameManager->Update();//场景更新逻辑
  step();//物理世界更新逻辑
}
```
Now, a part of the tasks is done by `gameManager`, a controller, making the border between view and controller clear.

### Observer
When there is a `MVC`, `observer pattern` follows. As an indispensable part of view class - it ensures controller would notify view class to update when there is a change in model. In our codes, it is used in `update()` function, more details would be told in `update pattern`.

### Strategy
Physics simulation, the core of our game, includes ball to wall, ball to ground, ball to paddle, ball to brick and pack to paddle contact. We take advantage of `strategy pattern`,abstract algorithms as stratgies in different situations. When `ContactListener` notices there is a contact, it creates corresponding strategy class `EventHandler`, then eventHandler would  `doStrategy()`. Eventually, a new `EventObj` would be pushed to `eventQueue`, a queue designed for `Event Queue pattern`. 

```C++
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
Codes above are how the strategy class `PaddleToBall` works. And the class diagram below explains the structure of this mechanism:
![](https://github.com/ambroseL/Architecture_Pattern/raw/master/Images/Strategy.png)

### Event Queue
As mentioned before, `EventHandler` adds an `EventObj` to `eventQueue` when calling `doStrategy()`. The `EventObj` is a structure containing the contact event type as well as the ID of the contact object. In every game loop, `GameManager` checks the `eventQueue`, takes `EventObj` out and works according to its data value. Here is the code:

```C++
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

```C++
while (true)
{
  processInput();
  update();
  render();
}
```
`processInput()` handles any user input that has happened since the last call. Then, `update()` advances the game simulation one step. It runs AI and physics Finally, `render()` draws the game so the player can see what happened. Thanks to Cocos-2dx engine, we do not need to concern about the how `render()` actually works. And the `ScheduleUpdate()` API ensures the `Update()` function would be called in each loop. We have already shown how our `Update()` in `GameLayer` is delegated to `GameManager`, and the logic inside is:

```C++
void GameManager::Update()
{
  if (isPause == true)//暂停时不更新
    return;
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

The order of logic inside `Update()` is strictly execuded: we handle user input in the first place, next we check whether the ball is out of the screen: if true, the user's HP subtracts one, game is over when it is zero. Otherwise, work continues. We check `eventQueue`, then delete objects, update their positions and go to next level if no bricks left. 
Besides update sequence, the interval between each loop also has a strong influence on game performance. If it is too short, the game reacts more timely, though much more burden for computation. While it is too long, the user may find the game lag behind his input and probably lose interests, bad news for a game. Most of the game engines now take flexible length of interval, which means the time depends on how much work we do in one frame. When transplanting the old game version to my new laptop, I find the game objects move too fast that results in a splash screen. This is probably because computation ability varies between computers. Another reason is that previously, we misunderstood the update mechanism, made the game loop at both regular and flexible interval. Now we only call `ScheduleUpdate()`, a Cocos API for updating game at each frame so that more users on different platforms would have the same game experience.  

## Distribution
**Liu Lidong**<br />
Team leader, overall architecture design, detailed design and implementation of MVC, Observer, Prototype, Component, Decorator, Delegate, Game Loop & Update patterns, presentation PPT,  project document.<br />
**Yang Zhichao**<br />
Team member, detailed design and implementation of Strategy, Event Queue, Game Loop & Update patterns.
