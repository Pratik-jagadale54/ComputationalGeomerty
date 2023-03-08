#include "GeomVector.h"
// #include "gnuplot_iostream.h"

using namespace GeomVector;

FILE *gpFile;

Point::Point(double p1, double p2, double p3)
{
    data[0] = p1;
    data[1] = p2;
    data[2] = p3;
}

Point::Point()
{
    data[0] = 0.0;
    data[1] = 0.0;
    data[2] = 0.0;
}

double Point::operator[](int index)
{
    return (data[index]);
}

Point::~Point()
{
}

Vector::Vector()
{
}

Vector::~Vector()
{
}

bool Vector::SurfaceLoft(Curve c1, Curve c2, int numV, Surface *loftSurface)
{
    if (c1.size() != c2.size())
        return false;

    double deltaV = 1.0 / (numV);
    for (double v = 0; v <= 1.0; v += deltaV)
    {
        Curve c;
        c.resize(c1.size());

        for (int i = 0; i < c1.size(); i++)
        {

            double x = c1[i][0] * (1 - v) + c2[i][0] * v;
            double y = c1[i][1] * (1 - v) + c2[i][1] * v;
            double z = c1[i][2] * (1 - v) + c2[i][2] * v;

            c[i] = Point(x, y, z);
        }
        loftSurface->push_back(c);
    }

    return true;
}

bool Vector::GenerateCircle(Point center, int iRadius, int iNumU, Curve *circle)
{
    if (circle == nullptr)
        circle = new Curve();

    double uAngle = 360 / iNumU;
    for (double angle = 0; angle <= 360.0; angle += uAngle)
    {
        double rAngle = angle * M_PI / 180.0;

        double x = (iRadius * cos(rAngle)) + center.data[0];
        double y = iRadius * sin(rAngle) + center.data[1];
        double z = center.data[2];
        cout << x << " " << y << " " << z << endl;
        circle->push_back(Point(x, y, z));
    }

    return true;
}

bool Vector::GenerateParabola(int iCenterPoint, int iRadius, int iNumU, Curve *parabola)
{

    return true;
}

bool Vector::GenerateBazierCurve(int iNumU, Point p1, Point p2, Point p3, Point p4, Curve *bazier)
{
    if (iNumU <= 0)
        return false;

    double du = 1.0 / iNumU;
    for (double u = 0.0; u <= 1.0; u += du)
    {
        double x = pow(1 - u, 3) * p1[0] + 3 * u * pow(1 - u, 2) * p2[0] + 3 * u * u * (1 - u) * p3[0] + pow(u, 3) * p4[0];
        double y = pow(1 - u, 3) * p1[1] + 3 * u * pow(1 - u, 2) * p2[1] + 3 * u * u * (1 - u) * p3[1] + pow(u, 3) * p4[1];
        double z = pow(1 - u, 3) * p1[2] + 3 * u * pow(1 - u, 2) * p2[2] + 3 * u * u * (1 - u) * p3[2] + pow(u, 3) * p4[2];

        bazier->push_back(Point(x, y, z));
    }

    // cout<< "size of curve :" << bazier.size() <<endl;

    /* for(int i = 0 ; i < bazier.size() ; i++)
    {
        for(int j = 0; j < 3; j++)
            cout<< "bazier = " << bazier[i].data[j];
        cout<<endl;
    } */

    return true;
}

bool Vector::GeneratePlane(int iNumU, int iNumV, Plane plane)
{

    return true;
}

int main(void)
{
    Vector vector;
    Curve c1;
    Curve c2;
    Curve *bazierCurve1 = new Curve();
    Curve *bazierCurve2 = new Curve();
    Surface *surface = new Surface();
    Surface *cylinder = new Surface();
    Curve *circle1 = new Curve();
    Curve *circle2 = new Curve();

    bool status = false;

    status = vector.GenerateBazierCurve(10, Point(0.0, 0.0, 0.0), Point(-4.0, 4.0, 0.0), Point(4.0, 4.0, 0.0), Point(0.0, 0.0, 0.0), bazierCurve1);
    if (status == false)
    {
        return -1;
    }

    status = vector.GenerateBazierCurve(10, Point(0.0, 0.0, -5.0), Point(-4.0, 4.0, -5.0), Point(4.0, 4.0, -5.0), Point(0.0, 0.0, -5.0), bazierCurve2);
    if (status == false)
    {
        return -1;
    }

    status = vector.SurfaceLoft(*bazierCurve1, *bazierCurve2, 10, surface);
    if (status == false)
    {
        return -1;
    }

    status = vector.GenerateCircle(Point(0.0, 0.0, -3.0), 5.0, 30, circle1);
    if (status == false)
    {
        return -1;
    }

    status = vector.GenerateCircle(Point(0.0, 0.0, -5.0), 5.0, 30, circle2);
    if (status == false)
    {
        return -1;
    }

    status = vector.SurfaceLoft(*circle1, *circle2, 30, cylinder);
    if (status == false)
    {
        return -1;
    }

    fopen_s(&gpFile, "cylinder.dat", "w");
    for (int i = 0; i < cylinder->size(); i++)
        for (int j = 0; j < cylinder[0].size(); j++)
            fprintf(gpFile, "%lf %lf %lf\n", cylinder->at(i)[j][0], cylinder->at(i)[j][1], cylinder->at(i)[j][2]);
    fclose(gpFile);

    fopen_s(&gpFile, "Circle1.dat", "w");
    for (int i = 0; i < circle1->size(); i++)
        fprintf(gpFile, "%lf %lf %lf\n", circle1->at(i)[0], circle1->at(i)[1], circle1->at(i)[2]);
    fclose(gpFile);

    fopen_s(&gpFile, "circle2.dat", "w");
    for (int i = 0; i < circle2->size(); i++)
        fprintf(gpFile, "%lf %lf %lf\n", circle2->at(i)[0], circle2->at(i)[1], circle2->at(i)[2]);
    fclose(gpFile);

    fopen_s(&gpFile, "Bazier.dat", "w");
    for (int i = 0; i < bazierCurve1->size(); i++)
        fprintf(gpFile, "%lf %lf %lf\n", bazierCurve1->at(i)[0], bazierCurve1->at(i)[1], bazierCurve1->at(i)[2]);
    fclose(gpFile);

    fopen_s(&gpFile, "Curve.dat", "w");
    for (int i = 0; i < surface->size(); i++)
        for (int j = 0; j < surface[0].size(); j++)
            fprintf(gpFile, "%lf %lf %lf\n", surface->at(i)[j][0], surface->at(i)[j][1], surface->at(i)[j][2]);
    fclose(gpFile);

    return (0);
}
