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
std::map<std::string, std::vector<float>> modelNormals;
std::map<std::string, GLuint> modelBufferPoints;
std::map<std::string, GLuint> modelBufferNormals;
std::vector<Light*> lights;

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


void getPoints(std::string source, std::vector<float> &points, std::vector<float> &normals) {
    std::ifstream file_input(source) ;
    float x, y, z, nx, ny, nz;
    while(file_input >> x >> y >> z >> nx >> ny >> nz) {
        points.push_back(x);
        points.push_back(y);
        points.push_back(z);

        normals.push_back(nx);
        normals.push_back(ny);
        normals.push_back(nz);
    }
    file_input.close();
}

void readGroup(tinyxml2::XMLElement *group, std::vector<Transformation*> ts) {
    using namespace tinyxml2;
    std::vector<Transformation*> backupTransformations = ts;

    while (group) {
        ts = backupTransformations;
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
                    std::vector<float> points, normals;
                    getPoints(path_3d + model, points, normals);
                    modelPoints[model] = points;
                    modelNormals[model] = normals;
                }

                std::vector<Color*> colors;
                XMLElement* COLORS = m->FirstChildElement("color");
                for (XMLElement *COLOR = COLORS->FirstChildElement(); COLOR; COLOR = COLOR->NextSiblingElement()) {
                    std::string ColorName = std::string(COLOR->Name());

                    if (ColorName == "diffuse") {
                        float r = atof(COLOR->Attribute("R")) / 255;
                        float rg = atof(COLOR->Attribute("G")) / 255;
                        float rgb = atof(COLOR->Attribute("B")) / 255;

                        colors.push_back(new Diffuse(r, rg, rgb));
                    } else if (ColorName == "ambient") {
                        float r = atof(COLOR->Attribute("R")) / 255;
                        float rg = atof(COLOR->Attribute("G")) / 255;
                        float rgb = atof(COLOR->Attribute("B")) / 255;

                        colors.push_back(new Ambient(r, rg, rgb));
                    } else if (ColorName == "specular") {
                        float r = atof(COLOR->Attribute("R")) / 255;
                        float rg = atof(COLOR->Attribute("G")) / 255;
                        float rgb = atof(COLOR->Attribute("B")) / 255;

                        colors.push_back(new Specular(r, rg, rgb));
                    } else if (ColorName == "emissive") {
                        float r = atof(COLOR->Attribute("R")) / 255;
                        float rg = atof(COLOR->Attribute("G")) / 255;
                        float rgb = atof(COLOR->Attribute("B")) / 255;

                        colors.push_back(new Emissive(r, rg, rgb));
                    } else if (ColorName == "shininess") {
                        float value = atof(COLOR->Attribute("value"));

                        colors.push_back(new Shininess(value));
                    }
                }

                models.push_back(Model(model, ts, colors));
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

    XMLElement* LIGHTS = doc.FirstChildElement("world")->FirstChildElement("lights");

    int lightIndex = 0;
    if (LIGHTS) {
        for (XMLElement* LIGHT = LIGHTS->FirstChildElement("light"); LIGHT; LIGHT = LIGHTS->NextSiblingElement("light")) {
            std::string lightType = LIGHT->Attribute("type");
            if (lightType == "point") {
                float x = atof(LIGHT->Attribute("posx"));
                float y = atof(LIGHT->Attribute("posy"));
                float z = atof(LIGHT->Attribute("posz"));

                lights.push_back(new LightPoint(x, y, z, lightIndex));
            } else if (lightType == "directional") {
                float dx = atof(LIGHT->Attribute("dirx"));
                float dy = atof(LIGHT->Attribute("diry"));
                float dz = atof(LIGHT->Attribute("dirz"));

                lights.push_back(new LightDirectional(dx, dy, dz, lightIndex));
            } else if (lightType == "spotlight") {
                float x = atof(LIGHT->Attribute("posx"));
                float y = atof(LIGHT->Attribute("posy"));
                float z = atof(LIGHT->Attribute("posz"));
                float dx = atof(LIGHT->Attribute("dirx"));
                float dy = atof(LIGHT->Attribute("diry"));
                float dz = atof(LIGHT->Attribute("dirz"));
                float cutoff = atof(LIGHT->Attribute("cutoff"));

                lights.push_back(new LightSpotlight(x, y, z, dx, dy, dz, cutoff, lightIndex));
            }
            
            lightIndex++;
        }
    }

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

void lightsOn() {
    for (Light* l: lights) {
        l->apply();
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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT, GL_FILL);

    //drawAxis();
    lightsOn();

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
        readXML(path_xml + "test.xml");


    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("Models");


    float dark[4] = {0.3, 0.3, 0.3, 1.0};
    float white[4] = {1.0, 1.0, 1.0, 1.0};
    // float black[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    glEnable(GL_LIGHTING);
	glEnable(GL_RESCALE_NORMAL);

    for (Light* l: lights) {
        glEnable(l->index);
        
        // light colors
        glLightfv(l->index, GL_AMBIENT, dark);
        glLightfv(l->index, GL_DIFFUSE, white);
        glLightfv(l->index, GL_SPECULAR, white);

        // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
    }

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glewInit();

    // inicializar e armazenar nos vbos
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    GLuint buffers[modelPoints.size() + modelNormals.size()];

    glGenBuffers(modelPoints.size() + modelNormals.size(), buffers);

    int i = 0;
    for (std::pair<std::string, std::vector<float>> element : modelPoints) {
        std::string model = element.first;
        std::vector<float> points = element.second;
        std::vector<float> normals = modelNormals[element.first];
        modelBufferPoints[model] = buffers[i];
        modelBufferNormals[model] = buffers[i + modelPoints.size()];
        glBindBuffer(GL_ARRAY_BUFFER, modelBufferPoints[model]);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, modelBufferNormals[model]);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
        i++;
    }


    for(Model & group : models){
        group.vertices = modelBufferPoints[group.model];
        group.normals = modelBufferNormals[group.model];
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