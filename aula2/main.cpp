#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

int degree = 0;
int offsetX = 0;
int offsetZ = 0;
int mode = 0;

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


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
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

    glEnd();

	// put the geometric transformations here
	glRotatef(degree, 0, 1, 0);
	glTranslatef(offsetX, 0, offsetZ);
	if (mode == 0) {
		glPolygonMode(GL_FRONT, GL_FILL);
	} else if (mode == 1) {
		glPolygonMode(GL_FRONT, GL_LINE);
	}

	// put drawing instructions here

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);

	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);	

	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);

	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);

	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);

	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);

	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);

	glEnd();


	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events

void onKeyboard(unsigned char key_code, int x, int y) {
	if (key_code == 'e') {
		degree += 15;
		glutPostRedisplay();
	} else if (key_code == 'q') {
		degree -= 15;
		glutPostRedisplay();
	} else if (key_code == 'w' || key_code == 'W') {
		offsetX -= 1;
		glutPostRedisplay();
	} else if (key_code == 's' || key_code == 'S') {
		offsetX += 1;
		glutPostRedisplay();
	} else if (key_code == 'a') {
		offsetZ += 1;
		glutPostRedisplay();
	} else if (key_code == 'd') {
		offsetZ -= 1;
		glutPostRedisplay();
	} else if (key_code == ' ') {
		mode = (mode + 1) % 2;
		glutPostRedisplay();
	}
}

int main(int argc, char **argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@A2");
		
	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
	// put here the registration of the keyboard callbacks
	glutKeyboardFunc(onKeyboard);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
