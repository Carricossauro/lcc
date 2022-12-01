//
// Created by tiago on 24/04/22.
//


#include "structs.h"


Point::Point(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
}


Translate::Translate(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
}

void Translate::apply() {
        glTranslatef(x, y, z);
}

RotateAngle::RotateAngle(float angle, float x, float y, float z) {
        this->angle = angle;
        this->x = x;
        this->y = y;
        this->z = z;
}

void RotateAngle::apply() {
        glRotatef(angle, x, y, z);
}


RotateTime::RotateTime(float time, float x, float y, float z) {
        this->time = time * 1000;
        this->x = x;
        this->y = y;
        this->z = z;
}

void RotateTime::apply() {
        float angle = glutGet(GLUT_ELAPSED_TIME)*360/time;
        glRotatef(angle, x, y, z);
}


Scale::Scale(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
}

void Scale::apply() {
        glScalef(x, y, z);
}

Curve::Curve(std::vector<Point> points, bool align, float time) {
        this->t = 0;
        this->control_points = points;
        this->time = time*1000;
        this->current_time = 0;
        this->align = align;
        this->prev_y[0] = 0;
        this->prev_y[1] = 1;
        this->prev_y[2] = 0;
}
void Curve::apply() {
        float pos[3], deriv[3];
        //renderCatmullRomCurve(this->control_points);
        getGlobalCatmullRomPoint(t, pos, deriv, control_points);

        glTranslatef(pos[0], pos[1], pos[2]);
        if (align) {
            float x[3] = {deriv[0], deriv[1], deriv[2]};
            float y[3];
            float z[3];
            float m[16];

            normalize(x);
            cross(x, prev_y, z);
            normalize(z);
            cross(z, x, y);

            normalize(y);
            memcpy(prev_y, y, 3*sizeof(float));

            buildRotMatrix(x, y, z, m);
            glMultMatrixf(m);
        }
        float new_time = glutGet(GLUT_ELAPSED_TIME);
        float diff = new_time - current_time;

        t += diff/time;
        current_time = new_time;
}

LightPoint::LightPoint(float a, float b, float c, int i) {
    this->pos[0] = a;
    this->pos[1] = b;
    this->pos[2] = c;
    this->pos[3] = 1.0f;
    this->index = getLight(i);
}

void LightPoint::apply() {
    glLightfv(this->index, GL_POSITION, this->pos);
}

LightDirectional::LightDirectional(float a, float b, float c, int i) {
    this->dir[0] = a;
    this->dir[1] = b;
    this->dir[2] = c;
    this->dir[3] = 0.0f;
    this->index = getLight(i);
}

void LightDirectional::apply() {
    glLightfv(this->index, GL_POSITION, this->dir);
}

LightSpotlight::LightSpotlight(float a, float b, float c, float da, float db, float dc, GLfloat ct, int i) {
    this->pos[0] = a;
    this->pos[1] = b;
    this->pos[2] = c;
    this->pos[3] = 1.0f;
    this->dir[0] = da;
    this->dir[1] = db;
    this->dir[2] = dc;
    this->dir[3] = 0.0f;
    this->cutoff = ct;
    this->index = getLight(i);
}

void LightSpotlight::apply() {
    glLightfv(this->index, GL_POSITION, this->pos);
    glLightfv(this->index, GL_SPOT_DIRECTION, this->dir);
    glLightfv(this->index, GL_SPOT_CUTOFF, &(this->cutoff));
}

Diffuse::Diffuse(float a, float b, float c) {
    this->rgb[0] = a;
    this->rgb[1] = b;
    this->rgb[2] = c;
    this->rgb[3] = 1.0f;
}

void Diffuse::apply() {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->rgb);
}

Ambient::Ambient(float a, float b, float c) {
    this->rgb[0] = a;
    this->rgb[1] = b;
    this->rgb[2] = c;
    this->rgb[3] = 1.0f;
}

void Ambient::apply() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, this->rgb);
}

Specular::Specular(float a, float b, float c) {
    this->rgb[0] = a;
    this->rgb[1] = b;
    this->rgb[2] = c;
    this->rgb[3] = 1.0f;
}

void Specular::apply() {
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->rgb);
}

