#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alpha_cam = 0, beta_cam = 0, radius_cam = 20;
float px, py, pz;

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

void drawTorus(float R, float r, int slices, int stacks) {
	float arch_alpha = (2 * M_PI) / slices, arch_beta = (2 * M_PI) / stacks;
	float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;

	float rr = (R + r) / 2;
	float dist = rr - r;

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < stacks; j++) {
			x1 = (R + r * cos(arch_alpha * i)) * cos(arch_beta * j);
			x2 = (R + r * cos(arch_alpha * (i+1))) * cos(arch_beta * j);
			x3 = (R + r * cos(arch_alpha * (i+1))) * cos(arch_beta * (j+1));
			x4 = (R + r * cos(arch_alpha * i)) * cos(arch_beta * (j+1));

			y1 = r * sin(arch_alpha * i);
			y2 = r * sin(arch_alpha * (i+1));
			y3 = r * sin(arch_alpha * (i+1));
			y4 = r * sin(arch_alpha * i);

			z1 = (R + r * cos(arch_alpha * i)) * sin(arch_beta * j);
			z2 = (R + r * cos(arch_alpha * (i+1))) * sin(arch_beta * j);
			z3 = (R + r * cos(arch_alpha * (i+1))) * sin(arch_beta * (j+1));
			z4 = (R + r * cos(arch_alpha * i)) * sin(arch_beta * (j+1));

			glVertex3f(x1, y1, z1);
			glVertex3f(x2, y2, z2);
			glVertex3f(x4, y4, z4);

			glVertex3f(x2, y2, z2);
			glVertex3f(x3, y3, z3);
			glVertex3f(x4, y4, z4);
			
		}
	}
	glEnd();
}

void camera_coordinates() {
	px = radius_cam * cos(beta_cam) * sin(alpha_cam);
	py = radius_cam * sin(beta_cam);
	pz = radius_cam * cos(alpha_cam) * cos(beta_cam);
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera_coordinates();

	// set the camera
	glLoadIdentity();
	gluLookAt(px, py, pz,
			  0, 0, 0,
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

	// drawCylinder(1,2,20);
	drawTorus(2.5, 1.5, 50, 50);

	// End of frame
	glutSwapBuffers();
}

void processSpecialKey(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_DOWN:
			beta_cam -= 0.1;
			if (beta_cam < -1.5f) {
				beta_cam = -1.5f;
			}
			break;
		case GLUT_KEY_UP:
			beta_cam += 0.1;
			if (beta_cam > 1.5f) {
				beta_cam = 1.5f;
			}
			break;
		case GLUT_KEY_LEFT:
			alpha_cam -= 0.1;
			break;
		case GLUT_KEY_RIGHT:
			alpha_cam += 0.1;
			break;
		case GLUT_KEY_PAGE_DOWN:
			radius_cam -= 0.1;
			break;
		case GLUT_KEY_PAGE_UP:
			radius_cam += 0.1;
			break;
		default:
			break;
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
	glutSpecialFunc(processSpecialKey);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
