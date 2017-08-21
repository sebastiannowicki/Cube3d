#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Cube.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    ~HelloWorld();
    
    CREATE_FUNC(HelloWorld);

private:
    Cube** cubes = NULL;
    
    cocos2d::DrawNode *drawNode;
    void update(float time);
    int halfScreenWidth = 0;
    int halfScreenHeight = 0;
    int yCubes = 1;
    int xCubes = 1;
};

#endif // __HELLOWORLD_SCENE_H__
