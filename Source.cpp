#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <GL/glut.h>
#include <ctime>

#include <iostream>
#include <string>

// for replay
bool repeat = false;
float replayDirectionX = 0;
float replayDirectionY = 0;
bool round_finished = false;
bool upReplay = true;
bool downReplay = true;
bool leftReplay = true;
bool rightReplay = true;



// camera modes
float cameraRot = 0;
bool cameraMode1 = false;
bool cameraMode2 = false;
float camera = 35.0;


bool stop_game = false;

float rotAng;

//values of ball projectile for translation
float ballx = 0;
float bally = 0;
float ballz = 25;

//for controlling ball direction before firing
float directionX = 0;
float directionY = 0;
bool right = false;
bool left = false;
bool up = false;
bool down = false;

// for detecting collisions
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


//for lighting tiles on touch
bool upTouchRed = false;
bool upTouchBlue = false;
bool upTouchGreen = false;
bool upTouchOrange = false;

bool rightTouchRed = false;
bool rightTouchBlue = false;
bool rightTouchGreen = false;
bool rightTouchOrange = false;

bool leftTouchRed = false;
bool leftTouchBlue = false;
bool leftTouchGreen = false;
bool leftTouchOrange = false;

bool downTouchRed = false;
bool downTouchBlue = false;
bool downTouchGreen = false;
bool downTouchOrange = false;


//score 
int score = 0;


class TileUp {
public:
	int score;
	float xCoordinate;
	float zCoordinate;
	
};
class TileDown {
public:
	int score;
	float xCoordinate;
	float zCoordinate;

};
class TileLeft {
public:
	int score;
	float yCoordinate;
	float zCoordinate;

};
class TileRight {
public:
	int score;
	float yCoordinate;
	float zCoordinate;

};


TileUp upTiles[240];
TileDown downTiles[240];
TileRight rightTiles[240];
TileLeft leftTiles[240];


void time(int val)
{
	upTouchOrange   = false;
	upTouchGreen    = false;
	upTouchRed      = false;
	upTouchBlue     = false;

	rightTouchRed   =false;
	rightTouchBlue	=false;
	rightTouchGreen	=false;
	rightTouchOrange=false;

	leftTouchRed	=false;
	leftTouchBlue 	=false;
	leftTouchGreen	=false;
	leftTouchOrange	=false;

	downTouchRed	=false;
	downTouchBlue 	=false;
	downTouchGreen	=false;
	downTouchOrange	=false;

	glutPostRedisplay();

}

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
	if (gameRounds != 0) {
		if (k == 'c') {
			cameraMode1 = true;
			cameraMode2 = false;
		}
		if (k == 'v') {
			cameraMode2 = true;
			cameraMode1 = false;
		}

		if (k == 'x') {
			throwBall = true;
			disableKeyboard = true;
		}

		if (k == 'r' && round_finished == true) {
			repeat = true;
			throwBall = true;
			round_finished = false;
		}
	}
	glutPostRedisplay();
}

