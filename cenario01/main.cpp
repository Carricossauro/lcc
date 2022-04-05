#include<stdio.h>
#include<stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;

int tree_number = 300;
float desvios[300];
float desvio_angulos[300];
float color[300];
float height[300];
int time_diff = -1;
float time_angle_diff = (2 * M_PI) / 175;
float time_angle_diff_2 = 360.0f / 175.0f;

float timebase, time_passed;
float frames = 0, fps;

unsigned int t, tw, th;
unsigned char *imageData;

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

float h(int i, int j) {
	// std::cout << "x= " << (int) i << ", z= " << (int) j << ", pos=" << i * tw + j << std::endl;
	return (imageData[i * tw + j]*30)/255;
}

void arvore(float x, float z, float colorLeaves, float y) {
	glPushMatrix();
	glColor3f(0.64f, 0.45f, 0.28f);

	glTranslatef(x, y, z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);

	glutSolidCone(1, 8, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0f, colorLeaves, 0.0f);

	glTranslatef(x, y + 2.5, z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);

	glutSolidCone(3, 10, 20, 20);

	glPopMatrix();
}

void drawTerrain() {
    // colocar aqui o código de desenho do terreno usando VBOs com TRIANGLE_STRIPS
	glColor3f(0.2f, 0.8f, 0.2f);

	float offsetX = tw/2;
	float offsetZ = th/2;

	glPolygonMode(GL_FRONT, GL_FILL);
	for (float z = 0; z < th - 1; z++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (float x = 0; x < tw; x++) {
			glVertex3f(-offsetX + x, h(z, x), -offsetZ + z);
			glVertex3f(-offsetX + x, h(z+1, x), -offsetZ + z + 1);
		}
		glEnd();
	}
}

void drawAula5() {
	time_diff += 1;
	glColor3f(1.0f, 0, 0);
	
	glPushMatrix();
	glTranslatef(0, h(0, 0), 0);
	glutSolidTorus(1, 3, 20, 20);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(0, h(0, 0), 0);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(1, 3, 20, 20);

	glPopMatrix();

	float alpha_arch = (M_PI * 2) / 8;
	float rotation_angle = 360 / 8;
	float rc = 15;

	glColor3f(0, 0, 1.0f);
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		float alpha = alpha_arch * i - time_angle_diff * time_diff;

		float x = rc * cos(alpha);
		float z = rc * sin(alpha);

		glTranslatef(x, 1.5f, z);
		glRotatef(-rotation_angle * i, 0, 1.0f, 0);
		glRotatef(time_angle_diff_2 * time_diff, 0, 1.0f, 0);
		glutSolidTeapot(2);

		glPopMatrix();
	}

	glColor3f(1.0f, 0, 0);

	alpha_arch = (2 * M_PI) / 16;
	rotation_angle = 360 / 16;
	float ri = 35;
	for (int i = 0; i < 16; i++) {
		glPushMatrix();
		float alpha = alpha_arch * i + time_angle_diff * time_diff;

		float x = ri * cos(alpha);
		float z = ri * sin(alpha);

		glTranslatef(x, 1.5f, z);
		glRotatef(180-rotation_angle * i, 0, 1.0f, 0);
		glRotatef(360-time_angle_diff_2 * time_diff, 0, 1.0f, 0);
		glutSolidTeapot(2);

		glPopMatrix();
	}

	float r = 50;
	alpha_arch = (2 * M_PI) / tree_number;

	for (int i = 0; i < tree_number; i++) {
		float radius = r + desvios[i];
		float x = radius * cos(alpha_arch * (i + desvio_angulos[i]));
		float y = height[i];
		// float y = 0;
		float z = radius * sin(alpha_arch * (i + desvio_angulos[i]));

		arvore(x, z, color[i], y);
	}

	// FPS Counter
	frames++;
	time_passed = glutGet(GLUT_ELAPSED_TIME);
	if (time_passed - timebase > 1000) {
		fps = frames*1000.0/(time_passed - timebase);
		timebase = time_passed;
		frames = 0;
	}

	char fps_buffer[50];

	sprintf(fps_buffer, "%d", (int) fps);

	glutSetWindowTitle(fps_buffer);
}

void renderScene(void) {
	float pos[4] = {-1.0, 1.0, 1.0, 0.0};

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	glPolygonMode(GL_FRONT, GL_LINE);

	drawTerrain();
	drawAula5();

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) {
	// put code to process regular keys in here
}

void processMouseButtons(int button, int state, int xx, int yy) {
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}

void processMouseMotion(int xx, int yy) {
	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}


void init() {
	// 	Load the height map "terreno.jpg"
	ilGenImages(1,&t);
	ilBindImage(t);
	// terreno.jpg is the image containing our height map
	ilLoadImage((ILstring)"terreno.jpg");
	// convert the image to single channel per pixel
	// with values ranging between 0 and 255
	ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
	// important: check tw and th values
	// both should be equal to 256
	// if not there was an error loading the image
	// most likely the image could not be found
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	// imageData is a LINEAR array with the pixel values
	imageData = ilGetData();
	
	float r = 50;
	float alpha_arch = (2 * M_PI) / tree_number;
	for (int i = 0; i < tree_number; i++) {
		float radius = r + desvios[i];
		float x = radius * cos(alpha_arch * (i + desvio_angulos[i]));
		float y = height[i];
		float z = radius * sin(alpha_arch * (i + desvio_angulos[i]));

		float h1, h2, h3, h4;
		h1 = h((int) ceil(tw/2.0f + z), (int) ceil(th/2.0f + x));
		h2 = h((int) ceil(tw/2.0f + z), (int) floor(th/2.0f + x));
		h3 = h((int) floor(tw/2.0f + z), (int) ceil(th/2.0f + x));
		h4 = h((int) floor(tw/2.0f + z), (int) floor(th/2.0f + x));

		h1 = std::min(h1, h2);
		h4 = std::min(h3, h4);

		height[i] = std::min(h1, h4);
	}

// 	Build the vertex arrays

// 	OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
}


int main(int argc, char **argv) {
	for(int i = 0; i < tree_number; i++) {
		desvios[i] = rand() % 50;
		desvio_angulos[i] = rand() % tree_number;
		color[i] = (rand() % 3);
		color[i] /= 10;
		color[i] += 0.4f;
	}

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("CG@DI-UM");
		

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

	ilInit();

	init();	

	// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}

