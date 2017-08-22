
#include "Point.h"
#include "consts.h"

#ifndef __MATH3D_
#define __MATH3D_
class Math3d  
{
    public:
        
        void rotateX(point3d *p, float angle, int nop);        
        void rotateY(point3d *p, float angle, int nop);
        void rotateZ(point3d *p, float angle, int nop);
        void translate(point3d *p, float tx, float ty, float tz, int nop);
        void scale(point3d *p, float sx, float sy, float sz, int nop);
        point3d normalize(point3d v);
        float dot_vectors(point3d v1, point3d v2);
        point3d cross_vectors(point3d v1, point3d v2);
        point3d add_vecors(point3d v1, point3d v2);
        point3d sub_vecors(point3d v1, point3d v2);
        point3d make_vector(point3d p1, point3d p2);
        int calc_index(float angle);
        float calc_angle(point3d v1, point3d v2);
        void make_tables(void);
        float vector_length(point3d p);

private:
    
       float tsin[3600];
       float tcos[3600];

};
#endif // __MATH3D_
