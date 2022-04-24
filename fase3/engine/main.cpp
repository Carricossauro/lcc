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
#include "structs.cpp"

struct Point{
    float x,y,z;
    Point(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

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

float length(float *v) {
	float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return res;

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
	float pos[3], deriv[3];
	float LINE_SEGMENTS = 100;
	
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < LINE_SEGMENTS; i++) {
		getGlobalCatmullRomPoint(1/LINE_SEGMENTS * i, pos, deriv, control_points);
		glVertex3f(pos[0], pos[1], pos[2]);
	}
	glEnd();
}

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

class RotateAngle : public Transformation{
    float x, y, z, angle;
public:
    RotateAngle(float angle, float x, float y, float z) {
        this->angle = angle;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void apply() {
        glRotatef(angle, x, y, z);
    }
};

class RotateTime : public Transformation{
    float x, y, z, time;
public:
    RotateTime(float time, float x, float y, float z) {
        this->time = time * 1000;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void apply() {
        float angle = glutGet(GLUT_ELAPSED_TIME)*360/time;
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
    float t, time, current_time;
    std::vector<Point> control_points;
    bool align;
    float prev_y[3];
public:
    Curve(std::vector<Point> points, bool align, float time) {
        this->t = 0;
        this->control_points = points;
        this->time = time*1000;
        this->current_time = 0;
        this->align = align;
        this->prev_y[0] = 0;
        this->prev_y[1] = 1;
        this->prev_y[2] = 0;
    }

    void apply() {
        float pos[3], deriv[3];
        renderCatmullRomCurve(control_points);

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
// vetor de Model onde sao armazenados os vetores com os pontos e as transformações
// std::vector<std::vector<Point>> models;
std::vector<Model> models;

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

// le pontos armazenados em source (ficheiro .3d) e retorna um vetor de vetores de Point
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
// funçao auxiliar do readXML que le um grupo
void readGroup(tinyxml2::XMLElement *group, std::vector<Transformation*> ts) {
    using namespace tinyxml2;
    std::vector<Transformation*> backup = ts;

    while (group) {
        ts = backup;
        XMLElement *transformation = group->FirstChildElement("transform");

        if (transformation) {
            for (XMLElement *t = transformation->FirstChildElement(); t; t = t->NextSiblingElement()) {
                std::string name = std::string(t->Name());
                std::cout << name << std::endl;

                if (name == "translate") {
                    std::cout << "p1" << std::endl;
                    if (t->Attribute("time") == nullptr) {
                        float x, y, z;
                        x = atof(t->Attribute("x"));
                        y = atof(t->Attribute("y"));
                        z = atof(t->Attribute("z"));

                        ts.push_back(new Translate(x, y, z));
                    } else {
                        std::cout << "p2" << std::endl;
                        float time;
                        std::string align;
                        std::vector<Point> curve;
                        time = atof(t->Attribute("time"));
                        align = t->Attribute("align");
                        std::cout << "p3" << std::endl;

                        for (XMLElement *p = t->FirstChildElement("point"); p; p = p->NextSiblingElement("point")) {
                            float x, y, z;
                            x = atof(p->Attribute("x"));
                            y = atof(p->Attribute("y"));
                            z = atof(p->Attribute("z"));

                            curve.push_back(Point(x, y, z));
                        }
                        std::cout << "p4" << std::endl;

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


// desenha as figuras com os pontos e transformações armazenados no vetor models
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

    glPolygonMode(GL_FRONT,GL_LINE);

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
    // caminho para os ficheiros 3d e xml
    path_3d = "../../3d/";
    path_xml = "../../xml/";


    spherical2Cartesian();

    if(argc == 2)
        readXML(path_xml + argv[1]);
    else
        readXML(path_xml + "test_3_1.xml");


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

    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    printInfo();
    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}