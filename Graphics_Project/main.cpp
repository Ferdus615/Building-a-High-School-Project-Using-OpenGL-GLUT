#include <iostream>
#include<GL/gl.h>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#include<windows.h>
#endif
#include<cstdio>
#include <stdlib.h>
#include <bits/stdc++.h>
#include<GL/gl.h>

#include<math.h>

using namespace std;

const int width = 1500;
const int height = 1000;

GLfloat eyeX = 35;
GLfloat eyeY = 45;
GLfloat eyeZ = 180;

GLfloat lookX = 15;
GLfloat lookY = 10;
GLfloat lookZ = 0;

static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void cube(float r,float g,float b)
{

    glBegin(GL_QUADS);
    glColor3d(r,g,b);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_cube[c_ind[i][j]][0]);
        }
    }
    glEnd();
}

void circle(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis, GLfloat radius, GLfloat rColor, GLfloat gColor, GLfloat bColor)
{
    glPushMatrix(); // Push the current matrix onto the stack
    glTranslatef(xAxis, yAxis, zAxis);

    glColor3f(rColor/255.0, gColor/255.0, bColor/255.0); // Red color used to draw.
    glutSolidSphere(radius, 20, 20);

    glPopMatrix(); // Pop the matrix from the stack to revert to the previous state
}

static void key(unsigned char key, int x, int y)
{
    float switchSpeed = 1.0;
    switch (key)
    {

    case 'd':
        eyeX=eyeX+switchSpeed;
        printf("eye x = %f \n", eyeX);
        break;
    case 'a':
        eyeX=eyeX-switchSpeed;
        printf("eye x = %f \n", eyeX);
    break;
    case 'w':
        eyeY=eyeY+switchSpeed;
        printf("eye y = %f\n", eyeY);
        break;
    case 's':
        eyeY=eyeY-switchSpeed;
        printf("eye y = %f\n", eyeY);
        break;
    case '1':
        eyeZ=eyeZ+switchSpeed;
        printf("eye z = %f\n", eyeZ);
        break;
    case '2':
        eyeZ=eyeZ-switchSpeed;
        printf("eye z = %f\n", eyeZ);
        break;


    case 'l':
        lookX=lookX+switchSpeed;
        printf("L X = %f\n", lookX);
    break;
    case 'j':
        lookX=lookX-switchSpeed;
        printf("L X = %f\n", lookX);
    break;
    case 'o':
        lookY=lookY+switchSpeed;
        printf("L Y = %f\n", lookY);
        break;
    case 'k':
        lookY=lookY-switchSpeed;
        printf("L Y = %f\n", lookY);
        break;
    case 'p':
        lookZ=lookZ+switchSpeed;
        printf("L Z = %f\n", lookZ);
        break;
    case 'i':
        lookZ=lookZ-switchSpeed;
        printf("L Z = %f\n", lookZ);
        break;

    }

    glutPostRedisplay();
}

    float sunXPosition = -183;
    float sunYPosition = 150;
    float sunZPosition = -90;

    float cloud1XPosition = -190;
    float cloud1YPosition = 102;
    float cloud1ZPosition = -57;

    float cloud2XPosition = -253;
    float cloud2YPosition = 45;
    float cloud2ZPosition = -90;

    float cloud3XPosition = -100;
    float cloud4XPosition = 60;


void createBaseField()
{
    // field
    glPushMatrix();
    glTranslated(-232,0-12,-200);
    glScaled(600,1,600);
    cube(0.4,0.8,0.5);
    glPopMatrix();

    //sky
    glPushMatrix();
    glTranslated(-1532,-220,-200);
    glScaled(2700,1000,1);
    cube(100/255.0, 255/255.0,255/255.0);
    glPopMatrix();
}

