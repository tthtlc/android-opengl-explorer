

#include <GL/glut.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//=================================================================================
//=================================================================================
class point
{
public:
	point(GLfloat x, GLfloat y, GLfloat z, point* ref = NULL);
	void visualize();

	GLfloat x,y,z;
};

point::point(GLfloat x, GLfloat y, GLfloat z, point* ref)
{
	this->x = x;
	this->y = y;
	this->z = z;

	if(ref != NULL)
	{
		this->x += ref->x;
		this->y += ref->y;
		this->z += ref->z;
	}
}

//=================================================================================
//=================================================================================

class Cube
{
public:
	Cube(point* origin, GLfloat edgelength, GLfloat depth);
	~Cube();

	void visualize();

private:
	void MakeFace(int i, int j, int k, int l);
	void ActAsContainer(point* o, GLfloat e, GLfloat d);
	void ActAsCube(point* o, GLfloat e);

	point** PointCloud;
	Cube** SubCubes;
};

Cube::Cube(point* origin, GLfloat edgelength, GLfloat depth)
{
	if(depth <= 1.0)
	{
		ActAsCube(origin, edgelength);
	} else {
		ActAsContainer(origin, edgelength, depth);
	}
}

Cube::~Cube()
{
	int i;

	if(PointCloud != NULL)
	{
		for(i = 0; i < 8; i++)
			delete PointCloud[i];
		delete[] PointCloud;
	}

	if(SubCubes != NULL)
	{
		for(i = 0; i < 20; i++)
			delete SubCubes[i];
		delete[] SubCubes;
	}
}

void Cube::ActAsCube(point* o, GLfloat e)
{
	GLfloat ne = e / 2.0;

	PointCloud = new point*[8];		// This is the actual physical cube coordinates;
	SubCubes = NULL;

	PointCloud[0] = new point( ne,  ne,  ne, o);	// net
	PointCloud[1] = new point( ne, -ne,  ne, o);	// set
	PointCloud[2] = new point(-ne,  ne,  ne, o);	// nwt
	PointCloud[3] = new point(-ne, -ne,  ne, o);	// swt
	PointCloud[4] = new point( ne,  ne, -ne, o);	// neb
	PointCloud[5] = new point( ne, -ne, -ne, o);	// seb
	PointCloud[6] = new point(-ne,  ne, -ne, o);	// nwb
	PointCloud[7] = new point(-ne, -ne, -ne, o);	// swb
}

void Cube::ActAsContainer(point* o, GLfloat e, GLfloat d)
{
	GLfloat ne = e / 3.0;

	SubCubes = new Cube*[20];	// These are the centers of each sub cube structure
	PointCloud = NULL;

	SubCubes[0] = new Cube(new point(-ne,  ne,  ne, o), ne, d-1.0);
	SubCubes[1] = new Cube(new point(0.0,  ne,  ne, o), ne, d-1.0);
	SubCubes[2] = new Cube(new point( ne,  ne,  ne, o), ne, d-1.0);
	SubCubes[3] = new Cube(new point( ne, 0.0,  ne, o), ne, d-1.0);
	SubCubes[4] = new Cube(new point( ne, -ne,  ne, o), ne, d-1.0);
	SubCubes[5] = new Cube(new point(0.0, -ne,  ne, o), ne, d-1.0);
	SubCubes[6] = new Cube(new point(-ne, -ne,  ne, o), ne, d-1.0);
	SubCubes[7] = new Cube(new point(-ne, 0.0,  ne, o), ne, d-1.0);
	
	SubCubes[8] = new Cube(new point( ne,  ne,  0.0, o), ne, d-1.0);
	SubCubes[9] = new Cube(new point( ne, -ne,  0.0, o), ne, d-1.0);
	SubCubes[10] = new Cube(new point(-ne, ne,  0.0, o), ne, d-1.0);
	SubCubes[11] = new Cube(new point(-ne, -ne,  0.0, o), ne, d-1.0);
	
	SubCubes[12] = new Cube(new point(-ne,  ne, -ne, o), ne, d-1.0);
	SubCubes[13] = new Cube(new point(0.0,  ne, -ne, o), ne, d-1.0);
	SubCubes[14] = new Cube(new point( ne,  ne, -ne, o), ne, d-1.0);
	SubCubes[15] = new Cube(new point( ne, 0.0, -ne, o), ne, d-1.0);
	SubCubes[16] = new Cube(new point( ne, -ne, -ne, o), ne, d-1.0);
	SubCubes[17] = new Cube(new point(0.0, -ne, -ne, o), ne, d-1.0);
	SubCubes[18] = new Cube(new point(-ne, -ne, -ne, o), ne, d-1.0);
	SubCubes[19] = new Cube(new point(-ne, 0.0, -ne, o), ne, d-1.0);
}

void Cube::MakeFace(int i, int j, int k, int l)
{
		glVertex3f(PointCloud[i]->x, PointCloud[i]->y, PointCloud[i]->z);
		glVertex3f(PointCloud[j]->x, PointCloud[j]->y, PointCloud[j]->z);
		glVertex3f(PointCloud[k]->x, PointCloud[k]->y, PointCloud[k]->z);
		glVertex3f(PointCloud[l]->x, PointCloud[l]->y, PointCloud[l]->z);

}

void Cube::visualize()
{
	int i;

	if(PointCloud != NULL)
	{
		glBegin(GL_QUADS);
			glColor3f(1.0,0.0,0.0);// top
			MakeFace(0,2,3,1);
			glColor3f(0.0,1.0,1.0);//bottom
			MakeFace(4,6,7,5);
			
			glColor3f(0.0,1.0,0.0);// north
			MakeFace(0,2,6,4);
			glColor3f(1.0,0.0,1.0);// south
			MakeFace(1,3,7,5);
			
			glColor3f(0.0,0.0,1.0);//east
			MakeFace(0,4,5,1);
			glColor3f(1.0,1.0,0.0);// west
			MakeFace(2,6,7,3);
		glEnd();
	}

	if(SubCubes != NULL)
	{
		for(i = 0; i < 20; i++)
		{
			SubCubes[i]->visualize();
		}
	}
}



