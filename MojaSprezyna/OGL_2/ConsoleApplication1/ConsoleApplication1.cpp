#include "stdafx.h"
#include <windows.h> 
#include <GL/gl.h> 
#include <glut.h> 
#include <math.h>
#include <stdlib.h> 
#include <cstdlib>
#include "imageloader.h"
//kont rotacji kamery
float angle = 0.0;
//po³o¿enie kamery
float lx = 0.0f, lz = -1.0f, ly=0.0f;
//pozycja kamery
float x = 0.0f, z = 5.0f, y = 1.0f;
//do myszy
float deltaAngle = 0.0f;
int xOrigin = -1;
GLUquadricObj *sphere = NULL;
GLuint _textureId;
GLuint textureId2, textureId3;
float anglec = 0;
GLfloat ambientLight[] ={ 0.90f, 0.90f, 0.90f, 1.0f };
float ypos, ysin=0;
int spr=1;
float podstawowyKatObrotySprezyny = 21.0;
int tmp3 = 0; int tmp4=1;
float odstepSprezyn = 0.107;
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB,
		image->width, image->height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		image->pixels);
	return textureId;
}
void changeSize(int w, int h) {
	//nie mo¿e byæ okna z zerow¹ d³ugoœci¹
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// Use the Projection Matrix
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	
	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
void renderScene(void) {


	//ypos = A*sin(Xx); Xx += 1.0f; if (A>0) A -= 0.01f;

	if (ysin < -0.6f)
		spr = 1;
	if (ysin > 0.6)
		spr = -1;
	if (spr == -1)
	{
		anglec = anglec + 0.027f;
		ysin = ysin - 0.001f;
	}
		
	else
	{
		ysin = ysin + 0.001f;
		anglec = anglec - 0.027f;
	}
		

	ypos = 1* sin(ysin);

	//czyszczenie
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Reset transformations
	glLoadIdentity();
	//ustawienie kamery
	gluLookAt(x, y, z, x + lx, y+ly, z + lz, 0.0f, 1.0f, 0.0f);

	//pod³o¿e
	glColor3f(0.1, 0.6, 0.1);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	//tylna œciana
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureId2);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-8.0f, 0.0f, -10.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(8.0f, 0.0f, -10.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(8.0f, 8.0f, -10.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-8.0f, 8.0f, -10.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//sufit sprê¿yny
	glColor3f(0.1f, 0.0f, 0.2f);
	//glColor3f(0.6f, 0.2f, 0.9f);
	glPushMatrix();
		//glEnable(GL_TEXTURE_2D);
		//glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//glEnable(GL_TEXTURE_GEN_T);
		//glBindTexture(GL_TEXTURE_2D, textureId3);
		glTranslatef(0, 2.5, 0);
		glScalef(8, 0.5, 8);
		glutSolidCube(0.25);
		//glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		//glDisable(GL_TEXTURE_GEN_T);
		//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//raczka na sprezyne gora
	glColor3f(0.3f, 0.3f, 0.3f);
	glPushMatrix();
		glTranslatef(0, 2.3, 0);
		glScalef(1, 2.50, 1);
			glutSolidCube(0.05);
	glPopMatrix();

	//raczka gorna 2
	glColor3f(0.3f, 0.3f, 0.3f);
	glPushMatrix();
		glTranslatef(0.05, 2.25, 0);
		glScalef(3, 0.5, 1);
			glutSolidCube(0.05);
	glPopMatrix();



	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////

	tmp4 = -1;
	for (tmp3 = 0; tmp3 < 9; tmp3++)
	{
		if (tmp4 == 1)
			tmp4 = -1;
		else
			tmp4 = 1;
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
		glEnable(GL_TEXTURE_GEN_T);
		glBindTexture(GL_TEXTURE_2D, textureId3);
			glTranslatef(0, 1.35 + odstepSprezyn*tmp3+(ypos*(8-tmp3))/7, 0);
			glRotated(tmp4*podstawowyKatObrotySprezyny, 0.0f, 0.0f, 1.0f);
			glRotated(anglec*tmp4, 0.0f, 0.0f, 1.0f);
			glScalef(3.0, 0.3, 0.5);
			glutSolidCube(0.1);
			glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}



	glTranslatef(0, (ypos*(8)) / 7 + ypos*0.06, 0);
	//raczka na sprezyne kuli 
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glTranslatef(0, 1.2, 0);
	glScalef(1, 3, 1);
	glutSolidCube(0.05);
	glPopMatrix();
	//raczka na sprezyne kuli 2
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glTranslatef(-0.05, 1.275, 0);
	glScalef(3, 0.5, 1);
	glutSolidCube(0.05);
	glPopMatrix();
	//kula 	
	//glutSolidSphere(0.2f, 40, 40);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTranslatef(0, 1, 0);
	gluSphere(sphere, 0.2f, 40, 40);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glTranslatef(0, -ypos, 0);

	////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	//przerzuca tylni bufor na przedni
	glutSwapBuffers();
	
}
void processSpecialKeys(int key, int xx, int yy) {
	float fraction = 0.3f;
	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.05f;
		lx = sin(angle);
		lz = -cos(angle);
		//y -= ly * 10;
		//z += lz * fraction;
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.05f;
		lx = sin(angle);
		lz = -cos(angle);
		//y += ly * 10;
		//z -= lz * fraction;
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}
void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}
void mouseButton(int button, int state, int x, int y) {
	//je¿eli lewy przycisk wciœniêty
	if (button == GLUT_LEFT_BUTTON) {
		//po puszczeniu przycisku
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {//je¿eli wciœniêty
			xOrigin = x;
		}
	}
}
void mouseMove(int x, int y) {
	//je¿eli wciœniêty lewy przycisk myszy
	if (xOrigin >= 0) {
		//zmiana k¹ta
		deltaAngle = (x - xOrigin) * 0.001f;
		//zmiana kierunku kamery
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}
void initRendering() {
	glClearColor(0.1, 0.1, 0.7, 1.0);
		//widok g³êbokoœci
		glEnable(GL_DEPTH_TEST);

		////////////OŒWIETLENIE
		//w³¹cza oœwietlenie //odleg³oœæ od obserwatora nie kolejnoœæ rysowania decyduje co jest widoczne
		glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);
		//scena oparta na œwietle otaczaj¹cym
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
		//oznacza cieniowanie technik¹ Gourauda. Jest to najdok³adniejsza metoda oferowana przez OpenGL
		glShadeModel(GL_SMOOTH);
		glEnable(GL_COLOR_MATERIAL);
		glDisable(GL_CULL_FACE);

		/////////////TEKSTURY
		//w³¹cza teksturowanie
		glEnable(GL_TEXTURE_2D);
		//³adujemy teksturê

		//Kwadryka (np. kula, walec, elipsoida, paraboloida, sto¿ek, hiperboloida) jest powierzchni¹ drugiego stopnia mo¿e byæ ³atwo przesuwana i skalowana
		sphere = gluNewQuadric();
		//style wype³nienia
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricTexture(sphere, GL_TRUE);
		gluQuadricNormals(sphere, GLU_SMOOTH);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		//jak ma teksturowaæ np repeat
		Image* image = loadBMP("a1.bmp");
		_textureId = loadTexture(image);
		delete image;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Image* image2 = loadBMP("a2.bmp");
		textureId2 = loadTexture(image2);
		delete image2;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Image* image3 = loadBMP("a3.bmp");
		textureId3 = loadTexture(image3);
		delete image3;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	//z bufor | bufor | kolory
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Sprê¿yna");
	//register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	//tryb bezczynnoœci
	glutIdleFunc(renderScene);
	//po naciœniêciu klawisza
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	//obs³uga myszy
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	//OpenGL init
	initRendering();
	//start
	glutMainLoop();
	return 1;
}