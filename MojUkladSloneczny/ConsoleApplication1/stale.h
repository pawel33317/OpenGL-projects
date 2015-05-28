#include <GL/gl.h> 

//Promienie Planet
const GLfloat Rmerkury = 0.1;
const GLfloat Rwenus = 0.18;
const GLfloat Rmars = 0.3;
const GLfloat Rjowisz = 0.6;
const GLfloat Rsaturn = 0.5;
const GLfloat Ruran = 0.3;
const GLfloat Rneptun = 0.3;
const GLfloat Rpluton = 0.05;
const GLfloat Rslonce = 1.0;
const GLfloat Rziemia = 0.18;

//Oddalenie od œrodka
const GLfloat Omerkury = 1.5;
const GLfloat Owenus = 2.0;
const GLfloat Omars = 3.5;
const GLfloat Ojowisz = 5.0;
const GLfloat Osaturn = 7.0;
const GLfloat Ouran = 8.5;
const GLfloat Oneptun = 9.0;
const GLfloat Opluton = 10.0;
const GLfloat Oziemia = 3.0;

//zmienne na tekstury
GLuint Tziemia = 1;
GLuint Tmerkury = 2;
GLuint Twenus = 3;
GLuint Tmars = 4;
GLuint Tjowisz = 5;
GLuint Tsaturn = 6;
GLuint Turan = 7;
GLuint Tneptun = 8;
GLuint Tpluton = 9;
GLuint Tslonce = 10;
GLuint TpierscienSaturna = 11;
GLuint Tksiezyc = 12;

//obrów wokó³ w³asnej osi w dniach
const GLfloat Dmercury = 59;
const GLfloat Dwenus = -243;
const GLfloat Dmars = 1;
const GLfloat Djowisz = 0.4;
const GLfloat Dsaturn = 0.4;
const GLfloat Duran = -0.7;
const GLfloat Dneptun = 0.7;
const GLfloat Dpluton = -6;

//obrót wokó³ s³oñca w dniach
const GLfloat Smerkury = 88*2;
const GLfloat Swenus = 225;
const GLfloat Sziemia = 365;
const GLfloat Smars = 686;
const GLfloat Sjowisz = 4333/1.5;
const GLfloat Ssaturn = 10759/2;
const GLfloat Suran = 30685/3;
const GLfloat Sneptun = 60190/6;
const GLfloat Spluton = 90800/9;

//nachylenie
const GLfloat Pmercury = 7;
const GLfloat Pwenus = 3;
const GLfloat Pmars = 2;
const GLfloat Pjowisz = 1;
const GLfloat Psaturn = 2;
const GLfloat Puran = 1;
const GLfloat Pneptun = 2;
const GLfloat Ppluton = 1;
const GLfloat Pziemia = 7;

GLfloat RotacjaDnia = 0.00;
GLfloat RotacjaWokolSlonca = 0.00;
GLfloat DzienneZwiekszanie = 0.01;
