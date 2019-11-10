#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <GL/glut.h>
#include <ctime>


float rotAng;

//values of ball projectile for translation
float ballx = 0;
float bally = 0;
float ballz = 0;

//for controlling ball direction before firing
float directionXR = 0;
float directionXL = 0;

float directionYU = 0;
float directionYD = 0;


bool bottomWallCollision = false;
bool rightWallCollision = false;
bool leftWallCollision = false;
bool topWallCollision = false;
bool throwBall = false;

bool right = false;
bool left = false;



void key(unsigned char k, int x, int y)

{
	

	if (k == 'w') {		 
		directionYU += 0.01;
	}
	if (k == 's') {

		directionYD -= 0.01;
	}
	if (k == 'a') {
		left = true;
		if (directionXL > -0.008) {
			directionXL -= 0.0001;
		}
	}
	if (k == 'd') {
		right = true;
		if (directionXR<0.008) {
			directionXR += 0.0001;
		}	
	}
	/*if (k == 'x') {

	}*/
	
	glutPostRedisplay();
}

void keyUp(unsigned char k, int x, int y)//keyboard up function is called whenever the keyboard key is released				
										 //for throwing 
{

	if (k == 'x') {
		throwBall = true;
	}
	glutPostRedisplay();
}

void drawWallBottomAndTop(double thickness, double x, double z, int random) {
	

	glPushMatrix();
	if (random == 1) {
		glColor3f(1.0, 0.3, 0.0);
	}
	else if(random == 2){
		glColor3f(0.2, 0.4, 1.0);
	}
	else if (random == 3){
		glColor3f(0.5, 0.7, 0.0);
	}
	else if (random == 4) {
		glColor3f(1.0, 1.0, 1.0);
	}
	else {
		glColor3f(1.0, 1.0, 1.0);
	}
	glTranslated(x, 0, z);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawWallRightAndLeft(double thickness, double x, double z, int random) {


	glPushMatrix();
	if (random == 1) {
		glColor3f(0.50, 0.2, 0.6);
	}
	else if (random == 2) {
		glColor3f(0.3, 0.4, 0.2);
	}
	else if (random == 3) {
		glColor3f(0.3, 1.0, 0.2);
	}
	else if (random == 4) {
		glColor3f(0.8, 0.4, 0.2);
	}
	else {
		glColor3f(1.0, 1.0, 1.0);
	}
	glRotated(90, 0, 0, 1);
	glTranslated(x, 0, z);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawWallEnd(double thickness, double x, double z) {
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glColor3f(0.2, 0.0, 0.7);
	glTranslated(x, 0, z);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawRoom() {

	glPushMatrix();
	glTranslatef(0.0, 3.0, 0.0);


	// draw the bottom wall tiles
	glPushMatrix();
	glTranslatef(-3, -6, -15);
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 12; j++) {
			int color = 0;
			if (i % 2 == 0) {
				if (j % 2 == 0) {
					color = 1;
				}
				if (j % 2 != 0) {
					color = 2;
				}

			}
			else {
				if (j % 2 == 0) {
					color = 3;
				}
				if (j % 2 != 0) {
					color = 4;
				}

			}
			drawWallBottomAndTop(0.0, i, j, color);
		}
	}
	glPopMatrix();





	// draw the left wall tiles
	glPushMatrix();
	glTranslatef(-3.5, -5.5, -15);
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 12; j++) {
			int color = 0;
			if (i % 2 == 0) {
				if (j % 2 == 0) {
					color = 1;
				}
				if (j % 2 != 0) {
					color = 2;
				}

			}
			else {
				if (j % 2 == 0) {
					color = 3;
				}
				if (j % 2 != 0) {
					color = 4;
				}

			}
			drawWallRightAndLeft(0.0, i, j, color);
		}
	}
	glPopMatrix();





	// draw the right wall tiles
	glPushMatrix();
	glTranslatef(3.5, -5.5, -15);
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 12; j++) {
			int color = 0;
			if (i % 2 == 0) {
				if (j % 2 == 0) {
					color = 1;
				}
				if (j % 2 != 0) {
					color = 2;
				}

			}
			else {
				if (j % 2 == 0) {
					color = 3;
				}
				if (j % 2 != 0) {
					color = 4;
				}

			}
			drawWallRightAndLeft(0.0, i, j, color);
		}
	}
	glPopMatrix();




	// draw the top wall tiles
	glPushMatrix();
	glTranslatef(-3, 1, -15);
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 12; j++) {
			int color = 0;
			if (i % 2 == 0) {
				if (j % 2 == 0) {
					color = 1;
				}
				if (j % 2 != 0) {
					color = 2;
				}

			}
			else {
				if (j % 2 == 0) {
					color = 3;
				}
				if (j % 2 != 0) {
					color = 4;
				}

			}
			drawWallBottomAndTop(0.0, i, j, color);
		}
	}
	glPopMatrix();





	// draw the end wall tiles
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-3, 0.5, -15.5);
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 6; j++) {
			drawWallEnd(0.0, i, j);
		}
	}
	glPopMatrix();


	glPopMatrix();

}

void drawArrow() {
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glScalef(0.1,0.1,10.0);
	glTranslated(0, -5 ,0.1);
	glutSolidCube(0.5);
	glPopMatrix();

}

void drawBall() {
	glPushMatrix();
	//glTranslatef(ballx, -1, ballz);
	glTranslatef(ballx, bally, ballz);

	glColor3f(1.0f, 0.0f, 1.0f);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();

}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawBall();
	drawRoom();
	glFlush();
}

void Anim() {
	rotAng += 0.08;



	if (throwBall == true) {





		if (bally <= -2.5) {									// hit bottom wall
			bottomWallCollision = true;

		}
		if (ballx >= 3) {										// hit right wall
			rightWallCollision = true;
		}

		if (ballx <= -3) {										// hit left wall
			leftWallCollision = true;
		}

		if (bally >= 3) {										// hit top wall
			topWallCollision = true;
		}


		printf("%d\n",leftWallCollision);

		ballz -= 0.003;
		
		if (bottomWallCollision == true) {  
			topWallCollision = false;
			bally += 0.008;
		}
		else {
			bally -= 0.008;
		}
	/*	if (right == true) {
			if (rightWallCollision == true) {
				leftWallCollision = false;
				ballx -= directionXR;
			}
			else {
				ballx += directionXR;
			}
		}
		if (left == true) {
			if (leftWallCollision == true && left == true) {
				rightWallCollision = false;
				ballx += directionXL;
			}
			else {
				ballx -= directionXL;
			}
		}*/

		



		if (topWallCollision == true) {
			bottomWallCollision = false;
			bally -= 0.008;
		}
		else {
			bally += 0.008;
		}



		

	}

	glutPostRedisplay();
}



void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 150);

	glutCreateWindow("Ball Blaster");
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);


	glClearDepth(1.0f);									// Set background depth to farthest
	glEnable(GL_DEPTH_TEST);							// Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);								// Set the type of depth-test
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 300 / 300, 0.1f, 300.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glutMainLoop();
}
