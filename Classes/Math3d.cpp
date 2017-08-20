
#include "Point.h"
#include "Math3d.h"
#include <math.h>

void Math3d::make_tables(void)
{
    int index;
    float i;
    float angle = 0;

    for (index = 0, i = 0.0; index<3600; index++, i += 1.0)
    {
        angle = i*0.1;
        tsin[index] = sin(angle*piover180);
        tcos[index] = cos(angle*piover180);
    }
}

void Math3d::rotateX(point3d *input, float angle, int nop)
{
    float mysin, mycos;   
    float y, z;

    mysin = tsin[calc_index(angle)];
    mycos = tcos[calc_index(angle)];
    
    
    for (int index = 0; index<nop; index++)
    {
        y = mycos*input[index].y - (mysin*input[index].z);
        z = mysin*input[index].y + (mycos*input[index].z);
        input[index].y = y;
        input[index].z = z;
    }  
}

void Math3d::rotateY(point3d *input, float angle, int nop)
{
    int index;
    float mysin, mycos;
    float x, z;

    mysin = tsin[calc_index(angle)];
    mycos = tcos[calc_index(angle)];
    

    for (index = 0; index<nop; index++)
    {
        x = mycos*input[index].x + (mysin*input[index].z);
        z = -mysin*input[index].x + (mycos*input[index].z);
        input[index].x = x;
        input[index].z = z;
    }
}

void Math3d::rotateZ(point3d *input, float angle, int nop)
{
    int index;
    float mysin, mycos;
    float x, y;

    mysin = tsin[calc_index(angle)];
    mycos = tcos[calc_index(angle)];
    

    for (index = 0; index<nop; index++)
    {
        x = input[index].x*mycos - (mysin*input[index].y);
        y = input[index].x*mysin + (mycos*input[index].y);
        input[index].x = x;
        input[index].y = y;
    }   
}

void Math3d::translate(point3d *p, float tx, float ty, float tz, int nop)
{
    int index;
    for (index = 0; index<nop; index++)
    {
        p[index].x += tx;
        p[index].y += ty;
        p[index].z += tz;
    }
}

void Math3d::scale(point3d *p, float sx, float sy, float sz, int nop)
{
    int index;
    for (index = 0; index<nop; index++)
    {
        p[index].x *= sx;
        p[index].y *= sy;
        p[index].z *= sz;
    }
}


point3d Math3d::normalize(point3d v)
{
    point3d ret;
    float t = 1 / sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
    ret.x = v.x*t;
    ret.y = v.y*t;
    ret.z = v.z*t;
    return ret;
}

float Math3d::dot_vectors(point3d v1, point3d v2)
{
    point3d v;
    v.x = v1.x*v2.x;
    v.y = v1.y*v2.y;
    v.z = v1.z*v2.z;
    return (v.x + v.y + v.z);
}

point3d Math3d::add_vecors(point3d v1, point3d v2)
{
    point3d v;
    v.x = v1.x + v2.x;
    v.y = v1.x + v2.y;
    v.z = v1.x + v2.z;
    return v;
}

point3d Math3d::sub_vecors(point3d v1, point3d v2)
{
    point3d v;
    v.x = v1.x - v2.x;
    v.y = v1.x - v2.y;
    v.z = v1.x - v2.z;
    return v;
}



int Math3d::calc_index(float angle)
{
    return (int)(angle*10.0);
}

point3d Math3d::make_vector(point3d p1, point3d p2)
{
    point3d v;
    v.x = p2.x - p1.x;
    v.y = p2.y - p1.y;
    v.z = p2.z - p1.z;
    return v;
}

point3d Math3d::cross_vectors(point3d v1, point3d v2)
{
    point3d v;
    v.x = (v1.y * v2.z) - (v1.z * v2.y);
    v.y = (v1.z * v2.x) - (v1.x * v2.z);
    v.z = (v1.x * v2.y) - (v1.y * v2.x);
    return v;
}

float Math3d::calc_angle(point3d v1, point3d v2)
{
    float angle;
    float licz, mian;
    float l1, l2;

    licz = dot_vectors(v1, v2);
    l1 = sqrt((v1.x*v1.x) + (v1.y + v1.y) + (v1.z + v1.z));
    l2 = sqrt((v2.x*v2.x) + (v2.y + v2.y) + (v2.z + v2.z));
    mian = l1*l2;

    angle = acos(licz / mian);
    angle *= (1.0 / piover180);
    return angle;
}
