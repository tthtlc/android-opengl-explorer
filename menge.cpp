
#include "menge.h"

Cube* MengerCube;

void idle()
{
	glutPostRedisplay();
}

void display()
{
	static GLfloat rtri = 0.0;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0,1.0,1.0, 0.0,0.0,0.0,0.0,1.0,0.0);
	glRotatef((rtri+=0.932), 1.0, 0.5, -1.0);

	MengerCube->visualize();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0,-8.0, 8.0,-8.0, 8.0);
}

void init()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glColor3f(1.0, 1.0, 1.0);
}

GLfloat getDepth(char* depth)
{
	int k = atoi(depth);
	if(k <= 1) return 1.0;
	else if (k>= 5) return 5.0;
	else return (GLfloat) k;
}

int main(int argc, char* argv[])
{
	GLfloat depth;
	bool viewAsPointCloud = false;
	point origin(0.0, 0.0, 0.0);

	printf("%d\n",argc);

	switch(argc)
	{
	case 2:
		depth = getDepth(argv[1]);
		break;
	default:
		depth = 2.0;
		break;
	}

	MengerCube = new Cube(&origin, 8.0, depth);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow(*argv);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	init();
	glutMainLoop();

	delete MengerCube;
}


