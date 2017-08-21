#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
      
    
    Director::getInstance()->setDisplayStats(false);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    halfScreenWidth = visibleSize.width / 2;
    halfScreenHeight = visibleSize.height / 2;
    
    drawNode = DrawNode::create();
    cubes = (Cube**)malloc(yCubes * xCubes * sizeof(Cube*));

    float xline = ((visibleSize.width - VALUE) / xCubes);
    float yline = ((visibleSize.height - VALUE) / yCubes);

    for (int y = 0; y < yCubes; y++)
    {
        for (int x = 0; x < xCubes; x++)
        {
            float l = sqrt((x*x) + (y*y)) * 8;
            cubes[y*xCubes + x] = new Cube((xline * x + (xline/2)) + xline, (yline * y + (yline / 2)) + yCubes , l);
        }
    }

    this->addChild(drawNode);
    this->schedule(schedule_selector(HelloWorld::update));    
    return true;
} 

void HelloWorld::update(float time) 
{
    for (int y = 0; y < yCubes; y++)
    {
        for (int x = 0; x < xCubes; x++)
        {
            cubes[y*xCubes + x]->Update(time);    
        }
    }

    drawNode->clear();

    for (int y = 0; y < yCubes; y++)
    {
        for (int x = 0; x < xCubes; x++)
        {
            cubes[y*xCubes + x]->Draw(drawNode);
        }
    }    
}


HelloWorld::~HelloWorld()
{
    if (cubes != NULL) 
    {
        free(cubes);
    }    
}

