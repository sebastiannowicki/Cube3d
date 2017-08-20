#ifndef __CUBE_H__
#define __CUBE_H__

#include "cocos2d.h"
#include "Math3d.h"
#include "Point.h"
#include "consts.h"

USING_NS_CC;

class Cube 
{
    public:
        Cube(int screenX, int screenY, float initAngle);
        ~Cube();
        void Update(float time);
        void Draw(DrawNode *drawNode);
    
private:
    Math3d* math3d;
    point3d *zeroPoints;
    int pointConnections[6][4];
    void ZeroAllPoints();
    void Calculate2D(point3d *points, int nop);


    float angle_x = 0, angle_y = 0, angle_z = 0;
    float deltaAngle = 0.3;
    float rz1 = 356, rz2 = 256, rz3 = 256;
    point3d vz = { 0.0, 0.0, 1.0 };
    int screenX, screenY;
};

#endif // __CUBE_H__
