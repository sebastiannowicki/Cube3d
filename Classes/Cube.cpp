#include "Cube.h"

Cube::Cube(int screenX, int screenY, float initAngle) 
{
    zeroPoints = (point3d *)malloc(NOP * sizeof(point3d));

    angle_x = initAngle;
    angle_y = initAngle;
    angle_z = initAngle;

    this->screenX = screenX;
    this->screenY = screenY;

    pointConnections[0][0] = 0; pointConnections[0][1] = 1; pointConnections[0][2] = 2; pointConnections[0][3] = 3;
    pointConnections[1][0] = 1; pointConnections[1][1] = 5; pointConnections[1][2] = 6; pointConnections[1][3] = 2;
    pointConnections[2][0] = 5; pointConnections[2][1] = 4; pointConnections[2][2] = 7; pointConnections[2][3] = 6;
    pointConnections[3][0] = 4; pointConnections[3][1] = 0; pointConnections[3][2] = 3; pointConnections[3][3] = 7;
    pointConnections[4][0] = 3; pointConnections[4][1] = 2; pointConnections[4][2] = 6; pointConnections[4][3] = 7;
    pointConnections[5][0] = 4; pointConnections[5][1] = 5; pointConnections[5][2] = 1; pointConnections[5][3] = 0;

    ZeroAllPoints();

    math3d = new Math3d();
    math3d->make_tables();
}

Cube::~Cube() {
    free(zeroPoints);    
}

void Cube::Update(float time)
{
    ZeroAllPoints();
    
    float maxAngle = 360;
    float minAngle = 0;

    if (angle_x >= maxAngle) while (angle_x>maxAngle) angle_x -= maxAngle;
    if (angle_y >= maxAngle) while (angle_y>maxAngle) angle_y -= maxAngle;
    if (angle_z >= maxAngle) while (angle_z>maxAngle) angle_z -= maxAngle;
    if (angle_x<minAngle) while (angle_x<minAngle) angle_x += maxAngle;
    if (angle_y<minAngle) while (angle_y<minAngle) angle_y += maxAngle;
    if (angle_z<minAngle) while (angle_z<minAngle) angle_z += maxAngle;

    math3d->rotateX(zeroPoints, angle_x, NOP);
    math3d->rotateY(zeroPoints, angle_y, NOP);
    math3d->rotateZ(zeroPoints, angle_z, NOP);

    math3d->translate(zeroPoints, 0, 0, 0, NOP);
    Calculate2D(zeroPoints, NOP);       

    angle_x += (time * 50);
    angle_y += (time * 50);
    angle_z += (time * 50);
}

void Cube::ZeroAllPoints() 
{
    zeroPoints[0].x = -VALUE; zeroPoints[0].y = VALUE;  zeroPoints[0].z = -VALUE;
    zeroPoints[1].x = VALUE; zeroPoints[1].y = VALUE;  zeroPoints[1].z = -VALUE;
    zeroPoints[2].x = VALUE; zeroPoints[2].y = -VALUE;  zeroPoints[2].z = -VALUE;
    zeroPoints[3].x = -VALUE; zeroPoints[3].y = -VALUE;  zeroPoints[3].z = -VALUE;
    zeroPoints[4].x = -VALUE; zeroPoints[4].y = VALUE;  zeroPoints[4].z = VALUE;
    zeroPoints[5].x = VALUE; zeroPoints[5].y = VALUE;  zeroPoints[5].z = VALUE;
    zeroPoints[6].x = VALUE; zeroPoints[6].y = -VALUE;  zeroPoints[6].z = VALUE;
    zeroPoints[7].x = -VALUE; zeroPoints[7].y = -VALUE;  zeroPoints[7].z = VALUE;
}

void Cube::Calculate2D(point3d *points, int nop) 
{
    int index;
    float temp;

    for (index = 0; index<nop; index++)
    {
        
        temp = 1.0 / (points[index].z + rz1);
        points[index].x = (points[index].x*rz2)*temp;
        points[index].y = (points[index].y*rz3)*temp;
        
    }
}

