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

struct Model {
    std::vector<Point> points;
    std::vector<Transformation*> transformations;
    Model(std::vector<Point> p, std::vector<Transformation*> t) {
        this->points = p;
        this->transformations = t;
    }
};

// caminho para os ficheiros .3d
std::string path_3d;
// caminho para os ficheiros xml
std::string path_xml;
// vetor de vetores de Point onde sao armazenados os pontos lidos dos ficheiros .3d
// std::vector<std::vector<Point>> models;
std::vector<Model> models;

float alpha = 0.0f, beta = 0.0f, radius = 5.0f, radius_diff = 1.0f;
float eyeX, eyeY, eyeZ, centerX = 0.0, centerY =0.0, centerZ=0.0, upX=0.0, upY=1.0, upZ = 0.0,fov=45.0f,near=1.0f,far=1000.0f;

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
    gluPerspective(fov ,ratio, near ,far);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

// le pontos armazenados em source (ficheiro .3d) e armazena em models (vetor de vetores de Point)
std::vector<Point> getModel(std::string source) {
    std::ifstream file_input(source) ;
    float x,y,z;
    std::vector<Point> model;
    while(file_input >> x >> y >> z) {
        model.push_back(Point(x,y,z));
    }
    file_input.close();
    return model;
}

void readGroup(tinyxml2::XMLElement *group, std::vector<Transformation*> ts) {
    using namespace tinyxml2;
    std::vector<Transformation*> backup = ts;

    while (group) {
        ts = backup;
        XMLElement *transformation = group->FirstChildElement("transform");

        if (transformation) {
            for (XMLElement *t = transformation->FirstChildElement(); t; t = t->NextSiblingElement()) {
                std::string name = std::string(t->Name());

                if (name == "translate") {
                    float x, y, z;
                    x = atof(t->Attribute("x"));
                    y = atof(t->Attribute("y"));
                    z = atof(t->Attribute("z"));

                    ts.push_back(new Translate(x, y, z));
                } else if (name == "rotate") {
                    float x, y, z, angle;
                    angle = atof(t->Attribute("angle"));
                    x = atof(t->Attribute("x"));
                    y = atof(t->Attribute("y"));
                    z = atof(t->Attribute("z"));

                    ts.push_back(new Rotate(angle, x, y, z));
                } else if (name == "scale") {
                    float x, y, z;
                    x = atof(t->Attribute("x"));
                    y = atof(t->Attribute("y"));
                    z = atof(t->Attribute("z"));

                    ts.push_back(new Scale(x, y, z));
                } else {
                    std::cout << "error: incorrect syntax" << std::endl;
                }
            }
        }

        XMLElement *MODELS = group->FirstChildElement("models");

        if (MODELS) {
            for(XMLElement *m = MODELS->FirstChildElement("model"); m; m = m->NextSiblingElement()) {
                std::vector<Point> points = getModel(path_3d + m->Attribute("file"));

                models.push_back(Model(points, ts));
            }
        }

        readGroup(group->FirstChildElement("group"), ts);
        group = group->NextSiblingElement("group");
    }
}

// le o ficheiro xml com as configurações
void readXML(std::string source) {
    using namespace tinyxml2;

    XMLDocument doc;
    doc.LoadFile(source.data());

    XMLElement *camera = doc.FirstChildElement("world")->FirstChildElement("camera");
    XMLElement *position = camera->FirstChildElement("position");
    eyeX = atof(position->Attribute("x"));
    eyeY = atof(position->Attribute("y"));
    eyeZ = atof(position->Attribute("z"));

    radius = sqrt(eyeX * eyeX + eyeY * eyeY + eyeZ * eyeZ);
    beta = asin(eyeY / radius);
    alpha = asin(eyeX / (radius * cos(beta)));

    XMLElement *lookAt = camera->FirstChildElement("lookAt");
    centerX = atof(lookAt->Attribute("x"));
    centerY = atof(lookAt->Attribute("y"));
    centerZ = atof(lookAt->Attribute("z"));

    XMLElement *up = camera->FirstChildElement("up");
    upX = atof(up->Attribute("x"));
    upY = atof(up->Attribute("y"));
    upZ = atof(up->Attribute("z"));

    XMLElement *projection = camera->FirstChildElement("projection");
    fov = atof(projection->Attribute("fov"));
    near = atof(projection->Attribute("near"));
    far = atof(projection->Attribute("far"));


    XMLElement* group = doc.FirstChildElement("world")->FirstChildElement("group");

    std::vector<Transformation*> t;
    readGroup(group, t);
}

// desenha as figuras com os pontos armazenados no vetor models
void drawModels(){
    glColor3f(1.0f, 1.0f, 1.0f);
    for (Model model : models){
        glPushMatrix();
        for (Transformation* t : model.transformations) {
            t->apply();
        }

        glBegin(GL_TRIANGLES);
        for (Point p : model.points){
            glVertex3f(p.x,p.y,p.z);
        }
        glEnd();
        glPopMatrix();
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
    drawModels();
    //glutWireSphere(0.5,10,1);

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
            radius -= radius_diff;
            if (radius < 0.1f)
                radius = 0.1f;
            break;

        case GLUT_KEY_PAGE_UP:
            radius += radius_diff;
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


    spherical2Cartesian();

    if(argc == 2)
        readXML(path_xml + argv[1]);
    else
        readXML(path_xml + "test_saturno.xml");


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