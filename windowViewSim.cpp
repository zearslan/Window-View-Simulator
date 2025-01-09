/**********************************
 CTIS164 - Homework 1
-----------------------------------
NAME SURNAME : Zeynep Arslan
STUDENT ID : 22303672
SECTION : 004

 Additional Functions:

	1-Esc to exit
	2-Left click to make it night time
		>> Sun becomes moon, everything turns darker(grass, tree, mountains)
	3-Right click to make it day time
		>> Moon becomes sun, everything turns lighter(grass, tree, mountains)
	4-Right arrow to speed up the car
	5-Left arrow to slow down the car

The program runs smoothly without encountering any problems
-----------------------------------
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  650
#define WINDOW_HEIGHT 650
#define TIMER_PERIOD  100 // Period for the timer.
#define TIMER_ON         1 // 0:Disable timer, 1:Enable timer
#define PI 3.141592654

int clX = 175, clY = 68; //initial coordinates of the cloud
int carX = -100, carY = -90; //initial coordinates of the car
int carSp = 4; //initial speed of the car

int r = 255, g = 255, b = 100; //initial color of the sun/moon
int skyR = 100, skyG = 150, skyB = 250; //initial color of the sky
int cl = 250; //initial color of the cloud
int grR = 10, grG = 150, grB = 30; //initial color of the grass
int mR = 35, mG = 20, mB = 15; //initial color of the mountains

bool activeTimer = true;
int  winWidth, winHeight; // Window width and height

// Display text with variables
void vprint(int x, int y, void* font, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, str[i]);
}

void circle(int x, int y, int r) {
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

// Functions to display objects
void drawCar() {

	// Bottom Part of the Car
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(carX - 110, carY - 5);
	glVertex2f(carX + 10, carY - 5);
	glVertex2f(carX, carY + 20);
	glVertex2f(carX - 100, carY + 20);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(150, 10, 20);
	glVertex2f(carX - 110, carY - 5);
	glVertex2f(carX + 10, carY - 5);
	glVertex2f(carX, carY + 20);
	glVertex2f(carX - 100, carY + 20);
	glEnd();

	// Shadow of the Bottom Part of the Car
	glBegin(GL_POLYGON);
	glColor3ub(100, 5, 10);
	glVertex2f(carX - 112, carY - 5);
	glVertex2f(carX + 12, carY - 5);
	glVertex2f(carX + 5, carY);
	glVertex2f(carX - 105, carY);
	glEnd();

	// Top Part of the Car
	glColor3ub(150, 10, 20);
	glRectf(carX - 90, carY + 40, carX - 10, carY + 10);

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(carX - 90, carY + 40);
	glVertex2f(carX - 10, carY + 40);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(carX - 90, carY + 20);
	glVertex2f(carX - 90, carY + 40);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(carX - 10, carY + 20);
	glVertex2f(carX - 10, carY + 40);
	glEnd();

	// Car Window
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(carX - 85, carY + 35);
	glVertex2f(carX - 15, carY + 35);
	glVertex2f(carX - 15, carY + 18);
	glVertex2f(carX - 85, carY + 18);
	glEnd();

	glColor3ub(250, 250, 250);
	glRectf(carX - 85, carY + 35, carX - 15, carY + 18);

	// Front Part of the Car
	glColor3ub(120, 10, 20);
	glRectf(carX - 50, carY + 35, carX - 45, carY + 18);

	// Car Door Handlers
	glColor3ub(120, 10, 20);
	glRectf(carX - 20, carY + 13, carX - 32, carY + 10);
	glRectf(carX - 72, carY + 13, carX - 60, carY + 10);

	// Exhaust Pipe
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(carX - 107, carY + 5);
	glVertex2f(carX - 115, carY + 5);
	glVertex2f(carX - 115, carY);
	glVertex2f(carX - 107, carY);
	glEnd();

	glColor3ub(70, 70, 70);
	glRectf(carX - 107, carY + 5, carX - 115, carY);

	// Exhaust Gas
	glColor3f(0.7, 0.7, 0.7);
	circle(carX - 120, carY + 10, 2);
	glColor3f(0.6, 0.6, 0.6);
	circle(carX - 130, carY + 15, 3);

	// Wheels
	glColor3f(0.2, 0.2, 0.2);
	circle(carX - 20, carY - 10, 12);
	circle(carX - 80, carY - 10, 12);

	// Inner Part of the Wheels
	glColor3f(0.5, 0.5, 0.5);
	circle(carX - 20, carY - 10, 6);
	circle(carX - 80, carY - 10, 6);

}


void drawCloud() {

	glColor3ub(cl, cl, cl);
	// cloud1
	circle(clX - 270, clY + 32, 30);
	circle(clX - 250, clY + 22, 22);
	circle(clX - 290, clY + 27, 20);
	// cloud2
	circle(clX - 120, clY + 6, 15);
	circle(clX - 130, clY + 4, 10);
	circle(clX - 110, clY, 8);
	// cloud3
	circle(clX - 20, clY + 17, 32);
	circle(clX - 50, clY + 7, 20);
	circle(clX, clY + 7, 23);
}


void display() {
	// Creating the window
	glClearColor(0.85, 0.7, 0.7, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Background
	glBegin(GL_LINES);
	glColor3ub(170, 120, 125);

	// Vertical lines
	for (int x = -600; x <= 600; x += 65) {

		glVertex2f(x, -600);
		glVertex2f(x, 600);

	}
	// Horizontal Lines
	for (int y = -600; y <= 600; y += 65) {

		glVertex2f(600, y);
		glVertex2f(-600, y);

	}
	glEnd();

	// Wallpaper Pattern
	glColor3ub(160, 100, 115);
	for (int x = -600; x <= 600; x += 65)
		for (int y = -600; y <= 600; y += 65)
		{
			circle(x, y, 5);
			circle(x + 5, y + 5, 3);
			circle(x - 5, y - 5, 3);
			circle(x - 5, y + 5, 2);
			circle(x + 5, y - 5, 2);
		}

	// Window
	glColor3ub(120, 60, 60);
	glRectf(-280, 200, 280, -200);

	glColor3ub(145, 75, 75);
	glRectf(-260, 180, 260, -180);

	// Name Handler
	glColor3ub(120, 60, 60);
	glRectf(-200, 260, 200, 230);

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-190, 255);
	glVertex2f(-190, 235);
	glVertex2f(190, 235);
	glVertex2f(190, 255);
	glEnd();

	glColor3ub(150, 90, 90);
	glRectf(-190, 255, 190, 235);
	circle(0, 280, 4);

	glColor3ub(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	// Line 1
	glVertex2f(-100, 260);
	glVertex2f(0, 280);
	// Line 2
	glVertex2f(100, 260);
	glVertex2f(0, 280);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(-200, 260);
	glVertex2f(-200, 230);
	glVertex2f(200, 230);
	glVertex2f(200, 260);
	glEnd();
	glColor3ub(40, 10, 20);
	vprint(-170, 240, GLUT_BITMAP_8_BY_13, "Looking Through the Window by Zeynep Arslan");

	// Sky
	glBegin(GL_POLYGON);
	glColor3ub(skyR, skyG, skyB);
	glVertex2f(-260, 140);
	glColor3ub(skyR, skyG, skyB);
	glVertex2f(260, 140);
	glColor3ub(skyR + 60, skyG + 90, skyB - 10);
	glVertex2f(260, -160);
	glColor3ub(skyR + 60, skyG + 90, skyB - 10);
	glVertex2f(-260, -160);
	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(260, 160);
	glVertex2f(260, -160);
	glVertex2f(-260, -160);
	glVertex2f(-260, 160);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(260, 140);
	glVertex2f(-260, 140);
	glEnd();

	//Mountain
	glColor3ub(mR, mG, mB);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-200, 50);
	glVertex2f(-150, -75);
	glVertex2f(-250, -75);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(-140, 30);
	glVertex2f(-170, -75);
	glVertex2f(-90, -75);
	glEnd();

	glColor3ub(mR + 35, mG + 20, mB + 15);
	glBegin(GL_TRIANGLES);
	glVertex2f(-200, 50);
	glVertex2f(-150, -75);
	glVertex2f(-250, -75);
	glEnd();
	glColor3ub(80, 40, 30);
	glBegin(GL_TRIANGLES);
	glVertex2f(-140, 30);
	glVertex2f(-170, -75);
	glVertex2f(-90, -75);
	glEnd();

	// Snow
	glColor3ub(250, 250, 230);
	glBegin(GL_TRIANGLES);
	glVertex2f(-200, 50);
	glVertex2f(-190, 30);
	glVertex2f(-210, 30);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-140, 30);
	glVertex2f(-145, 15);
	glVertex2f(-132, 15);
	glEnd();


	// Grass
	glColor3ub(0, grG, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-260, -75);
	glVertex2f(260, -75);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(grR, grG, grB); //the part where the sun is brighter :)
	glVertex2f(-260, -75);
	glColor3ub(grR - 3, grG - 30, grB - 15);
	glVertex2f(260, -75);
	glColor3ub(grR - 3, grG - 50, grB - 15);
	glVertex2f(260, -160);
	glVertex2f(-260, -160);
	glEnd();

	// Tree
	glColor3ub(80, 40, 30);
	glRectf(90, -20, 110, -78);
		// Leafs
	glColor3ub(grR - 1, grG - 10, grB - 10);
	circle(80, -25, 22);
	circle(120, -25, 20);
	glColor3ub(grR - 1, grG - 15, grB - 10);
	circle(100, -20, 30);

	// Bush
	glColor3ub(grR, grG - 30, grB - 15);
	circle(180, -75, 10);
	circle(200, -72, 15);
	circle(220, -75, 10);

	// Road
	glColor3ub(10, 10, 10);
	glRectf(-260, -90, 260, -140);

	glColor3ub(250, 250, 250);
	glRectf(-220, -120, -260, -110);
	glRectf(-140, -120, -180, -110);
	glRectf(-60, -120, -100, -110);
	glRectf(20, -120, -20, -110);
	glRectf(100, -120, 60, -110);
	glRectf(180, -120, 140, -110);
	glRectf(260, -120, 220, -110);

	// Sun/Moon :)
	glColor3ub(r - 15, g - 15, b - 10);
	circle(-200, 105, 32);
	glColor3ub(r, g, b);
	circle(-200, 105, 28);

	drawCar();
	drawCloud();

	// Front Part of the Window
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(20, 160);
	glVertex2f(20, -160);
	glVertex2f(-20, -160);
	glVertex2f(-20, 160);
	glEnd();

	glColor3ub(145, 75, 75);
	glRectf(-20, 180, 20, -180);

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0, -180);
	glVertex2f(0, 180);
	glEnd();


	// Window Handler
	glColor3ub(0, 0, 0);
	circle(11, 10, 9);
	circle(-11, 10, 9);
	glBegin(GL_LINE_LOOP);
	glVertex2f(7, -22);
	glVertex2f(50, -22);
	glVertex2f(50, -15);
	glVertex2f(7, -15);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(-7, -22);
	glVertex2f(-50, -22);
	glVertex2f(-50, -15);
	glVertex2f(-7, -15);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(7, -20);
	glVertex2f(14, -20);
	glVertex2f(14, 5);
	glVertex2f(7, 5);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(-7, -20);
	glVertex2f(-14, -20);
	glVertex2f(-14, 5);
	glVertex2f(-7, 5);
	glEnd();

	glColor3ub(120, 105, 100);
	glRectf(7, 5, 14, -20);
	glRectf(-7, 5, -14, -20);

	glRectf(7, -22, 50, -15);
	glRectf(-50, -22, -7, -15);

	circle(11, 10, 8);
	circle(-11, 10, 8);
	glEnd();

	// Fixing the sides of the window to prevent the car and cloud from going over the window and the wallpaper

			// Background
		glColor3ub(216, 178, 178);
		glRectf(280, 200, 500, -200);
		glRectf(-280, 200, -600, -200);
		glBegin(GL_LINES);
		glColor3ub(170, 120, 125);

			// Vertical lines
		for (int x = -600; x <= -288; x += 65) {

			glVertex2f(x, -600);
			glVertex2f(x, 600);

		}
		for (int x = 310; x <= 600; x += 65) {

			glVertex2f(x, -600);
			glVertex2f(x, 600);

		}
			// Horizontal Lines
		for (int y = -600; y <= 600; y += 65) {

			glVertex2f(-280, y);
			glVertex2f(-600, y);
			glVertex2f(280, y);
			glVertex2f(600, y);

		 }
		glEnd();

			// Wallpaper Pattern
		glColor3ub(160, 100, 115);
		for (int x = -600; x <= -288; x += 65)
			for (int y = -600; y <= 600; y += 65)
			{
				circle(x, y, 5);
				circle(x + 5, y + 5, 3);
				circle(x - 5, y - 5, 3);
				circle(x - 5, y + 5, 2);
				circle(x + 5, y - 5, 2);
			}
		for (int x = 310; x <= 600; x += 65)
			for (int y = -600; y <= 600; y += 65)
			{
				circle(x, y, 5);
				circle(x + 5, y + 5, 3);
				circle(x - 5, y - 5, 3);
				circle(x - 5, y + 5, 2);
				circle(x + 5, y - 5, 2);
			}

		glColor3ub(120, 60, 60);
		glRectf(-260, 200, -280, -200);
		glRectf(260, 200, 280, -200);

	// Outline of the Window
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(280, 200);
	glVertex2f(280, -200);
	glVertex2f(-280, -200);
	glVertex2f(-280, 200);
	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(260, 180);
	glVertex2f(260, -180);
	glVertex2f(-260, -180);
	glVertex2f(-260, 180);
	glEnd();

	glutSwapBuffers();
}

void onClick(int button, int stat, int x, int y)
{
	// On left click it becomes night, everything becomes darker
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
		r = 255;
		g = 255;
		b = 255;

		skyR = 0;
		skyG = 0;
		skyB = 50;

		cl = 150;

		grR = 5;
		grG = 100;
		grB = 15;

		mR = 20;
		mG = 5;
		mB = 2;
	}

	// On right click it becomes day, everything is lighter again
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN) {
		r = 255;
		g = 255;
		b = 100;

		skyR = 100;
		skyG = 150;
		skyB = 250;

		cl = 250;

		grR = 10;
		grG = 150;
		grB = 30;

		mR = 35;
		mG = 20;
		mB = 15;
	}

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

void onResize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // Refresh window.
}

void onKeyDown(unsigned char key, int x, int y) {

	// The car and the clouds stop/start when clicking on the spacebar
	if (key == ' ')
		activeTimer = !activeTimer;

	// To refresh the window it calls display() function
	glutPostRedisplay();
}


void onKeyUp(unsigned char key, int x, int y) {

	// Exit when ESC is pressed
	if (key == 27)
		exit(0);

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

void onSpecialKeyDown(int key, int x, int y) {

	// Speeding up the car
	if (key == GLUT_KEY_RIGHT) {
		carSp++;
	}
	// Slowing down the car
	if (key == GLUT_KEY_LEFT && carSp > 1) {
		carSp--;
	}
	// To refresh the window it calls display() function
	glutPostRedisplay();
}
#if TIMER_ON == 1
void onTimer(int v) {
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);

	if (activeTimer) {
		// Animate the car and the clouds 
		clX--;
		carX = carX + carSp;

		//The objects start its movement again after reaching the end of the window
		if (clX < -280)
			clX = 570;
		if (carX > 400)
			carX = -270;
	}
	//to refresh the window it calls display() function
	glutPostRedisplay();
}
#endif

void Init() {
	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Zeynep Arslan");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	// Keyboard Events
	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);
	glutSpecialFunc(onSpecialKeyDown);

	// Mouse Events
	glutMouseFunc(onClick);

#if  TIMER_ON == 1
	// Timer Event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();
	glutMainLoop();
	return(0);
}