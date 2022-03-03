#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "tinyxml2.h"

// estrutura que representa um ponto no espaço
struct Point{
    float x,y,z;
    Point(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

// caminho para os ficheiros .3d
std::string path_3d;
// caminho para os ficheiros xml
std::string path_xml;
// vetor de vetores de Point onde sao armazenados os pontos lidos dos ficheiros .3d
std::vector<std::vector<Point>> models;

float alpha = 0.0f, beta = 0.0f, radius = 5.0f;
float eyeX, eyeY, eyeZ, centerX = 0.0, centerY =0.0, centerZ=0.0, upX=0.0, upY=1.0, upZ = 0.0;

// funçao que calcula a posição da camera
void spherical2Cartesian() {

    eyeX = radius * cos(beta) * sin(alpha);
    eyeY = radius * sin(beta);
    eyeZ = radius * cos(beta) * cos(alpha);
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}




/*
void drawPlane(float length, int divisions) {
    float unit = length / divisions;
    float offset = length / 2;
    float x1, x2, z1, z2;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            x1 = i * unit - offset;
            z1 = j * unit - offset;
            x2 = (i+1) * unit - offset;
            z2 = (j+1) * unit - offset;

            glVertex3f(x1, 0, z1);
            glVertex3f(x2, 0, z2);
            glVertex3f(x2, 0, z1);

            glVertex3f(x1, 0, z1);
            glVertex3f(x1, 0, z2);
            glVertex3f(x2, 0, z2);
        }
    }
    glEnd();
}

void drawBox(float length, int divisions) {
    float unit = length / divisions;
    float offset = length / 2;
    float x1, x2, y1, y2, z1, z2;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            x1 = i * unit - offset;
            z1 = j * unit - offset;
            x2 = (i+1) * unit - offset;
            z2 = (j+1) * unit - offset;

            glVertex3f(x1, offset, z1);
            glVertex3f(x2, offset, z2);
            glVertex3f(x2, offset, z1);

            glVertex3f(x1, offset, z1);
            glVertex3f(x1, offset, z2);
            glVertex3f(x2, offset, z2);

            glVertex3f(x2, -offset, z2);
            glVertex3f(x1, -offset, z1);
            glVertex3f(x2, -offset, z1);

            glVertex3f(x1, -offset, z2);
            glVertex3f(x1, -offset, z1);
            glVertex3f(x2, -offset, z2);
        }
    }

    for (int i = 0; i< divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            x1 = i * unit - offset;
            y1 = j * unit - offset;
            x2 = (i+1) * unit - offset;
            y2 = (j+1) * unit - offset;

            glVertex3f(x2, y2, offset);
            glVertex3f(x1, y1, offset);
            glVertex3f(x2, y1, offset);

            glVertex3f(x1, y2, offset);
            glVertex3f(x1, y1, offset);
            glVertex3f(x2, y2, offset);

            glVertex3f(x1, y1, -offset);
            glVertex3f(x2, y2, -offset);
            glVertex3f(x2, y1, -offset);

            glVertex3f(x1, y1, -offset);
            glVertex3f(x1, y2, -offset);
            glVertex3f(x2, y2, -offset);
        }
    }

    for (int i = 0; i< divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            z1 = i * unit - offset;
            y1 = j * unit - offset;
            z2 = (i+1) * unit - offset;
            y2 = (j+1) * unit - offset;

            glVertex3f(offset, y1, z1);
            glVertex3f(offset, y2, z2);
            glVertex3f(offset, y1, z2);

            glVertex3f(offset, y1, z1);
            glVertex3f(offset, y2, z1);
            glVertex3f(offset, y2, z2);

            glVertex3f(-offset, y2, z2);
            glVertex3f(-offset, y1, z1);
            glVertex3f(-offset, y1, z2);

            glVertex3f(-offset, y2, z1);
            glVertex3f(-offset, y1, z1);
            glVertex3f(-offset, y2, z2);
        }
    }

    glEnd();
}

void drawSphere(float radius, float slices, float stacks ) {
    float x1, x2, x3, x4, y1, y2, z1, z2, z3, z4, arch_alfa = 2*M_PI / slices, arch_beta = M_PI / stacks;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            x1 = radius * cos(M_PI_2 - arch_beta * j) * sin(arch_alfa*i);
            x2 = radius * cos(M_PI_2 - arch_beta * (j+1)) * sin(arch_alfa*i);
            x3 = radius * cos(M_PI_2 - arch_beta * (j+1)) * sin(arch_alfa*(i+1));
            x4 = radius * cos(M_PI_2 - arch_beta * j) * sin(arch_alfa*(i+1));

            y1 = radius * sin(M_PI_2 - arch_beta*j);
            y2 = radius * sin(M_PI_2 - arch_beta * (j+1));

            z1 = radius * cos(M_PI_2 - arch_beta * j) * cos(arch_alfa*i);
            z2 = radius * cos(M_PI_2 - arch_beta * (j+1)) * cos(arch_alfa*i);
            z3 = radius * cos(M_PI_2 - arch_beta * (j+1)) * cos(arch_alfa*(i+1));
            z4 = radius * cos(M_PI_2 - arch_beta * j) * cos(arch_alfa*(i+1));

            if(j!=stacks-1) {
                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y2, z3);
            }
            if(j!=0){
                glVertex3f(x1, y1, z1);
                glVertex3f(x3, y2, z3);
                glVertex3f(x4, y1, z4);

            }

        }
    }
    glEnd();
}

void drawCone(float radius, float height, float slices, float stacks) {
    float arch_alfa = 2*M_PI / slices,ratio = height/radius, stack_size = height/stacks;
    float x1, x2, x3, x4, y1, y2, z1, z2, z3, z4, h1, h2, r1, r2;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < slices; i++) {
        x1 = radius * sin(arch_alfa * i);
        x2 = radius * sin(arch_alfa * (i+1));
        z1 = radius * cos(arch_alfa * i);
        z2 = radius * cos(arch_alfa * (i+1));

        glVertex3f(x1, 0, z1);
        glVertex3f(0, 0, 0);
        glVertex3f(x2, 0, z2);
    }

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            h1 = height - (i * stack_size);
            h2 = height - ((i+1) * stack_size);
            r1 = h1 / ratio;
            r2 = h2 / ratio;

            x1 = r1 * sin(arch_alfa * j);
            x2 = r1 * sin(arch_alfa * (j+1));
            x3 = r2 * sin(arch_alfa * (j+1));
            x4 = r2 * sin(arch_alfa * j);
            y1 = height - h1;
            y2 = height - h2;
            z1 = r1 * cos(arch_alfa * j);
            z2 = r1 * cos(arch_alfa * (j+1));
            z3 = r2 * cos(arch_alfa * (j+1));
            z4 = r2 * cos(arch_alfa * j);

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y1, z2);
            glVertex3f(x4, y2, z4);

            if (i!=stacks-1){
                glVertex3f(x4, y2, z4);
                glVertex3f(x2, y1, z2);
                glVertex3f(x3, y2, z3);

            }
        }
    }

    glEnd();
}*/

// le pontos armazenados em source (fuicheiro .3d) e armazena em models (vetor de vetores de Point)
void getModel(std::string source){
    std::ifstream file_input(source) ;
    float x,y,z;
    std::vector<Point> model;
    while(file_input >> x >> y >> z) {
        model.push_back(Point(x,y,z));
    }
    models.push_back(model);
    file_input.close();
}


// le o ficheiro xml com as configurações
// por fazer
void readXML(std::string source);


// desenha as figuras com os pontos armazenados no vetor models
void drawModels(){
    glColor3f(1.0f, 1.0f, 1.0f);
    for (std::vector<Point> model : models){
        glBegin(GL_TRIANGLES);
        for (Point p : model){
            glVertex3f(p.x,p.y,p.z);
        }
        glEnd();
    }
}


// desenha os eixos x y z
void drawAxis(){

    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-radius,0,0);
    glVertex3f(radius,0,0);

    glColor3f(0.0,1.0,0.0);
    glVertex3f(0,-radius,0);
    glVertex3f(0,radius,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,-radius);
    glVertex3f(0,0,radius);

    glEnd();
    glColor3f(1.0,1.0,1.0);
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ,
              centerX, centerY, centerZ,
              upX, upY, upZ);

