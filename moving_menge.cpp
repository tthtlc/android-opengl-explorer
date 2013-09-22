
#include "menge.h"

Cube* MengerCube;

int maxcounter=0;

int xdir=1;
int ydir=1;
int zdir=1;
GLfloat xf=0.0;
GLfloat yf=0.0;
GLfloat zf=0.0;
GLfloat ORTHMIN =-80.0;
GLfloat ORTHMAX =80.0;
GLfloat XMIN =ORTHMIN;
GLfloat YMIN =ORTHMIN;
GLfloat ZMIN =ORTHMIN;
GLfloat XMAX =ORTHMAX;
GLfloat YMAX =ORTHMAX;
GLfloat ZMAX =ORTHMAX;

int MAXCOUNT = 20;
int MAXDEPTH = 8;

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
	glTranslatef(xf, yf, zf);
	xf+=10.0*xdir;
	yf+=20.0*ydir;
	zf+=30.0*zdir;
	if ((xf < XMIN) || (xf > XMAX)) xdir=-1*xdir;
	if ((yf < YMIN) || (yf > YMAX)) ydir=-1*ydir;
	if ((zf < ZMIN) || (zf > ZMAX)) zdir=-1*zdir;

	maxcounter++;
        GLfloat matrix[16];

	if (maxcounter>MAXCOUNT) {

		depth++;
		if (depth> MAXDEPTH) depth = 2;
		maxcounter=0;
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		MengerCube = new Cube(&origin, 40.0, depth);

	}

	MengerCube->visualize();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(ORTHMIN, ORTHMAX, ORTHMIN, ORTHMAX, ORTHMIN, ORTHMAX);
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

	MengerCube = new Cube(&origin, 40.0, depth);

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


