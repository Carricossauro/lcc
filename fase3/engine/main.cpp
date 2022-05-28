#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>

#endif

#include <iostream>
#include <fstream>
#include "tinyxml2.h"
#include "structs.h"
#include <map>



std::string path_3d;
std::string path_xml;
std::vector<Model> models;
std::map<std::string, std::vector<float>> modelPoints;
std::map<std::string, GLuint> modelBuffer;

float alpha = 0.0f, beta = 0.0f, radius = 5.0f, radius_diff = 1.0f, speed = 1.0f;
float eyeX, eyeY, eyeZ, centerX = 0.0, centerY =0.0, centerZ=0.0, upX=0.0, upY=1.0, upZ = 0.0,fov=45.0f,near=1.0f,far=1000.0f,
    dx=0, dy=0,dz=0,rx=0,ry=0,rz=0;

void printInfo() {
    printf("\e[1;1H\e[2J");
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

    std::cout << "Speed: " << speed << std::endl;
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


std::vector<float> getPoints(std::string source) {
    std::ifstream file_input(source) ;
    float x,y,z;
    std::vector<float> points;
    while(file_input >> x >> y >> z) {
        points.push_back(x);
        points.push_back(y);
        points.push_back(z);
    }
    file_input.close();
    return points;
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

                    if (t->Attribute("time") == nullptr) {
                        float x, y, z;
                        x = atof(t->Attribute("x"));
                        y = atof(t->Attribute("y"));
                        z = atof(t->Attribute("z"));

                        ts.push_back(new Translate(x, y, z));
                    } else {

                        float time;
                        std::string align;
                        std::vector<Point> curve;
                        time = atof(t->Attribute("time"));
                        align = t->Attribute("align");


                        for (XMLElement *p = t->FirstChildElement("point"); p; p = p->NextSiblingElement("point")) {
                            float x, y, z;
                            x = atof(p->Attribute("x"));
                            y = atof(p->Attribute("y"));
                            z = atof(p->Attribute("z"));

                            curve.push_back(Point(x, y, z));
                        }


                        ts.push_back(new Curve( curve, align == "True", time));
                    }
                } else if (name == "rotate") {
                    float x, y, z, angle, time;
                    x = atof(t->Attribute("x"));
                    y = atof(t->Attribute("y"));
                    z = atof(t->Attribute("z"));
                    if (t->Attribute("time") == nullptr) {
                        angle = atof(t->Attribute("angle"));
                        ts.push_back(new RotateAngle(angle, x, y, z));
                    } else {
                        time = atof(t->Attribute("time"));
                        ts.push_back(new RotateTime(time, x, y, z));
                    }

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
                std::string model = m->Attribute("file");
                if(!modelPoints.count(model)){
                    std::vector<float> points = getPoints(path_3d + model);
                    modelPoints[model] = points;
                }
                models.push_back(Model(model, ts));
            }
        }

        readGroup(group->FirstChildElement("group"), ts);
        group = group->NextSiblingElement("group");
    }
}


void readXML(std::string source) {
    using namespace tinyxml2;

    XMLDocument doc;
    doc.LoadFile(source.data());

    XMLElement *camera = doc.FirstChildElement("world")->FirstChildElement("camera");
    XMLElement *position = camera->FirstChildElement("position");
    eyeX = atof(position->Attribute("x"));
    eyeY = atof(position->Attribute("y"));
    eyeZ = atof(position->Attribute("z"));



    XMLElement *lookAt = camera->FirstChildElement("lookAt");
    centerX = atof(lookAt->Attribute("x"));
    centerY = atof(lookAt->Attribute("y"));
    centerZ = atof(lookAt->Attribute("z"));


    XMLElement *up = camera->FirstChildElement("up");
    upX = atof(up->Attribute("x"));
    upY = atof(up->Attribute("y"));
    upZ = atof(up->Attribute("z"));

    float upNorm = sqrt(upX * upX + upY * upY + upZ * upZ);
    upX /= upNorm;
    upY /= upNorm;
    upZ /= upNorm;

    XMLElement *projection = camera->FirstChildElement("projection");
    fov = atof(projection->Attribute("fov"));
    near = atof(projection->Attribute("near"));
    far = atof(projection->Attribute("far"));

    dx = centerX - eyeX;
    dy = centerY - eyeY;
    dz = centerZ - eyeZ;
    float norm = sqrt(dx * dx + dy * dy + dz * dz);
    dx /= norm;
    dy /= norm;
    dz /= norm;

    rx = dy*upZ - dz*upY;
    ry = dz*upX - dx*upZ;
    rz = dx*upY - dy*upX;


    radius = sqrt((eyeX-centerX) * (eyeX-centerX) + (eyeY-centerY) * (eyeY-centerY) + (eyeZ-centerZ) * (eyeZ-centerZ));
    beta = asin((eyeY-centerY )/radius);
    alpha = asin((eyeX-centerX)/(radius*cos(beta)));


    XMLElement* group = doc.FirstChildElement("world")->FirstChildElement("group");

    std::vector<Transformation*> t;
    readGroup(group, t);
}

