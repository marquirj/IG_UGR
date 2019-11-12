//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "algorithm"

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};




//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
		void  parametros(vector<_vertex3f> perfil1, int num1, int tipo,int eje);

		vector<_vertex3f> perfil;
		int num;
};
//*************************************************************************
// clase CILINDRO
//*************************************************************************
class _cilindro: public _rotacion {
public:
    _cilindro(float altura, float radio, int num);
    _vertex3f trio;
    int num;
};
//*************************************************************************
// clase CONO
//*************************************************************************
class _cono: public _rotacion {
public:
	_vertex3f trio;
    _cono(float altura, float radio, int num);
    void conoCompleto(float altura, float radio, int num);
	int num;
};
//*************************************************************************
// clase BOTELLA
//*************************************************************************
class _botella: public _rotacion {
public:
	_vertex3f trio;
    _botella(char *archivo, int num1);

	int num;
};
//*************************************************************************
// clase ESFERA
//*************************************************************************

class _esfera: public _rotacion {
public:
    int num;
    _vertex3f trio;
    _esfera(float radio, float latitud, float longitud);

};
