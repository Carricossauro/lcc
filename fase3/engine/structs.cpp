#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>


struct Point{
    float x,y,z;
    Point(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

class Transformation {
public:
    void virtual apply() = 0;
};

class Translate : public Transformation{
    float x, y, z;
public:
    Translate(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void apply() {
        glTranslatef(x, y, z);
    }
};

class Rotate : public Transformation{
    float x, y, z, angle;
public:
    Rotate(float angle, float x, float y, float z) {
        this->angle = angle;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void apply() {
        glRotatef(angle, x, y, z);
    }
};

class Scale : public Transformation{
    float x, y, z;
public:
    Scale(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void apply() {
        glScalef(x, y, z);
    }
};

class Curve : public Transformation {
    float t, time;
    std::vector<Point> control_points;
    bool align;
public:
    Curve(float t, std::vector<Point> points, bool align, float time) {
        this->t = t;
        this->control_points = points;
        this->time = time;
        this->align = align;
    }

    void apply() {

    }

};

struct Model {
    std::vector<Point> points;
    std::vector<Transformation*> transformations;
    Model(std::vector<Point> p, std::vector<Transformation*> t) {
        this->points = p;
        this->transformations = t;
    }
};