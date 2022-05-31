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
#include <string>



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

class Light{
public:
    int index;
    void virtual apply() = 0;
};

class LightPoint : public Light {
    float pos[4];
public:
    LightPoint(float a, float b, float c, int i);
    void apply();
};

class LightDirectional : public Light{
    float dir[4];
public:
    LightDirectional(float a, float b, float c, int i);
    void apply();
};

class LightSpotlight : public Light{
    float pos[4], dir[4], cutoff;
public:
    LightSpotlight(float a, float b, float c, float da, float db, float dc, float ct, int i);
    void apply();
};

class Color{
public:
    void virtual apply() = 0;
};

class Diffuse : public Color {
    float rgb[4];
public:
    Diffuse(float a, float b, float c);
    void apply();
};

class Ambient : public Color {
    float rgb[4];
public:
    Ambient(float a, float b, float c);
    void apply();
};

class Specular : public Color {
    float rgb[4];
public:
    Specular(float a, float b, float c);
    void apply();
};

class Emissive : public Color {
    float rgb[4];
public:
    Emissive(float a, float b, float c);
    void apply();
};

class Shininess : public Color {
    float s;
public:
    Shininess(float a);
    void apply();
};

struct Model{
    std::string model;
    GLuint texture;
    std::vector<Transformation*> transformations;
    std::vector<Color*> colors;
    GLuint vertices, verticeCount, normals, textures;
    Model(std::string model, std::vector<Transformation*> t, std::vector<Color*>, GLuint texture);
    void draw();

};

void convertPoint(Point p, float* point);

void buildRotMatrix(float *x, float *y, float *z, float *m);

void cross(float *a, float *b, float *res);

void normalize(float *a);


void multMatrixVector(float *m, float *v, float *res);


void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);


void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, std::vector<Point> p);

void renderCatmullRomCurve(std::vector<Point> control_points);

int getLight(int nLight);

#endif //ENGINE_STRUCTS_H
