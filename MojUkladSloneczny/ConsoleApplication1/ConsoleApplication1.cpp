#include "stdafx.h"
#include <windows.h> 
#include <GL/gl.h> 
#include <glut.h> 
#include <math.h>
#include <stdlib.h> 
#include <cstdlib>
#include "stale.h"
#include "RGBpixmap.h"
//kont rotacji kamery
float angle = 0.0;
//pozycja kamery
float x = 0.0f, z = 15.0f, y = 0.0f;
//po³o¿enie obiektu na który patrzy siê kamera
float lx = 0.0f, lz = 0.0f, ly=0.0f;
//do myszy
float deltaAngle = 0.0f;
int xOrigin = -1;
//oœwietlenie
GLfloat ambientLight[] = { 0.50f, 0.50f, 0.50f, 1.0f };


void initRendering();

double ObrotPlanet = 0.0;
void czytajObraz(const char obrazchar[], GLuint &nazwaTekstury)
{
	RGBpixmap pix;
	pix.readBMPFile(obrazchar, false);
	pix.setTexture(nazwaTekstury);
	return;
}
void ladujObrazy()
{
	czytajObraz("obrazy/slonce.bmp", Tslonce);
	czytajObraz("obrazy/merkury.bmp", Tmerkury);
	czytajObraz("obrazy/ziemia.bmp", Tziemia);
	czytajObraz("obrazy/jowisz.bmp", Tjowisz);
	czytajObraz("obrazy/saturn.bmp", Tsaturn);
	czytajObraz("obrazy/uran.bmp", Turan);
	czytajObraz("obrazy/neptun.bmp", Tneptun);
	czytajObraz("obrazy/mars.bmp", Tmars);
	czytajObraz("obrazy/pluton.bmp", Tpluton);
	czytajObraz("obrazy/wenus.bmp", Twenus);
	czytajObraz("obrazy/saturnpierscien.bmp", TpierscienSaturna);
	czytajObraz("obrazy/ksiezyc.bmp", Tksiezyc);
	return;
}
void rysujPlanete(GLfloat nachylenie, GLfloat dlugoscRoku, GLfloat oddalenieOdSrodka, GLfloat obrotOsi, GLuint tekstura, GLfloat promien)
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
			glRotatef(nachylenie, 0.0, 0.0, 1.0);
			//wokó³ s³oñca
			if (dlugoscRoku!=0.0)
			glRotatef(RotacjaWokolSlonca*(1/dlugoscRoku)*100000, 0.0, 1.0, 0.0);
			glTranslatef(oddalenieOdSrodka, 0.0, 0.0);
			//wokó³ w³asnej osi
			glRotatef(360.0 *(ObrotPlanet/obrotOsi), 0.0, 1.0, 0.0);
			//obrócenie w celu normalnoœci planety - pieguny na górze
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glBindTexture(GL_TEXTURE_2D, tekstura);
			gluSphere(quadro, promien, 48, 48);
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
void rysujPierscien()
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
			glRotatef(Psaturn, 0.0, 0.0, 1.0);
			//glRotatef(360.0 * (RotacjaWokolSlonca / Ssaturn), 0.0, 1.0, 0.0);
			glRotatef(RotacjaWokolSlonca*(1 / Ssaturn) * 100000, 0.0, 1.0, 0.0);
			//nachylenie
			glTranslatef(Osaturn, 0.0, 0.0);
			//obrócenie w celu normalnoœci planety - pieguny na górze
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glBindTexture(GL_TEXTURE_2D, TpierscienSaturna);
			glScalef(1, 1, .02);
			gluSphere(quadro, Rsaturn * 2, 48, 48);
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}
void rysujKsiezyc()
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
		//nachylenie
		glRotatef(Pziemia, 0.0, 0.0, 1.0);
		//wokó³ s³oñca
		glRotatef(RotacjaWokolSlonca*(1 / Sziemia) * 100000, 0.0, 1.0, 0.0);
		glTranslatef(Oziemia, 0.0, 0.0);
		//wokó³ w³asnej osi
		glRotatef(360.0 *(ObrotPlanet / 1)*4, 0.0, 1.0, 0.0);
			//oddalenie od ziemi
			glTranslatef(0.5, 0.0, 0.0);
			glBindTexture(GL_TEXTURE_2D, Tksiezyc);
			gluSphere(quadro, 0.04, 48, 48);
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	//gdzie kamera, gdzie sie patrzy, gdzie gora
	//na œrodku w poziomie, w pionie na œrodku, oddalenie
	gluLookAt(x, y,z, lx, ly, lz, 0.0f, 1.0f, 0.0f);
	initRendering();
	rysujPlanete(0.0f, 0, 0, 365, Tslonce, Rslonce);
	rysujPlanete(Pziemia, Sziemia, Oziemia, 1, Tziemia, Rziemia);
	rysujPlanete(Pmercury, Smerkury, Omerkury, Dmercury, Tmerkury, Rmerkury);
	rysujPlanete(Psaturn, Ssaturn, Osaturn, Dsaturn, Tsaturn, Rsaturn);
	rysujPlanete(Ppluton, Spluton, Opluton, Dpluton, Tpluton, Rpluton);
	rysujPlanete(Pmars, Smars, Omars, Dmars, Tmars, Rmars);
	rysujPlanete(Pneptun, Sneptun, Oneptun, Dneptun, Tneptun, Rneptun);
	rysujPlanete(Pwenus, Swenus, Owenus, Dwenus, Twenus, Rwenus);
	rysujPlanete(Pjowisz, Sjowisz, Ojowisz, Djowisz, Tjowisz, Rjowisz);
	rysujPlanete(Psaturn, Suran, Ouran, Duran, Turan, Ruran);
	rysujPierscien();
	rysujKsiezyc();

	glutSwapBuffers();
}
void processSpecialKeys(int key, int xx, int yy) {
	float fraction = 0.3f;
	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.05f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.05f;
		lx = sin(angle);
		lz = -cos(angle);
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
void processNormalKeys(unsigned char key, int xx, int yy) {
	if (key == 27)
		exit(0);
	switch (key) {
	case 'w':
		y = y + 1.0f;
		break;
	case 's':
		y = y - 1.0f;
		break;
	case 'r':
		y = 0.0f;
		x = 0.0f;
		z = 15.0f;
		ly = 0.0f;
		lx = 0.0f;
		lz = 0.0f;
		break;
	case 'z':
		DzienneZwiekszanie = DzienneZwiekszanie - 0.001;
		break;
	case 'x':
		DzienneZwiekszanie = DzienneZwiekszanie + 0.001;
		break;
	case 'o':
		glDisable(GL_LIGHTING);
		break;
	case 'p':
		initRendering();
		break;
	}
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
		lx = sin(angle + deltaAngle)*3;
		lz = -cos(angle + deltaAngle)*3;
	}
}