void createHills()
{
    float xBasePosition = -183;
    float yBasePosition = 0.5-12-14;
    float zBasePosition = -90;

    // hill 1
    glPushMatrix();
    glTranslated(xBasePosition-20,yBasePosition-30,zBasePosition-14);
    glRotated(40, 1, 0, 1);
    glScaled(115,55,1);
    cube(0.75,0.35,0.35);
    glPopMatrix();

    // hill 2
    glPushMatrix();
    glTranslated(xBasePosition+43,yBasePosition-30,zBasePosition-12);
    glRotated(47, 1, 0, 1);
    glScaled(115,55,1);
    cube(0.25,0.45,0.35);
    glPopMatrix();

    float rightShift = 172;
    // hill 3
    glPushMatrix();
    glTranslated(xBasePosition-83+rightShift+2,yBasePosition-38,zBasePosition-3);
    glRotated(46, 1, 0, 1);
    glScaled(105,55,1);
    cube(0.35,0.35,0.35);
    glPopMatrix();

    // hill 4
    glPushMatrix();
    glTranslated(xBasePosition+33+rightShift,yBasePosition-11,zBasePosition-44);
    glRotated(60, 1, 0, 1);
    glScaled(85,85,1);
    cube(0.75,0.35,0.35);
    glPopMatrix();

    // hill 5
    glPushMatrix();
    glTranslated(xBasePosition+88+rightShift,yBasePosition-38,zBasePosition+2);
    glRotated(45, 0, 0, 1);
    glScaled(75,75,1);
    cube(0.25,0.45,0.35);
    glPopMatrix();

    float rightShift2 = 350;
    // hill 6
    glPushMatrix();
    glTranslated(xBasePosition-83+rightShift2+57,yBasePosition-44,zBasePosition-3);
    glRotated(44, 0, 0, 1);
    glScaled(85,85,1);
    cube(0.35,0.35,0.35);
    glPopMatrix();

    // hill 7
    glPushMatrix();
    glTranslated(xBasePosition+33+rightShift2+72,yBasePosition-31,zBasePosition-44);
    glRotated(55, 0, 0, 1);
    glScaled(85,85,1);
    cube(0.75,0.35,0.35);
    glPopMatrix();

    // hill 8
    glPushMatrix();
    glTranslated(xBasePosition+88+rightShift2+20,yBasePosition-44,zBasePosition+2);
    glRotated(50, 0, 0, 1);
    glScaled(75,75,1);
    cube(0.25,0.45,0.35);
    glPopMatrix();
}

void window()
{
    glPushMatrix();
    glScaled(5, 6 , 1);
    cube(0.1,0.9,0.9);
    glPopMatrix();
}

void floor_of_building()
{
    glPushMatrix();
    glTranslated(-9, -11 , 0);
    glScaled(13,14,18);
    for (int i = 0; i < 5; i++)
    {
        glPushMatrix();
        glTranslatef(i, 0, 0); // Translate along X-axis
        cube(0.7, 0, 0);
        glPopMatrix();
    }

    glPopMatrix();

//line
    glPushMatrix();
    glTranslated(-9, 3 , 0);
    glScaled(83,1.5,18);
    cube(0, 0 , 0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-16, -11 , 0);
    glScaled(18,14,13);
    for (int i = 0; i < 3; i++)
    {
        glPushMatrix();
        glTranslatef(4, 0, i); // Translate along X and Z axes (flipped side)
        cube(0.9, 0.8, 0.0);
        glPopMatrix();
    }
    glPopMatrix();
    //line
    glPushMatrix();
    glTranslated(56, 3 , 18.5);
    glScaled(18,1.5,20.5);
    cube(0, 0 , 0);
    glPopMatrix();


    glPushMatrix();
    glTranslated(-3, -7 ,19);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(7,-7,19);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(17,-7,19);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(27,-7,19);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(57,-7,38.5);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(67,-7,38.5);
    window();
    glPopMatrix();
}

void Mainbuilding()
{
    //1st floor
    glPushMatrix();
    floor_of_building();

    //door
    glTranslated(37,-9,19);
    glScaled(15,10,0.5);
    cube(0.7 ,0.8, 0.7);
    glPopMatrix();

    //2st floor
    glPushMatrix();
    glTranslated(0, 15.5 ,0);
    floor_of_building();

    glPushMatrix();
    glTranslated(37,-7,20);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(46,-7,20);
    window();
    glPopMatrix();

    glPopMatrix();

    //3rd floor

    glPushMatrix();
    glTranslated(0, 31 ,0);
    floor_of_building();

    glPushMatrix();
    glTranslated(37,-7,20);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(46,-7,20);
    window();
    glPopMatrix();

    glPopMatrix();
}

