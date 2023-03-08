#ifndef _GEOM_VECTOR_
#define _GEOM_VECTOR_

#define _USE_MATH_DEFINES

#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>

using namespace std;

namespace GeomVector
{
    #define SUCCESS 0
    #define FAILED -1

    class Point
    {
    private:
            /* data */
    public:
        double data[3];
        Point();
        Point(double p1, double p2, double p3);
        double operator[](int index);
        void operator()(int index, double value);
        ~Point();
    };

    typedef vector<Point> Curve;
    typedef vector<Point> Line;
    typedef vector<Line> Plane;
    typedef vector<Curve > Surface;

    class Vector
    {
    private:
        /* data */
    public:
        Vector(/* args */);
        ~Vector();

        bool SurfaceLoft(Curve c1, Curve c2, int numV, Surface* loftSurface);
        bool GenerateCircle(Point center, int iRadius, int iNumU,  Curve *circle);
        bool GenerateParabola(int iCenterPoint, int iRadius, int iNumU,  Curve *parabola);
        bool GenerateBazierCurve(int iNumU,  Point p1, Point p2 , Point p3, Point p4, Curve* bazier);
        bool GenerateCylider(int iCenterPoint, int iRadius, int iNumU,  Curve* circle);

        bool GeneratePlane(int iNumU, int iNumV, Plane plane);
        //bool GenerateCylinder(int iNumU, int iNumV, Surface cylinder);

    };
    
    
} // namespace GeomVector

#endif // _GEOM_VECTOR_