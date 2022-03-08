#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alpha_cam = M_PI, beta_cam = 0, radius_cam = 10;
float px = 0, py = 0, pz = 5.0f, dx = 0, dy = 0, dz = 0;

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

void drawCylinder(float radius, float height, int slices) {
	float alpha = (2 * M_PI) / slices;
	float x1, z1;
	float x2, z2;
	float x3, z3;
	float y1, y2;

	// Cylinder base
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < slices; i++) {
		x1 = 0;
		z1 = 0;
		x2 = radius * sin(alpha * i);
		z2 = radius * cos(alpha * i);
		x3 = radius * sin(alpha * (i+1));
		z3 = radius * cos(alpha * (i+1));
		y1 = 0;
		y2 = height;
		
		if (i % 2 == 0) glColor3f(0.25, 0.25, 0.25);
		else glColor3f(0.75, 0.75, 0.75);

		glVertex3f(x1, y1, z1);
		glVertex3f(x3, y1, z3);
		glVertex3f(x2, y1, z2);

		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x3, y1, z3);

		glVertex3f(x2, y2, z2);
		glVertex3f(x3, y1, z3);
		glVertex3f(x3, y2, z3);

		glVertex3f(x1, y2, z1);
		glVertex3f(x2, y2, z2);
		glVertex3f(x3, y2, z3);
	}
	glEnd();
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	dx = sin(alpha_cam) * cos(beta_cam);
	dy = sin(beta_cam);
	dz = cos(alpha_cam) * cos(beta_cam);
	gluLookAt(px, py, pz,
			  px+dx, py+dy, pz+dz,
			  0.0f,1.0f,0.0f);
	
	glBegin(GL_LINES);

    glColor3f (1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(5.0, 0.0, 0.0);

    glColor3f (0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 5.0, 0.0);

    glColor3f (0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 5.0);

	glColor3f(1.0, 1.0, 1.0);

    glEnd();

	drawCylinder(1,2,20);

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
	// dx = sin(alpha_cam) * cos(beta_cam);
	// dy = sin(beta_cam);
	// dz = cos(alpha_cam) * cos(beta_cam);
	float alpha_mov, beta_mov;
	if (c == 'w') {
		alpha_mov = alpha_cam;
		beta_mov = beta_cam;
	} else if (c == 's') {
		alpha_mov = alpha_cam + M_PI;
		beta_mov = beta_cam;
	} else if (c == 'a') {
		alpha_mov = alpha_cam + M_PI_2;
		beta_mov = beta_cam;
	} else if (c == 'd') {
		alpha_mov = alpha_cam - M_PI_2;
		beta_mov = beta_cam;
	}
	float dx_mov = sin(alpha_mov) * cos(beta_mov);
	float dy_mov = sin(beta_mov);
	float dz_mov = cos(alpha_mov) * cos(beta_mov);
	px += dx_mov * 0.05;
	py += dy_mov * 0.05;
	pz += dz_mov * 0.05;
	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
	if (key == GLUT_KEY_RIGHT) {
		alpha_cam -= 0.1;
	} else if (key == GLUT_KEY_LEFT) {
		alpha_cam += 0.1;
	} else if (key == GLUT_KEY_UP) {
		beta_cam += 0.1;
	} else if (key == GLUT_KEY_DOWN) {
		beta_cam -= 0.1;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {
// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}