    glPolygonMode(GL_FRONT,GL_LINE);

    drawAxis();
    //drawPlane(2,2);
    // drawBox(2,2);
    //drawSphere(1,10,10);
    //drawCone(1, 5, 10, 10);
    drawModels();



    // End of frame
    glutSwapBuffers();
}




void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {

        case GLUT_KEY_RIGHT:
            alpha -= 0.1;
            break;

        case GLUT_KEY_LEFT:
            alpha += 0.1;
            break;

        case GLUT_KEY_UP:
            beta += 0.1f;
            if (beta > 1.5f)
                beta = 1.5f;
            break;

        case GLUT_KEY_DOWN:
            beta -= 0.1f;
            if (beta < -1.5f)
                beta = -1.5f;
            break;

        case GLUT_KEY_PAGE_DOWN:
            radius -= 0.1f;
            if (radius < 0.1f)
                radius = 0.1f;
            break;

        case GLUT_KEY_PAGE_UP:
            radius += 0.1f;
        break;

        default:
            break;
    }
    spherical2Cartesian();
    glutPostRedisplay();

}


int main(int argc, char **argv) {


    // caminho para os ficheiros 3d e xml
    path_3d = "../../3d/";
    path_xml = "../../xml/";

    // estas quatro chamadas sao para substituir por uma unica chamada da função readXML
    getModel(path_3d + "plane.3d");
    getModel(path_3d + "box.3d");
    getModel(path_3d + "sphere.3d");
    getModel(path_3d + "code.3d");

    //readXML(path_xml + "test_1_3.xml");

    spherical2Cartesian();


// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Models");


// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    //glutIdleFunc(renderScene);


    glutSpecialFunc(processSpecialKeys);




//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);



// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