const GLfloat LIGHT_0_POSITION[] = { 0.0, 0.0, 2.0, 1.0 };
const GLfloat LIGHT_7_POSITION[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat LIGHT_8_POSITION[] = { 1.0, -1.0, 1.0, 1.0 };
const GLfloat LIGHT_9_POSITION[] = { -1.0, 1.0, 1.0, 1.0 };
const GLfloat LIGHT_10_POSITION[] = { -1.0, -1.0, 1.0, 1.0 };
const GLfloat LIGHT_1_POSITION[] = { 0.0, 0.0, -2.0, 1.0 };
const GLfloat LIGHT_3_POSITION[] = { 2.0, 0.0, 0.0, 1.0 };
const GLfloat LIGHT_4_POSITION[] = { -2.0, 0.0, 0.0, 1.0 };
const GLfloat LIGHT_5_POSITION[] = { 0.0, 2.0, 0.0, 1.0 };
const GLfloat LIGHT_6_POSITION[] = { 0.0, -2.0, 0.0, 1.0 };
const GLfloat LIGHT_AMBIENT[] = { 0.05, 0.05, 0.05, 1.0 };
const GLfloat LIGHT_DIFFUSE[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat LIGHT_SPECULAR[] = { 1.0, 1.0, 1.0, 1.0 };
void initRendering() {
		glEnable(GL_LIGHTING);
			//glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT_AMBIENT);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFFUSE);
			glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
			glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, LIGHT_DIFFUSE);
			glLightfv(GL_LIGHT1, GL_SPECULAR, LIGHT_SPECULAR);
			glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);
			glEnable(GL_LIGHT1);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, LIGHT_DIFFUSE);
			glLightfv(GL_LIGHT2, GL_SPECULAR, LIGHT_SPECULAR);
			glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_3_POSITION);
			glEnable(GL_LIGHT2);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, LIGHT_DIFFUSE);
			glLightfv(GL_LIGHT3, GL_SPECULAR, LIGHT_SPECULAR);
			glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_4_POSITION);
			glEnable(GL_LIGHT3);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, LIGHT_DIFFUSE);
			glLightfv(GL_LIGHT4, GL_SPECULAR, LIGHT_SPECULAR);
			glLightfv(GL_LIGHT4, GL_POSITION, LIGHT_5_POSITION);
			glEnable(GL_LIGHT4);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, LIGHT_DIFFUSE);
			glLightfv(GL_LIGHT5, GL_SPECULAR, LIGHT_SPECULAR);
			glLightfv(GL_LIGHT5, GL_POSITION, LIGHT_6_POSITION);
			glEnable(GL_LIGHT5);
			glLightfv(GL_LIGHT6, GL_DIFFUSE, LIGHT_DIFFUSE);
			glLightfv(GL_LIGHT6, GL_SPECULAR, LIGHT_SPECULAR);
			glLightfv(GL_LIGHT6, GL_POSITION, LIGHT_7_POSITION);
			glEnable(GL_LIGHT6);
			glLightfv(GL_LIGHT7, GL_DIFFUSE, LIGHT_DIFFUSE);
			glLightfv(GL_LIGHT7, GL_SPECULAR, LIGHT_SPECULAR);
			glLightfv(GL_LIGHT7, GL_POSITION, LIGHT_8_POSITION);
			glEnable(GL_LIGHT7);

}
void funkcjaCzasu(int val)
{
	ObrotPlanet = ObrotPlanet + DzienneZwiekszanie;
	RotacjaWokolSlonca = RotacjaWokolSlonca + DzienneZwiekszanie;
	glutTimerFunc(20, funkcjaCzasu, 1);
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	//z bufor | bufor | kolory
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("Uk³ad S³oneczny");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutTimerFunc(20, funkcjaCzasu, 1);
	//tryb bezczynnoœci
	glutIdleFunc(renderScene);
	//po naciœniêciu klawisza
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	//obs³uga myszy
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	//OpenGL init
	ladujObrazy();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//widok g³êbokoœci
	glEnable(GL_DEPTH_TEST);
	//start
	glutMainLoop();
	return 1;
}