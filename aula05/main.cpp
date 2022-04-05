#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

float alfa = 0.0f, beta = 0.5f, radius = 200.0f;
float camX, camY, camZ;
int tree_number = 300;
float desvios[300];
float desvio_angulos[300];
float color[300];
int time_diff = -1;
float time_angle_diff = (2 * M_PI) / 175;
float time_angle_diff_2 = 360.0f / 175.0f;

float timebase, time_passed;
float frames = 0, fps;


void spherical2Cartesian() {
	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
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

void arvore(float x, float z, float color) {
	glPushMatrix();
	glColor3f(0.64f, 0.45f, 0.28f);

	glTranslatef(x, 0, z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);

	glutSolidCone(1, 8, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0f, color, 0.0f);

	glTranslatef(x, 2.5, z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);

	glutSolidCone(3, 10, 20, 20);

	glPopMatrix();
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();

	// End of frame

	time_diff += 1;

	glColor3f(1.0f, 0, 0);
	glutSolidTorus(1, 3, 20, 20);
	glPushMatrix();

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
		float z = radius * sin(alpha_arch * (i + desvio_angulos[i]));

		arvore(x, z, color[i]);
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
	
	glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_RIGHT:
			alfa -= 0.1; break;

		case GLUT_KEY_LEFT:
			alfa += 0.1; break;

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

		case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
			if (radius < 1.0f)
				radius = 1.0f;
			break;

		case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();
}

void printInfo() {
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin\n");
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
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	timebase = glutGet(GLUT_ELAPSED_TIME);
	
	// Callback registration for keyboard processing
	glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

	// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}