Emissive::Emissive(float a, float b, float c) {
    this->rgb[0] = a;
    this->rgb[1] = b;
    this->rgb[2] = c;
    this->rgb[3] = 1.0f;
}

void Emissive::apply() {
    glMaterialfv(GL_FRONT, GL_EMISSION, this->rgb);
}

Shininess::Shininess(float a) {
    this->s = a;
}

void Shininess::apply() {
    glMaterialf(GL_FRONT, GL_SHININESS, this->s);
}


Model::Model(std::string model, std::vector<Transformation*> t, std::vector<Color*> c, GLuint texture) {
    this->model = model;
    this->texture = texture;
    this->transformations = t;
    this->colors = c;
}

Model::Model() {}


void Model::draw(){
        glPushMatrix();
        for (Transformation* t : this->transformations) {
            t->apply();
        }
        for (Color* c : this->colors) {
            c->apply();
        }

        glBindBuffer(GL_ARRAY_BUFFER, vertices);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, normals);
        glNormalPointer(GL_FLOAT, 0, 0);
        
        if (this->texture != -1) {
            glBindTexture(GL_TEXTURE_2D, this->texture);

            glBindBuffer(GL_ARRAY_BUFFER, textures);
            glTexCoordPointer(2, GL_FLOAT, 0, 0);
        }

        glDrawArrays(GL_TRIANGLES, 0, this->verticeCount);

        float clear[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, clear);
        
        glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();
}


void convertPoint(Point p, float* point) {
        point[0] = p.x;
        point[1] = p.y;
        point[2] = p.z;
}

void buildRotMatrix(float *x, float *y, float *z, float *m) {
    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}



void cross(float *a, float *b, float *res) {
    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *a) {
    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

void multMatrixVector(float *m, float *v, float *res) {
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {
    // catmull-rom matrix
    float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
                         { 1.0f, -2.5f,  2.0f, -0.5f},
                         {-0.5f,  0.0f,  0.5f,  0.0f},
                         { 0.0f,  1.0f,  0.0f,  0.0f}};


    for (int i = 0; i < 3; i++) { // x y z
        float A[4];
        float temp[] = {p0[i], p1[i], p2[i], p3[i]};
        multMatrixVector((float *) m, temp, A);

        // Compute pos = T * A
        // pos[i]
        pos[i] = pow(t, 3) * A[0] + pow(t, 2) * A[1] + t * A[2] + A[3];

        // Compute deriv = T' * A
        // deriv[i]
        deriv[i] = 3 * pow(t, 2) * A[0] + 2 * t * A[1] + A[2];
    }
}


// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, std::vector<Point> p) {
    int POINT_COUNT = p.size();

    float t = gt * POINT_COUNT; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
    indices[1] = (indices[0]+1)%POINT_COUNT;
    indices[2] = (indices[1]+1)%POINT_COUNT;
    indices[3] = (indices[2]+1)%POINT_COUNT;

    float p0[3], p1[3], p2[3], p3[3];
    convertPoint(p[indices[0]], p0);
    convertPoint(p[indices[1]], p1);
    convertPoint(p[indices[2]], p2);
    convertPoint(p[indices[3]], p3);

    getCatmullRomPoint(t, p0, p1, p2, p3, pos, deriv);
}

void renderCatmullRomCurve(std::vector<Point> control_points) {
    // draw curve using line segments with GL_LINE_LOOP
    glDisable(GL_LIGHTING);

    float pos[3], deriv[3];
    float LINE_SEGMENTS = 100;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < LINE_SEGMENTS; i++) {
        getGlobalCatmullRomPoint(1/LINE_SEGMENTS * i, pos, deriv, control_points);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

int getLight(int nLight) {
    int CLight;
    switch (nLight) {
        case 0: CLight = GL_LIGHT0; break;
        case 1: CLight = GL_LIGHT1; break;
        case 2: CLight = GL_LIGHT2; break;
        case 3: CLight = GL_LIGHT3; break;
        case 4: CLight = GL_LIGHT4; break;
        case 5: CLight = GL_LIGHT5; break;
        case 6: CLight = GL_LIGHT6; break;
        case 7: CLight = GL_LIGHT7; break;
        default: exit(1);
    }
    return CLight;
}