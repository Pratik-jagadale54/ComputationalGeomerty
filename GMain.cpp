#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "GVector.h"

using namespace GeomVector;

FILE *gpFile;

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

    fopen_s(&gpFile, "./DatFiles/cylinder.dat", "w");
    for (int i = 0; i < cylinder->size(); i++)
        for (int j = 0; j < cylinder[0].size(); j++)
            fprintf(gpFile, "%lf %lf %lf\n", cylinder->at(i)[j][0], cylinder->at(i)[j][1], cylinder->at(i)[j][2]);
    fclose(gpFile);

    fopen_s(&gpFile, "./DatFiles/Circle1.dat", "w");
    for (int i = 0; i < circle1->size(); i++)
        fprintf(gpFile, "%lf %lf %lf\n", circle1->at(i)[0], circle1->at(i)[1], circle1->at(i)[2]);
    fclose(gpFile);

    fopen_s(&gpFile, "./DatFiles/circle2.dat", "w");
    for (int i = 0; i < circle2->size(); i++)
        fprintf(gpFile, "%lf %lf %lf\n", circle2->at(i)[0], circle2->at(i)[1], circle2->at(i)[2]);
    fclose(gpFile);

    fopen_s(&gpFile, "./DatFiles/Bazier.dat", "w");
    for (int i = 0; i < bazierCurve1->size(); i++)
        fprintf(gpFile, "%lf %lf %lf\n", bazierCurve1->at(i)[0], bazierCurve1->at(i)[1], bazierCurve1->at(i)[2]);
    fclose(gpFile);

    fopen_s(&gpFile, "./DatFiles/Curve.dat", "w");
    for (int i = 0; i < surface->size(); i++)
        for (int j = 0; j < surface[0].size(); j++)
            fprintf(gpFile, "%lf %lf %lf\n", surface->at(i)[j][0], surface->at(i)[j][1], surface->at(i)[j][2]);
    fclose(gpFile);

    return (0);
}
