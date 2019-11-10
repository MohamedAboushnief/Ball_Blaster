#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <GL/glut.h>
#include <ctime>

#include <iostream>
#include <string>

bool repeat = false;
float camera = 8.0;

float rotAng;

//values of ball projectile for translation
float ballx = 0;
float bally = 0;
float ballz = 0;

//for controlling ball direction before firing
float directionX = 0;
float directionY = 0;


bool right = false;
bool left = false;
bool up = false;
bool down = false;

bool verticalWallCollisionU = false;
bool verticalWallCollisionD = false;
bool sideWallCollisionR = false;
bool sideWallCollisionL = false;
bool throwBall = false;

float angle = 0;  
int arrowX = 0; 
int arrowY = 0;

bool disableKeyboard = false;

int gameRounds = 3;



void displayText(float x, float y,float z, int r, int g, int b, const char* string) {
	int j = strlen(string);
	glColor3f(r, g, b);
	glRasterPos3f(x, y,z);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void key(unsigned char k, int x, int y)

{
	if (disableKeyboard == false) {

		if (k == 'w') {
			up = true;
			if (directionY < 0.008) {
				directionY += 0.0001;
				//arrowY = 1;
			}
		}
		if (k == 's') {
			down = true;
			if (directionY < 0.008) {
				directionY -= 0.0001;
				//arrowY = 1;
			}
		}

		if (k == 'd') {
			right = true;
			if (directionX < 0.008) {
				directionX += 0.0001;
				//arrowX = 1;
			}
		}

		if (k == 'a') {
			left = true;
			if (directionX > -0.008) {
				directionX -= 0.0001;
				//arrowX = 1;
			}
		}
	}
	
	glutPostRedisplay();
}

void keyUp(unsigned char k, int x, int y)//keyboard up function is called whenever the keyboard key is released				
										 //for throwing 
{

	if (k == 'x') {
		throwBall = true;
		disableKeyboard = true;
	}

	if (k == 'r') {
		repeat = true;
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
	//glRotatef(-rotAng, 1, 1, 0);
	glScalef(0.2,0.2,1);
	glTranslated(0, 0, 4);
	glRotatef(-20,arrowX,arrowY,0);
	
	glutSolidCube(0.5);
	glPopMatrix();

}

void drawBall() {
	glPushMatrix();
	glTranslatef(ballx, bally, ballz);
	glColor3f(1.0f, 0.0f, 1.0f);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();

}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, camera, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	drawBall();
	//drawArrow();
	drawRoom();
	char result[100];   // array to hold the result.

	if (gameRounds == 3) {
		displayText(-1, -2.3, 1, 1, 0, 0, "Game Round: 3");
	}
	if (gameRounds == 2) {
		displayText(-1, -2.3, 1, 1, 0, 0, "Game Round: 2");
	}
	if (gameRounds == 1) {
		displayText(-1, -2.3, 1, 1, 0, 0, "Game Round: 1");
	}
	if (gameRounds == 0) {
		displayText(-1, -2.3, 1, 1, 0, 0, "Game Over");
	}




	glFlush();
}

void Anim() {
	rotAng += 0.08;


	if (repeat == true) {

	}

	
	if (throwBall == true) {
		//camera -= 0.002;

		if (bally <= -2.5) {									// hit bottom wall
			verticalWallCollisionD = true;
			verticalWallCollisionU = false;
		}
		if (bally >= 3) {										// hit top wall
			verticalWallCollisionU = true;
			verticalWallCollisionD = false;
		}


		if (ballx >= 3) {										// hit right wall
			sideWallCollisionR = true;
			sideWallCollisionL = false;
		}
		if (ballx <= -3) {										// hit left wall
			sideWallCollisionR = false;
			sideWallCollisionL = true;
		}

		if (ballz <= -15.5) {									// stick to the end wall
			gameRounds -= 1;
			ballx = 0;
			bally = 0;
			ballz = 0;
			directionX = 0;
			directionY = 0;


			right = false;
			left = false;
			up = false;
			down = false;

			verticalWallCollisionU = false;
			verticalWallCollisionD = false;
			sideWallCollisionR = false;
			sideWallCollisionL = false;
			throwBall = false;

			angle = 0;
			arrowX = 0;
			arrowY = 0;
			//camera =8.0;

			disableKeyboard = false;
			
		}



		ballz -= 0.003;
		

		if (up== true) {
			if (verticalWallCollisionU == true) {
				bally -= directionY;
			}
			else {
				bally += directionY;
			}
		}
		if (down == true) {
			if (verticalWallCollisionD== true) {
				bally -= directionY;
			}
			else {
				bally += directionY;
			}
		}

		if (left == true) {
			if (sideWallCollisionL == true) {
				ballx -= directionX;
			}
			else {
				ballx += directionX;
			}
		}
		if (right == true) {
			if (sideWallCollisionR == true) {
				ballx -= directionX;
			}
			else {
				ballx += directionX;
			}
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
	//gluLookAt(0.0f, 0.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glutMainLoop();
}