void drawWallBottomAndTop(double thickness, double x, double z, int random) {

	glPushMatrix();
	if (random == 1) {
		glColor3f(0.7, 0.0, 0.0);
	}
	else if(random == 2){
		glColor3f(0.0, 0.0, 0.7);
	}
	else if (random == 3){
		glColor3f(1.0, 0.5, 0.0);
	}
	else if (random == 4) {
		glColor3f(0.0, 0.5, 0.0);
	}
	else if(random== -1){
		glColor3f(1.0, 0.0, 0.0);
	}
	else if (random == -2) {
		glColor3f(1.0, 0.0, 1.0);
	}
	else if (random == -3) {
		glColor3f(1.0, 1.0, 0.0);
	}
	else if (random == -4) {
		glColor3f(0.0, 1.0, 0.0);
	}


	glTranslated(x, 0, z);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawWallRightAndLeft(double thickness, double x, double z, int random) {


	glPushMatrix();
	if (random == 1) {
		glColor3f(0.0, 0.0, 0.7);
	}
	else if (random == 2) {
		glColor3f(0.7, 0.0, 0.0);
	}
	else if (random == 3) {
		glColor3f(0.0, 0.5, 0.0);
	}
	else if (random == 4) {
		glColor3f(1.0, 0.5, 0.0);
	}
	else if (random == -1) {
		glColor3f(0.0, 0.0, 1.0);
	}
	else if (random == -2) {
		glColor3f(1.0, 0.0, 1.0);
	}
	else if (random == -3) {
		glColor3f(0.0, 1.0, 0.0);
	}
	else if (random == -4) {
		glColor3f(1.0, 1.0, 0.0);
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
	glColor3f(0.5, 0.5, 0.5);
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
	int k = 0;
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 40; j++) {
			int color = 0;
			if (i % 2 == 0) {
				if (j % 2 == 0 && downTouchRed == true) {
					color = -1;
				}
				else if (j % 2 == 0) {
					color = 1;
				}
				else if (j % 2 != 0 && downTouchBlue==true) {
					color = -2;
				}
				else if (j % 2 != 0) {
					color = 2;
				}

			}
			else {
				if (j % 2 == 0 && downTouchOrange == true) {
					color = -3;
				}
				else if (j % 2 == 0) {
					color = 3;
				}
				else if (j % 2 != 0 && downTouchGreen == true) {
					color = -4;
				}
				else if (j % 2 != 0) {
					color = 4;
				}

			}
			// draws one tile every loop
			drawWallBottomAndTop(0.05, i, j, color);
			downTiles[k].score=color;
			downTiles[k].xCoordinate = -3 + i;
			downTiles[k].zCoordinate = -15 + j;
			k++;
		}
	}
	glPopMatrix();





	// draw the left wall tiles
	glPushMatrix();
	glTranslatef(-3.5, -5.5, -15);
	int p = 0;
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 40; j++) {
			int color = 0;
			if (i % 2 == 0) {
				if (j % 2 == 0 && leftTouchRed == true) {
					color = -1;
				}
				else if (j % 2 == 0) {
					color = 1;
				}
				else if (j % 2 != 0 && leftTouchBlue == true) {
					color = -2;
				}
				else if (j % 2 != 0) {
					color = 2;
				}

			}
			else {
				if (j % 2 == 0 && leftTouchOrange == true) {
					color = -3;
				}
				else if (j % 2 == 0) {
					color = 3;
				}
				else if (j % 2 != 0 && leftTouchGreen == true) {
					color = -4;
				}
				else if (j % 2 != 0) {
					color = 4;
				}


			}
			drawWallRightAndLeft(0.05, i, j, color);
			leftTiles[p].score = color;
			leftTiles[p].yCoordinate = (-3.5*sin(90))+(-5.5*cos(90))+i;
			leftTiles[p].zCoordinate = -15 + j;
			p++;
		}
	}
	glPopMatrix();





	// draw the right wall tiles
	glPushMatrix();
	glTranslatef(3.5, -5.5, -15);
	int f = 0;
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 40; j++) {
			int color = 0;
			if (i % 2 == 0) {
				if (j % 2 == 0 && rightTouchRed == true) {
					color = -1;
				}
				else if (j % 2 == 0) {
					color = 1;
				}
				else if (j % 2 != 0 && rightTouchBlue == true) {
					color = -2;
				}
				else if (j % 2 != 0) {
					color = 2;
				}

			}
			else {
				if (j % 2 == 0 && rightTouchOrange == true) {
					color = -3;
				}
				else if (j % 2 == 0) {
					color = 3;
				}
				else if (j % 2 != 0 && rightTouchGreen == true) {
					color = -4;
				}
				else if (j % 2 != 0) {
					color = 4;
				}


			}
			rightTiles[f].score = color;
			rightTiles[f].yCoordinate = (-3.5 * sin(90)) + (-5.5 * cos(90)) + i;
			rightTiles[f].zCoordinate = -15 + j;
			f++;
			drawWallRightAndLeft(0.05, i, j, color);
		}
	}
	glPopMatrix();




	// draw the top wall tiles
	glPushMatrix();
	glTranslatef(-3, 1, -15);
	int u = 0;
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 40; j++) {
			int color = 0;
			if (i % 2 == 0) {
				if (j % 2 == 0 && upTouchRed == true) {
					color = -1;
				}
				else if (j % 2 == 0) {
					color = 1;
				}
				else if (j % 2 != 0 && upTouchBlue==true) {
					color = -2;
				}
				else if (j % 2 != 0) {
					color = 2;
				}

			}
			else {
				if (j % 2 == 0 && upTouchOrange==true) {
					color = -3;
				}
				else if (j % 2 == 0) {
					color = 3;
				}
				else if (j % 2 != 0 && upTouchGreen==true) {
					color = -4;
				}
				else if (j % 2 != 0) {
					color = 4;
				}


			}
			
			upTiles[u].score = color;
			upTiles[u].xCoordinate = -3 + i;
			upTiles[u].zCoordinate = -15 + j;
			drawWallBottomAndTop(0.05, i, j, color);
			u++;
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
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();

}