void left_floor_of_building()
{
    glPushMatrix();
    glTranslated(3, 0, 0);


    glPushMatrix();
    glTranslated(-9, -11 , 0);
    glScaled(13,14,18);
    for (int i = 0; i < 5; i++)
    {
        glPushMatrix();
        glTranslatef(i, 0, 0); // Translate along X-axis
        cube(0.7, 0, 0);
        glPopMatrix();
    }

    glPopMatrix();

//line
    glPushMatrix();
    glTranslated(-9, 3 , 0);
    glScaled(65,1.5,18);
    cube(0, 0 , 0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3, -7 ,19);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(7,-7,19);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(17,-7,19);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(27,-7,19);
    window();
    glPopMatrix();

    glPopMatrix();


    glPushMatrix();
    glTranslated(-80, 0 , 0);

    glPushMatrix();
    glTranslated(-16, -11 , 0);
    glScaled(18,14,13);
    for (int i = 0; i < 3; i++)
    {
        glPushMatrix();
        glTranslatef(4, 0, i); // Translate along X and Z axes (flipped side)
        cube(0.9, 0.8, 0.0);
        glPopMatrix();
    }
    glPopMatrix();
    //line
    glPushMatrix();
    glTranslated(56, 3 , 18.5);
    glScaled(18,1.5,20.5);
    cube(0, 0 , 0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(57,-7,38.5);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(67,-7,38.5);
    window();
    glPopMatrix();

    glPopMatrix();
}

void Left_Mainbuilding()
{
    //1st floor
    glPushMatrix();
    left_floor_of_building();

    //door
    glTranslated(37,-9,19);
    glScaled(15,10,0.5);
    cube(0.7, 0.8, 0.7);
    glPopMatrix();

    //2st floor
    glPushMatrix();
    glTranslated(0, 15.5 ,0);
    left_floor_of_building();

    glPushMatrix();
    glTranslated(37,-7,20);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(46,-7,20);
    window();
    glPopMatrix();

    glPopMatrix();

    //3rd floor

    glPushMatrix();
    glTranslated(0, 31 ,0);
    left_floor_of_building();

    glPushMatrix();
    glTranslated(37,-7,20);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslated(46,-7,20);
    window();
    glPopMatrix();

    glPopMatrix();
}

void schoolfild()
{
    glPushMatrix();
    glTranslated(-100,-11,-30);
    glScaled(250,1,150);
    cube(0.0,0.4,0.0);
    glPopMatrix();
}

void Boundary()
{
    //Length Wall
    glPushMatrix();
    glTranslated(-100,-11,-30);

    //Back Wall
    glPushMatrix();
    glScaled(250,12,1);
    cube(1.0,1.0,0.8);
    glPopMatrix();

    //Gate Wall
    glPushMatrix();
    glScaled(115,12,1);
    glTranslated(0,0,149);
    cube(1.0,1.0,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslated(135,0,149);

    glPushMatrix();
    glScaled(115,12,1);
    cube(1.0,1.0,0.8);
    glPopMatrix();

    glPopMatrix();

    //Gate
    glPushMatrix();
    glTranslated(115,0,149);

    glPushMatrix();
    glScaled(2,22,1);
    cube(0.0,0.0,0.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(133,0,149);

    glPushMatrix();
    glScaled(2,22,1);
    cube(0.0,0.0,0.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(115,22,149);

    glPushMatrix();
    glScaled(20,3,1);
    cube(0.0,0.0,0.0);
    glPopMatrix();

    glPopMatrix();

    //Side Wall
    glPushMatrix();
    glScaled(1,12,150);
    cube(1.0,1.0,0.8);
    glPopMatrix();

    //Side Wall
    glPushMatrix();
    glScaled(1,12,150);
    glTranslated(249,0,0);
    cube(1.0,1.0,0.8);
    glPopMatrix();

    glPopMatrix();
}

void SEU()
{
    //S code
    glPushMatrix();
    glTranslated(10,41,120);

    glPushMatrix();
    glScaled(10,2,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(10,31,120);

    glPushMatrix();
    glScaled(10,2,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(10,21,120);

    glPushMatrix();
    glScaled(10,2,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(10,31,120);

    glPushMatrix();
    glScaled(2,10,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(18,21,120);

    glPushMatrix();
    glScaled(2,10,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    //E code
    glPushMatrix();
    glTranslated(25,41,120);

    glPushMatrix();
    glScaled(10,2,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(25,31,120);

    glPushMatrix();
    glScaled(10,2,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(25,21,120);

    glPushMatrix();
    glScaled(10,2,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(25,31,120);

    glPushMatrix();
    glScaled(2,10,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(25,21,120);

    glPushMatrix();
    glScaled(2,10,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    //U code
    glPushMatrix();
    glTranslated(40,21,120);

    glPushMatrix();
    glScaled(11,2,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(40,21,120);

    glPushMatrix();
    glScaled(2,22,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslated(50,21,120);

    glPushMatrix();
    glScaled(2,22,2);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    //Base Cube
    glPushMatrix();
    glTranslated(6,18,110);

    glPushMatrix();
    glScaled(50,2,20);
    cube(0.7,0.0,0.0);
    glPopMatrix();

    glPopMatrix();
}

void Road()
{
    glPushMatrix();
    glTranslated(-250,-11,120);

    glPushMatrix();
    glScaled(700,1.5,10);
    cube(0.7,0.7,0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,0,25);

    glPushMatrix();
    glScaled(700,1,1);
    cube(1.0,1.0,1.0);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glScaled(700,1,40);
    cube(0.0,0.0,0.0);
    glPopMatrix();

    glPopMatrix();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glFrustum(-3.5, 3, -3, 3, 2.0, 800.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);
    glViewport(0, 0, width, height);

    glPushMatrix();
    glScaled(0.7,0.7,0.7);
    glTranslated(110,-33,0);
    SEU();
    glPopMatrix();

    createBaseField();
    createHills();
    schoolfild();
    Boundary();
    Road();

    glPushMatrix();
    glTranslated(43,5,0);
    Mainbuilding();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-43,5,0);
    Left_Mainbuilding();
    glPopMatrix();

    glutSwapBuffers();
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(1500,1000);
    glutCreateWindow("High School");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}
