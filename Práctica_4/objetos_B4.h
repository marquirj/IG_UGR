//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID, SOLID_ILLUMINATED_FLAT, SOLID_ILLUMINATED_GOURAUD} _modo;

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
void    draw_iluminacion_plana();
void    draw_iluminacion_suave();

vector<_vertex3i> caras;
vector<_vertex3i> caras_par;
vector<_vertex3i> caras_imp;
vector<_vertex3f>normales_caras;
vector<_vertex3f>normales_vertices;
void calcular_normales_caras();
void calcular_normales_vertices();
bool b_normales_caras;
bool b_normales_vertices;
_vertex4f ambiente_difusa;
_vertex4f especular;
float brillo;

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
void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);

vector<_vertex3f> perfil;
int num;
};
//*************************************************************************
// clase ESFERA
//*************************************************************************

class _esfera: public _rotacion {
public:
    int num;
    _vertex3f trio;
    _esfera(float radio=1.0, float latitud=10.0, float longitud=10.0);

};

//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  rodamiento;
_cubo  base;
};



//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};



//************************************************************************
// objeto articulado: gruaJuan
//************************************************************************




//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_tubo;
float giro_torreta;

float giro_tubo_min;
float giro_tubo_max;

protected:
_chasis  chasis;
_torreta  torreta;
_tubo     tubo;
};

//************************************************************************
// objeto articulado: gruaJuan
//************************************************************************

class _base: public _triangulos3D{
public:
	_base();
	void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
	float altura;
protected:
	_cubo base;
};
class _estructuraVertical: public _triangulos3D
{
public:
       _estructuraVertical();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;
protected:
_cubo  trozos;//rodamiento;
_cubo baseSuperior;
};

class _estructuraHorizontal: public _triangulos3D{
public:
	_estructuraHorizontal();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
protected:
	_cubo trozo;
};

class _contraPeso: public _triangulos3D{
public:
	_contraPeso();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
protected:
	_cubo contra;
};

class _carro: public _triangulos3D{
public:
	_carro();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
protected:
	_cubo carro;
};
class _cuerda: public _triangulos3D{
public:
	_cuerda();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
protected:

	_cubo cuerda;
	//_esfera bola(1.0,10.0,10.0);
};

class _maza: public _triangulos3D{
public:
	_maza();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
protected:
	_esfera maza;
};


class _grua: public _triangulos3D
{
public:
       _grua();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_centro;
float giro_b;
float moverCarro;
float moverCarroMax;
float moverCarroMin;

float moverCuerda;
float moverCuerdaMax;
float moverCuerdaMin;

float giroMaza;
protected:
_estructuraVertical  estructuraVertical;
_base base;
_estructuraHorizontal estructuraHorizontal;
_contraPeso contraPeso;
_carro carro;
_cuerda cuerda;
_maza maza;
//_esfera esfera
};