void reset() {
	ballx = 0;
	bally = 0;
	ballz = 25;

	replayDirectionX = directionX;
	replayDirectionY = directionY;
	rightReplay = right;
	leftReplay = left;
	upReplay = up;
	downReplay = down;

	

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
	cameraRot = 0;
	camera = 35.0;
	//camera =8.0;

	disableKeyboard = false;
}

void Anim() {
	//rotAng += 0.08;

	// replay
	if (repeat == true) {
		if (throwBall == true) {
			camera -= 0.004;

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
				ballx = 0;
				bally = 0;
				ballz = 25;
				directionX = 0;
				directionY = 0;


				rightReplay = false;
				leftReplay = false;
				upReplay = false;
				downReplay = false;

				verticalWallCollisionU = false;
				verticalWallCollisionD = false;
				sideWallCollisionR = false;
				sideWallCollisionL = false;
				throwBall = false;

				angle = 0;
				arrowX = 0;
				arrowY = 0;
				camera =35.0;

				repeat = false;
				disableKeyboard = false;
				

			}



			ballz -= 0.007;


			if (upReplay == true) {
				if (verticalWallCollisionU == true) {
					bally -= replayDirectionY;
				}
				else {
					bally += replayDirectionY;
				}
			}
			if (downReplay == true) {
				if (verticalWallCollisionD == true) {
					bally -= replayDirectionY;
				}
				else {
					bally += replayDirectionY;
				}
			}

			if (leftReplay == true) {
				if (sideWallCollisionL == true) {
					ballx -= replayDirectionX;
				}
				else {
					ballx += replayDirectionX;
				}
			}
			if (rightReplay == true) {
				if (sideWallCollisionR == true) {
					ballx -= replayDirectionX;
				}
				else {
					ballx += replayDirectionX;
				}
			}


		}
	}

	// normal gameplay
	else{

	if (throwBall == true) {

		//camera mode 1
		if (cameraMode1 == true) {
			camera -= 0.004;
			cameraRot -= 0.002;
		}
		//camera mode 2
		if (cameraMode2 == true) {
			camera -= 0.004;
		}

		if (bally <= -2.5) {									// hit bottom wall
			verticalWallCollisionD = true;
			verticalWallCollisionU = false;

			// detecting which tile the ball hit exactly in bottom floor to calculate score
			for (int i = 0; i < sizeof(downTiles)/ sizeof(downTiles[0]); i++) {
				if (ballx<= downTiles[i].xCoordinate+0.5 && ballx >= downTiles[i].xCoordinate - 0.5 && ballz <= downTiles[i].zCoordinate + 0.5 && ballz >= downTiles[i].zCoordinate - 0.5) {
					if (downTiles[i].score == 1) {
						downTouchRed = true;
						score += 1;
					}
					if (downTiles[i].score == 2) {
						downTouchBlue = true;
						score += 2;
					}
					if (downTiles[i].score == 3) {
						downTouchOrange = true;
						score += 3;
					}
					if (downTiles[i].score == 4) {
						downTouchGreen = true;
						score -= 2;
					}
				}

			}
			glutTimerFunc(500, time, 0);
			
		}
		else if (bally >= 3) {										// hit top wall
			verticalWallCollisionU = true;
			verticalWallCollisionD = false;
			// detecting which tile the ball hit exactly in top wall to calculate score
			for (int i = 0; i < sizeof(upTiles) / sizeof(upTiles[0]); i++) {
				if (ballx <= upTiles[i].xCoordinate + 0.5 && ballx >= upTiles[i].xCoordinate - 0.5 && ballz <= upTiles[i].zCoordinate + 0.5 && ballz >= upTiles[i].zCoordinate - 0.5) {
					if (upTiles[i].score == 1) {
						upTouchRed = true;
						score += 1;
					}
					if (upTiles[i].score == 2) {
						upTouchBlue = true;
						score += 2;
					}
					if (upTiles[i].score == 3) {
						upTouchOrange = true;
						score += 3;
					}
					if (upTiles[i].score == 4) {
						upTouchGreen = true;
						score -= 2;
					}
				}

			}
			glutTimerFunc(500, time, 0);


		}


		else if (ballx >= 3) {										// hit right wall
			sideWallCollisionR = true;
			sideWallCollisionL = false;
			// detecting which tile the ball hit exactly in right floor to calculate score
			for (int i = 0; i < sizeof(rightTiles) / sizeof(rightTiles[0]); i++) {
				if (bally <= rightTiles[i].yCoordinate + 0.5 && bally >= rightTiles[i].yCoordinate - 0.5 && ballz <= rightTiles[i].zCoordinate + 0.5 && ballz >= rightTiles[i].zCoordinate - 0.5) {
					if (rightTiles[i].score == 1) {
						rightTouchBlue = true;
						score += 2;
					}
					if (rightTiles[i].score == 2) {
						rightTouchRed = true;
						score += 1;
					}
					if (rightTiles[i].score == 3) {
						rightTouchGreen = true;
						score -= 2;
					}
					if (rightTiles[i].score == 4) {
						rightTouchOrange = true;
						score += 3;
					}
				}

			}
			glutTimerFunc(500, time, 0);
		
		}
		else if (ballx <= -3) {										// hit left wall
			sideWallCollisionR = false;
			sideWallCollisionL = true;
			// detecting which tile the ball hit exactly in left floor to calculate score
			for (int i = 0; i < sizeof(leftTiles) / sizeof(leftTiles[0]); i++) {
				
				if (bally <= leftTiles[i].yCoordinate + 0.5 && bally >= leftTiles[i].yCoordinate - 0.5 && ballz <= leftTiles[i].zCoordinate + 0.5 && ballz >= leftTiles[i].zCoordinate - 0.5) {
					if (leftTiles[i].score == 1) {
						leftTouchBlue = true;
						score += 2;
					}
					if (leftTiles[i].score == 2) {
						leftTouchRed = true;
						score += 1;
					}
					if (leftTiles[i].score == 3) {
						leftTouchGreen = true;
						score -=2;
					}
					if (leftTiles[i].score == 4) {
						leftTouchOrange = true;
						score += 3;
					}
					
				}

			}
			glutTimerFunc(500, time, 0);
		}

		if (ballz <= -15.5) {									// stick to the end wall
			gameRounds -= 1;
			reset();
			round_finished = true;
		}



		ballz -= 0.007;


		if (up == true) {
			if (verticalWallCollisionU == true) {
				bally -= directionY;
			}
			else {
				bally += directionY;
			}
		}
		if (down == true) {
			if (verticalWallCollisionD == true) {
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
}

	glutPostRedisplay();
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 20 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	GLfloat lightIntensity[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat lightPosition[] = { 0.1f, 0.1f,0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	setupLights();


	gluLookAt(0.0f, 0.0f, camera, 0.0f, 1.0f, 0.0f, cameraRot, 1.0f, 0.0f);

	drawBall();
	//drawArrow();
	drawRoom();
	char result[100];   // array to hold the result.

	if (gameRounds == 3) {
		displayText(-1, -3.4, 25, 1, 0, 0, "Game Round: 3");
	}
	if (gameRounds == 2) {
		displayText(-1, -3.4, 25, 1, 0, 0, "Game Round: 2");
	}
	if (gameRounds == 1) {
		displayText(-1, -3.4, 25, 1, 0, 0, "Game Round: 1");
	}
	if (gameRounds == 0) {
		displayText(-1, -3.4, 25, 1, 0, 0, "Game Over");
	}





	if (upTouchRed == true || downTouchRed == true || rightTouchRed == true || leftTouchRed == true) {
		displayText(0, 0, 25, 1, 0, 0, "+1");
	}

	glFlush();

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

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


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
	glutTimerFunc(0, time, 0);

	glutMainLoop();
}
