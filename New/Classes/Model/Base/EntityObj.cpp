#include "EntityObj.h"// class implemented

/////////////// PUBLIC///////////////////////

//================= 构造函数 ====================

EntityObj::EntityObj()
{
	this->graphicsComponent = new GraphicsComponent();
	this->physicsComponent = new PhysicsComponent();
	id = nullptr;
}// EntityObj


EntityObj::EntityObj(PhysicsComponent* physicsComponent, GraphicsComponent* graphicsComponent, std::string* id):physicsComponent(physicsComponent),graphicsComponent(graphicsComponent),id(id)
{
}// EntityObj

EntityObj::EntityObj(const EntityObj& entityObj)
{
	this->graphicsComponent = entityObj.graphicsComponent;
	this->physicsComponent = entityObj.physicsComponent;
	this->id = entityObj.id;
}// EntityObj

EntityObj::~EntityObj()
{
}// ~EntityObj

EntityObj* EntityObj::Clone()											
{	
	return new EntityObj(this->physicsComponent->Clone(), this->graphicsComponent->Clone(),new std::string(this->id->c_str()));
}

//==============类的操作 =====================

void EntityObj::Update()
{
}

//==============属性存取 =====================

const float EntityObj::getWidth()										
{
	return this->graphicsComponent->getWidth();
}

const float EntityObj::getHeight()										
{
	return this->graphicsComponent->getHeight();
}

void EntityObj::setWidth(float fWidth)									
{
	this->graphicsComponent->setWidth(fWidth);
	this->physicsComponent->setSize(fWidth, this->getGraphicsComponent()->getSprite()->getContentSize().height);

}

void EntityObj::setHeight(float fHeight)								
{
	this->graphicsComponent->setHeight(fHeight);
	this->physicsComponent->setSize(this->getGraphicsComponent()->getSprite()->getContentSize().width, fHeight);
}

const b2Vec2 EntityObj::getSpeed()
{
	return this->physicsComponent->getSpeed();
}

void EntityObj::setSpeed(b2Vec2 fSpeed)
{
	this->physicsComponent->setSpeed(fSpeed);
}

ParticleSystem* EntityObj::getParticle()
{
	return graphicsComponent->getParticle();
}

void EntityObj::setParticle(ParticleSystem* cps)
{
	graphicsComponent->setParticel(cps);
}

GraphicsComponent* EntityObj::getGraphicsComponent()
{

	return this->graphicsComponent;
}

PhysicsComponent* EntityObj::getPhysicsComponent()
{
	return this->physicsComponent;
}

const std::string* EntityObj::getID()
{
	return this->id;
}

void EntityObj::setID(std::string* id)
{
	this->id = id;
}

b2Vec2 EntityObj::getPosition()
{
	return physicsComponent->getPosition();
}

void EntityObj::setPosition(b2Vec2 pos)
{
	physicsComponent->setPosition(pos);
	graphicsComponent->setPosition(Point(pos.x,pos.y));
}

void EntityObj::setTexture(Texture2D* texture)
{
	if (texture != NULL)
		graphicsComponent->setTexture(texture);
}
