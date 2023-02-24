//**************************************************************************
// Proyecto final: Alejandro
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS, SOLID_FLAT, SOLID_SMOOTH,SELECT} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
vector<_vertex3f> colores_vertices;
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
void 	draw_solido_colores();
void    draw_seleccion(int r, int g, int b);

/* Permite dibujar objetos con iluminación plana*/
void  draw_solido_plano();
/* Permite dibujar objetos con iluminación con suavizado de Gouraud */
void  draw_solido_suave();

void 	draw(_modo modo, float r, float g, float b, float grosor);

/* asignación de colores */
void 	colors_random();
void 	colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);
void  colors_lambert_c (float l_x, float l_y, float l_z, float r, float g, float b);

/* Permite calcular normales a triángulos y a vértices*/
void calcular_normales_caras();
void calcular_normales_vertices(int tipo);    // tipo == 0 objeto cualquiera, tipo == 1 esfera

vector<_vertex3i> caras;     // esto guarda los indices de los vertices en el vector de vertices
vector<_vertex3f> colores_caras; // añadido para poder colorear


vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

// material
_vertex4f ambiente;
_vertex4f difuso;
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

	_piramide(float tam=0.5, float al=1.0);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

void  parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************
// tipo indica si es una figura por revolución normal o bien un cono o una esfera
// tipo=0 normal, tipo=1 cono, tipo=2 esfera
// tapa_in=0 sin tapa inferior, tap_in=1 con tapa inferior
// tapa_su=0 sin tapa superior, tapa_su con tapa superior


class _rotacion: public _triangulos3D
{
public:
       _rotacion();
       
void  parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su);
//void  parametros(vector<_vertex3f> perfil, int num);
};

//************************************************************************
// cilindro
//************************************************************************
class _cilindro: public _rotacion
{
public:
		_cilindro(float radio=1.0, float altura=2.0, int num=12);
};

//************************************************************************
// cono
//************************************************************************
class _cono: public _rotacion
{
	public:
		_cono(float radio=0.1, float altura=5, int num=10);
};

//************************************************************************
// esfera
//************************************************************************
class _esfera: public _rotacion
{
	public:
		_esfera(float radio=0.1, int num1=10, int num2=10);
            void calcular_normales_vertices_esfera();
};

//************************************************************************
// objeto por rotación a través de archivo PLY
//************************************************************************

class _rotacion_ply: public _rotacion
{
	public:
		_rotacion_ply();
		void parametros_rotacion_ply(char *fichero, int num); 

};


//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion: public _triangulos3D
{
public:
       _extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};



//************************************************************************
// práctica 3, objeto jerárquico articulado excavadora
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

class _pala: public _triangulos3D
{
public:
      _pala(float radio=1.0, float ancho=2.0, int num=8);
};

//************************************************************************
// brazo
//************************************************************************

class _brazo: public _triangulos3D
{
public:
      _brazo();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

//************************************************************************
// cabina
//************************************************************************

class _cabina: public _triangulos3D
{
public:
       _cabina();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

//************************************************************************
// sustentación
//************************************************************************

class _sustentacion: public _triangulos3D
{
public:
      _sustentacion();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
_cubo base;
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

class _excavadora: public _triangulos3D
{
public:
       _excavadora();
       
void  draw(_modo modo, float r, float g, float b, float grosor);
void  seleccion(); // método para selección

float giro_cabina;
float giro_primer_brazo;
float giro_segundo_brazo;
float giro_pala;

float giro_primer_brazo_max;
float giro_primer_brazo_min;
float giro_segundo_brazo_max;
float giro_segundo_brazo_min;
float giro_pala_max;
float giro_pala_min;

float tamanio_pala;

// atributos para la selección

_vertex3f color_pick;
vector<_vertex3i> color_select;
vector<int> activo;
int piezas;
int grosor_select; 

protected:
_pala pala;
_brazo brazo;
_cabina cabina;
_sustentacion sustentacion;
};


// DINOSAURIO

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// caparazon
//************************************************************************

class _caparazon: public _triangulos3D
{
public:
      _caparazon(float rad=0.5, float ancho=0.6, int num=12);

	float radio;
      float an;
      float al;
      float fo;
};

//************************************************************************
// pinchos
//************************************************************************

class _pincho: public _triangulos3D
{
public:
       _pincho();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_piramide piramide;
};

//************************************************************************
// cuerpo
//************************************************************************

class _cuerpo: public _triangulos3D
{
public:
       _cuerpo();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo base;
_caparazon caparazon;
_pincho pincho;
};

//************************************************************************
// patas
//************************************************************************

class _patas: public _triangulos3D
{
public:
      _patas();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho_sup;
float alto_sup;
float fondo_sup;
float ancho_inf;
float alto_inf;
float fondo_inf;
float ancho_pez;
float alto_pez;
float fondo_pez;

protected:
_cubo superior;
_cubo inferior;
_cubo pezunia;
};

//************************************************************************
// cuello
//************************************************************************

class _cuello: public _triangulos3D
{
public:
      _cuello();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cilindro cuello;
};

//************************************************************************
// cabeza
//************************************************************************

class _cabeza: public _triangulos3D
{
public:
      _cabeza();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo craneo;
_esfera ojo;
_esfera pupila;
_pincho pincho;
_cubo boca_lado;
_cubo boca_centro;


};

//************************************************************************
// tail
//************************************************************************

class _tail: public _triangulos3D
{
public:
      _tail();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cono tail;
_cilindro mazo;
};

//************************************************************************
// dinosaurio (montaje del objeto final)
//************************************************************************

class _dinosaurio: public _triangulos3D
{
public:
       _dinosaurio();
       
void  draw(_modo modo, float r, float g, float b, float grosor);
void  seleccion(); // método para selección

float giro_cola_vertical;
float giro_cola_vertical_max;
float giro_cola_vertical_min;

float giro_cola_horizontal;
float giro_cola_horizontal_min;
float giro_cola_horizontal_max;

float giro_cuello_vertical;
float giro_cuello_vertical_max;
float giro_cuello_vertical_min;

float giro_cuello_horizontal;
float giro_cuello_horizontal_max;
float giro_cuello_horizontal_min;

float giro_cabeza;
float giro_cabeza_min;
float giro_cabeza_max;

float giro_pata1;
float giro_pata_max1;
float giro_pata_min1;

float giro_pata2;
float giro_pata_max2;
float giro_pata_min2;

// atributos para la selección

_vertex3f color_pick;
vector<_vertex3i> color_select;
vector<int> activo;
int piezas;
int grosor_select; 

protected:
_cuerpo cuerpo;
_cuello cuello;
_cabeza cabeza;
_patas pata;
_tail cola;
};