void Cube::Draw(DrawNode *drawNode) 
{
    for (int index = 0; index < NOS; index++) 
    {
        point3d v1 = math3d->make_vector(zeroPoints[pointConnections[index][0]], zeroPoints[pointConnections[index][1]]);   //dwa wektory ze sciany
        point3d v2 = math3d->make_vector(zeroPoints[pointConnections[index][1]], zeroPoints[pointConnections[index][2]]);
        point3d v = math3d->normalize(math3d->cross_vectors(v1, v2));    //ich iloczyn wektotowy oraz normalizacja
        float ans = math3d->dot_vectors(v, vz);

        if (ans < 0.0) 
        {
            Vec2 points[8];

            Vec2 vl1((int)(zeroPoints[pointConnections[index][0]].x + screenX), (int)(zeroPoints[pointConnections[index][0]].y + screenY));
            Vec2 vl2((int)(zeroPoints[pointConnections[index][1]].x + screenX), (int)(zeroPoints[pointConnections[index][1]].y + screenY));
            Vec2 vl3((int)(zeroPoints[pointConnections[index][1]].x + screenX), (int)(zeroPoints[pointConnections[index][1]].y + screenY));
            Vec2 vl4((int)(zeroPoints[pointConnections[index][2]].x + screenX), (int)(zeroPoints[pointConnections[index][2]].y + screenY));
            Vec2 vl5((int)(zeroPoints[pointConnections[index][2]].x + screenX), (int)(zeroPoints[pointConnections[index][2]].y + screenY));
            Vec2 vl6((int)(zeroPoints[pointConnections[index][3]].x + screenX), (int)(zeroPoints[pointConnections[index][3]].y + screenY));
            Vec2 vl7((int)(zeroPoints[pointConnections[index][3]].x + screenX), (int)(zeroPoints[pointConnections[index][3]].y + screenY));
            Vec2 vl8((int)(zeroPoints[pointConnections[index][0]].x + screenX), (int)(zeroPoints[pointConnections[index][0]].y + screenY));            
           
            points[0] = vl1;
            points[1] = vl2;
            points[2] = vl3;
            points[3] = vl4;
            points[4] = vl5;
            points[5] = vl6;
            points[6] = vl7;
            points[7] = vl8;

            float colorVal = (float)abs((255.0 * ans));
            Color4F color(colorVal, colorVal, colorVal, 1);

            drawNode->drawPolygon(points, 8, color, 0, Color4F::GREEN);
            /*
            Vec2 vl1((int)(zeroPoints[pointConnections[index][0]].x + screenX) , (int)(zeroPoints[pointConnections[index][0]].y + screenY));
            Vec2 vl2((int)(zeroPoints[pointConnections[index][1]].x + screenX) , (int)(zeroPoints[pointConnections[index][1]].y + screenY));            
            drawNode->drawLine(vl1, vl2, Color4F::BLUE);            

            Vec2 vl3((int)(zeroPoints[pointConnections[index][1]].x + screenX) , (int)(zeroPoints[pointConnections[index][1]].y + screenY));
            Vec2 vl4((int)(zeroPoints[pointConnections[index][2]].x + screenX) , (int)(zeroPoints[pointConnections[index][2]].y + screenY));
            drawNode->drawLine(vl3, vl4, Color4F::BLUE);            

            Vec2 vl5 ((int)(zeroPoints[pointConnections[index][2]].x + screenX) , (int)(zeroPoints[pointConnections[index][2]].y + screenY));
            Vec2 vl6 ((int)(zeroPoints[pointConnections[index][3]].x + screenX) , (int)(zeroPoints[pointConnections[index][3]].y + screenY));
            drawNode->drawLine(vl5, vl6, Color4F::BLUE);            

            Vec2 vl7 ((int)(zeroPoints[pointConnections[index][3]].x + screenX) , (int)(zeroPoints[pointConnections[index][3]].y + screenY));
            Vec2 vl8 ((int)(zeroPoints[pointConnections[index][0]].x + screenX) , (int)(zeroPoints[pointConnections[index][0]].y + screenY));
            drawNode->drawLine(vl7, vl8, Color4F::BLUE);
            */
        }
    }
}
