//
// Created by tiago on 24/04/22.
//

#ifndef ENGINE_STRUCTS_H
#define ENGINE_STRUCTS_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <math.h>
#include "structs.h"
#include "string.h"


struct Point{
    float x,y,z;
    Point(float x, float y, float z);
};


class Transformation {
public:
    void virtual apply() = 0;
};

class Translate : public Transformation{
    float x, y, z;
public:
    Translate(float x, float y, float z);
    void apply();
};

class RotateAngle : public Transformation{
    float x, y, z, angle;
public:
    RotateAngle(float angle, float x, float y, float z);

    void apply();
};

class RotateTime : public Transformation{
    float x, y, z, time;
public:
    RotateTime(float time, float x, float y, float z);
    void apply();
};

class Scale : public Transformation{
    float x, y, z;
public:
    Scale(float x, float y, float z);
    void apply();
};

class Curve : public Transformation {
    float t, time, current_time;
    std::vector<Point> control_points;
    bool align;
    float prev_y[3];
public:
    Curve(std::vector<Point> points, bool align, float time);

    void apply();

};

struct Model {
    //std::vector<Point> points;
    std::vector<float> vertexB;
    std::vector<Transformation*> transformations;
    GLuint vertices, verticeCount;
    Model(std::vector<Point> p, std::vector<Transformation*> t);
    void bind();
    void draw();

};

void convertPoint(Point p, float* point);

void buildRotMatrix(float *x, float *y, float *z, float *m);

void cross(float *a, float *b, float *res);

void normalize(float *a);

float length(float *v);

void multMatrixVector(float *m, float *v, float *res);


void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);


void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, std::vector<Point> p);

void renderCatmullRomCurve(std::vector<Point> control_points);

#endif //ENGINE_STRUCTS_H