void spherical2Cartesian() {

    centerX =  eyeX - cos(beta) * sin(alpha);
    centerY =  eyeY - sin(beta);
    centerZ =  eyeZ - cos(beta) * cos(alpha);


    dx = centerX - eyeX;
    dy = centerY - eyeY;
    dz = centerZ - eyeZ;
    float norm = sqrt(dx * dx + dy * dy + dz * dz);
    dx /= norm;
    dy /= norm;
    dz /= norm;
    rx = dy*upZ - dz*upY;
    ry = dz*upX - dx*upZ;
    rz = dx*upY - dy*upX;
}


void drawModels(){
    glColor3f(1.0f, 1.0f, 1.0f);
    for (Model model : models){
        model.draw();
    }
}


void drawAxis(){

    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(centerX-far,0,0);
    glVertex3f(centerX+far,0,0);

    glColor3f(0.0,1.0,0.0);
    glVertex3f(0,centerY-far,0);
    glVertex3f(0,centerY+far,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,centerZ-far);
    glVertex3f(0,0,centerZ+far);

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

    //glPolygonMode(GL_FRONT,GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //drawAxis();
    drawModels();


    // End of frame
    glutSwapBuffers();
}



void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_RIGHT:
            alpha -= 0.05;
            break;

        case GLUT_KEY_LEFT:
            alpha += 0.05;
            break;

        case GLUT_KEY_DOWN:
            beta += 0.05f;
            if (beta > 1.5f)
                beta = 1.5f;
            break;

        case GLUT_KEY_UP:
            beta -= 0.05f;
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

void processKeys(unsigned char c, int xx, int yy) {
    switch (c) {
        case 'w':
            centerX += speed*dx;
            eyeX += speed*dx;
            centerY += speed*dy;
            eyeY += speed*dy;
            centerZ += speed*dz;
            eyeZ += speed*dz;
            break;
        case 's':
            centerX -= speed*dx;
            eyeX -= speed*dx;
            centerY -= speed*dy;
            eyeY -= speed*dy;
            centerZ -= speed*dz;
            eyeZ -= speed*dz;
            break;
        case 'a':
            centerX -= speed*rx;
            eyeX -= speed*rx;
            centerY -= speed*ry;
            eyeY -= speed*ry;
            centerZ -= speed*rz;
            eyeZ -= speed*rz;
            break;
        case 'd':
            centerX += speed*rx;
            eyeX += speed*rx;
            centerY += speed*ry;
            eyeY += speed*ry;
            centerZ += speed*rz;
            eyeZ += speed*rz;
            break;
        case '+':
            speed *= 2;
            if (speed > 64.0f) speed = 64.0f;
            printInfo();
            break;
        case '-':
            speed /= 2;
            if (speed < 0.1f) speed = 0.1f;
            printInfo();
            break;

    }

    glutPostRedisplay();


}

int main(int argc, char **argv) {
    path_3d = "../../3d/";
    path_xml = "../../xml/";


    spherical2Cartesian();

    if(argc == 2)
        readXML(path_xml + argv[1]);
    else
        readXML(path_xml + "test_3_2.xml");


    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Models");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glewInit();

    // inicializar e armazenar nos vbos
    glEnableClientState(GL_VERTEX_ARRAY);
    GLuint buffers[modelPoints.size()];

    glGenBuffers(modelPoints.size(),buffers);

    int i = 0;
    for (std::pair<std::string, std::vector<float>> element : modelPoints) {
        std::string model = element.first;
        std::vector<float> points = element.second;
        modelBuffer[model] = buffers[i];
        glBindBuffer(GL_ARRAY_BUFFER, modelBuffer[model]);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);
        i++;
    }


    for(Model & group : models){
        group.vertices = modelBuffer[group.model];
        group.verticeCount = modelPoints[group.model].size();
    }


    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    printInfo();
    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}