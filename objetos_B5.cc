//**************************************************************************
// Proyecto final: Alejandro 
//**************************************************************************

#include "objetos_B5.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
  int i;
  glPointSize(grosor);
  glColor3f(r,g,b);
  glBegin(GL_POINTS);
  for (i=0;i<vertices.size();i++){
    glVertex3fv((GLfloat *) &vertices[i]);
    }
  glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D() 
{
	ambiente = _vertex4f(0.621,0,0,1.0);  // ambiental = difuso (R,G,B)
	difuso =  _vertex4f(0.621,0,0,1.0);
	especular = _vertex4f(1.0,1.0,1.0,1.0);       // (R,G,B)
	brillo = 10;
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b) // modificado 
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();

}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores() // modificado 
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
			glColor3f(colores_caras[i].r,colores_caras[i].g,colores_caras[i].b);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo seleccion
//*************************************************************************

void _triangulos3D::draw_seleccion(int r, int g, int b)
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3ub(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con iluminación blanca 
//*************************************************************************

void _triangulos3D::draw_solido_plano( )
{
	int i;
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &ambiente);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &difuso);
	glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) &especular);
	glMaterialfv(GL_FRONT, GL_SHININESS, (GLfloat *) &brillo);
	glEnable(GL_NORMALIZE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glNormal3f(normales_caras[i].x,normales_caras[i].y,normales_caras[i].z);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
	glDisable(GL_LIGHTING);
}


//*************************************************************************
// dibujar en modo sólido con el suavizado de Gouraud
//*************************************************************************

void _triangulos3D::draw_solido_suave( )
{
	int i;
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &ambiente);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &difuso);
	glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) &especular);
	glMaterialfv(GL_FRONT, GL_SHININESS, (GLfloat *) &brillo);
	glEnable(GL_NORMALIZE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glNormal3f(normales_vertices[caras[i]._0].x,normales_vertices[caras[i]._0].y,normales_vertices[caras[i]._0].z);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glNormal3f(normales_vertices[caras[i]._1].x,normales_vertices[caras[i]._1].y,normales_vertices[caras[i]._1].z);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glNormal3f(normales_vertices[caras[i]._2].x,normales_vertices[caras[i]._2].y,normales_vertices[caras[i]._2].z);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
	glDisable(GL_LIGHTING);
}




//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r, g, b, grosor);break;
	case EDGES:draw_aristas(r, g, b, grosor);break;
	case SOLID:draw_solido(r, g, b);break;
	case SOLID_COLORS:draw_solido_colores();break;
	case SOLID_FLAT:draw_solido_plano();break;
	case SOLID_SMOOTH:draw_solido_suave();break;
	case SELECT:draw_seleccion(r, g, b);break;
	}
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random()
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
srand (time(NULL));
for (i=0;i<n_c;i++)  
  {colores_caras[i].r=rand()%1000/1000.0;
   colores_caras[i].g=rand()%1000/1000.0;
   colores_caras[i].b=rand()%1000/1000.0;
  }
}

//*************************************************************************

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i, n_c;
n_c=caras.size();
colores_caras.resize(n_c);
for (i=0;i<n_c;i++)  
  {if (i%2==0) 
     {colores_caras[i].r=r1;
      colores_caras[i].g=g1;
      colores_caras[i].b=b1;
     }
   else 
     {colores_caras[i].r=r2;
      colores_caras[i].g=g2;
      colores_caras[i].b=b2;
     } 
  }
}

//*************************************************************************
// Colores Lambert
//*************************************************************************

void _triangulos3D::colors_lambert_c (float l_x, float l_y, float l_z, float r, float g, float b){
	int i, n_c;
	n_c=caras.size();
	colores_caras.resize(n_c);	
	_vertex3f aux_luz, luz;
	float modulo, p_escalar;

	aux_luz.x=l_x;
	aux_luz.y=l_y;
	aux_luz.z=l_z;

	for (i=0; i<n_c;i++){

		luz=aux_luz-vertices[caras[i]._0];
		modulo = sqrt(luz.x*luz.x+luz.y*luz.y+luz.z*luz.z);
		luz.x=luz.x/modulo;
		luz.y=luz.y/modulo;
		luz.z=luz.z/modulo;

		p_escalar = luz.x * normales_caras[i].x+luz.y * normales_caras[i].y+luz.z * normales_caras[i].z;

		if (p_escalar < 0.0)
			p_escalar = 0.0;

     	colores_caras[i].r=r*p_escalar;
      	colores_caras[i].g=g*p_escalar;
      	colores_caras[i].b=b*p_escalar;

   
	}
}

//*************************************************************************
// calcular normales
//*************************************************************************

void _triangulos3D::calcular_normales_caras() {
	int i, n_c;
	n_c=caras.size();
	normales_caras.resize(n_c);
	_vertex3f vector_a, vector_b, aux;
	float modulo;

	for (i=0;i<n_c;i++){
		vector_a=vertices[caras[i]._1]-vertices[caras[i]._0];  // vector A = punto P1 - punto P0
		vector_b=vertices[caras[i]._2]-vertices[caras[i]._0];  // vector B = punto P2 - punto P0

		// Producto vectorial de AxB
		aux.x =vector_a.y*vector_b.z-vector_a.z*vector_b.y;    // i(AyBz - AzBy)
		//aux.y =vector_a.z*vector_b.x-vector_a.x*vector_b.z;
		aux.y =vector_a.x*vector_b.z-vector_a.z*vector_b.x;   // j(AxBz - AzBx)
		aux.z =vector_a.x*vector_b.y-vector_a.y*vector_b.x;   // k(AxBy - AyBx)

		modulo = sqrt(aux.x*aux.x+aux.y*aux.y+aux.z*aux.z);    // sqrt(x^2 + y^2 + z^2)

		normales_caras[i].x=aux.x/modulo;
		normales_caras[i].y=aux.y/modulo;   // Normalización, aux / |aux|
		normales_caras[i].z=aux.z/modulo;
	}
}

//*************************************************************************
// calcular normales vértices
//*************************************************************************

void _triangulos3D::calcular_normales_vertices(int tipo) {     // si tipo==0, objeto cualquiera, si tipo==1, esfera
	int n_v, n_c;
	n_v=vertices.size();
	n_c=caras.size();
	normales_vertices.resize(n_v);
	_vertex3f aux;
	float modulo;

	if (tipo == 0) {
		for (int i=0; i<n_v;i++){  // para cada vértice 
			aux.x=0;
			aux.y=0;
			aux.z=0;
			for (int j=0; j<n_c; j++){
				if (caras[j]._0 == i || caras[j]._1 == i || caras[j]._2 == i){ // las caras que tienen en común a dicho vértice
					aux.x += normales_caras[j].x;
					aux.y += normales_caras[j].y;   // suma de los vectores normales normalizados
					aux.z += normales_caras[j].z;

				}
			}
			modulo = sqrt(aux.x*aux.x+aux.y*aux.y+aux.z*aux.z); // norma de la suma

			normales_vertices[i].x=aux.x/modulo;
			normales_vertices[i].y=aux.y/modulo;   
			normales_vertices[i].z=aux.z/modulo;
		}
	}
	else {     // ES UNA ESFERA

		for (int i=0; i<n_v;i++){
			// la normal al vértice será el vector que vaya desde el centro hasta el punto
			normales_vertices[i].x = vertices[i].x;   // componente i del vector será x del vértice
			normales_vertices[i].y = vertices[i].y;   // componente j del vector será y del vértice
			normales_vertices[i].z = vertices[i].z;   // componente k del vector será z del vértice 

			modulo = sqrt (normales_vertices[i].x *normales_vertices[i].x +normales_vertices[i].y *normales_vertices[i].y + normales_vertices[i].z *normales_vertices[i].z );

			normales_vertices[i].x = normales_vertices[i].x / modulo;
			normales_vertices[i].y = normales_vertices[i].y / modulo;   // normalización 
			normales_vertices[i].z = normales_vertices[i].z / modulo;
		}

	}


}


//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)   // modificado
{
  // vertices
	//float dim = tam/2; // nuestro centro del cubo es el origen de coordenadas

	//vertices
	vertices.resize(8);
	vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
	vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
	vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
	vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
	vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
	vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

	// triangulos
	caras.resize(12);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
	caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
	caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
	caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
	caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
	caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
	caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
	caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
	caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
	caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
	caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
	caras[11]._0=1;caras[11]._1=5;caras[11]._2=4; 

	// normales a cara

	calcular_normales_caras();
	calcular_normales_vertices(0);

	//colores de las caras
	colors_random();

}




//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

	//vertices 
	vertices.resize(5); 
	vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
	vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
	vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

	caras.resize(6);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
	caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
	caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
	caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
	caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

	// normales a cara

	calcular_normales_caras();
	calcular_normales_vertices(0);

	colors_random();
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices

 
}



void _objeto_ply::parametros(char *archivo)
{

	int n_ver,n_car;

	vector<float> ver_ply ;  // vectores en los que se guardan vétices y caras del PLY
	vector<int>   car_ply ;
	
	_file_ply::read(archivo, ver_ply, car_ply );

	n_ver=ver_ply.size()/3;
	n_car=car_ply.size()/3;

	printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

	vertices.resize(n_ver);
	caras.resize(n_car);

	for (int i=0; i<n_ver; i++){
		vertices[i].x=ver_ply[3*i];
		vertices[i].y=ver_ply[3*i+1];
		vertices[i].z=ver_ply[3*i+2];
	}

	for (int i=0; i<n_car; i++){
		caras[i].x=car_ply[3*i];
		caras[i].y=car_ply[3*i+1];
		caras[i].z=car_ply[3*i+2];
	}

	// normales a caras

	calcular_normales_caras();

	// normales a vértices

	calcular_normales_vertices(0);

	// colores

	colors_lambert_c(0,10,40,1.0,0.8,0);


	// PARTE para COLORES 

	//colores_caras.resize(n_car);
/*
	for (int i=0; i<n_car; i++){
		colores_caras[i].r=rand()%1000/1000.0; // añadido para colorear en modo solido colores
		colores_caras[i].g=rand()%1000/1000.0;
		colores_caras[i].b=rand()%1000/1000.0;
	}
*/

/*
	for (int i=0; i<n_car; i++){
		if (vertices[caras[i]._0].y>0 && vertices[caras[i]._0].x<0) {
			colores_caras[i].r=rand()%1000/1000.0; // añadido para colorear en modo solido colores
			colores_caras[i].g=0;
			colores_caras[i].b=0;
		}
		else if (vertices[caras[i]._0].y>0 && vertices[caras[i]._0].x>0) {
			colores_caras[i].r=0; // añadido para colorear en modo solido colores
			colores_caras[i].g=rand()%1000/1000.0;
			colores_caras[i].b=0;
		}	
		else if ((vertices[caras[i]._0].y<0 && vertices[caras[i]._0].x>0)) {
			colores_caras[i].r=0; // añadido para colorear en modo solido colores
			colores_caras[i].g=rand()%1000/1000.0;
			colores_caras[i].b=rand()%1000/1000.0;
		}
		else if ((vertices[caras[i]._0].y<0 && vertices[caras[i]._0].x<0)) {
			colores_caras[i].r=rand()%1000/1000.0; // añadido para colorear en modo solido colores
			colores_caras[i].g=rand()%1000/1000.0;;
			colores_caras[i].b=0;	
		}
		else {
			colores_caras[i].r=rand()%1000/1000.0; // añadido para colorear en modo solido colores
			colores_caras[i].g=0;
			colores_caras[i].b=0;			
		}

	}

*/



}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su) // num determina número de lados longitudinales (en ejemplo es 6)
{
	int i,j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;              // para guardar número de vértices del perfil 
	float radio;         // para esfera

	// tratamiento de los vértices

	radio=sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);    // cáculo del radio 

	num_aux=perfil.size();  // en nuestro ejemplo de clase es 3

	if (tipo==1) // (cono), el vértice de arriba será fijo
		num_aux=num_aux-1;

	vertices.resize(num_aux*num+2);  // Se guardarán numero_vertices_perfil × numero_lados_longitudinales + 2 vértices para tapas
	for (j=0;j<num;j++)    // numero_lados_long sucesivas transformaciones de rotación con respecto al eje Y
	{for (i=0;i<num_aux;i++)   // para cada uno de los vértices del perfil 
		{
		vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
						perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
		vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+  // utilizamos la matriz R y,0 de las diapositiva 54 [(x,y,z) * matriz]
						perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
		vertice_aux.y=perfil[i].y;
		vertices[i+j*num_aux]=vertice_aux;  // vamos añadiendo el vértice a nuestra estructura 
		}
	}

	// tratamiento de las caras 

	if (tapa_in==0 && tapa_su==0) 				// ninguna tapa
		caras.resize(2*(num_aux-1)*num);
	else if ((tapa_in==0 && tapa_su==1) || (tapa_in==1 && tapa_su==0))  // solo una tapa (inf o sup)
		caras.resize(2*(num_aux-1)*num+num);	
	else
		caras.resize(2*(num_aux-1)*num+2*num);  // cálculo del número de caras, debemos añadir 2*numero de lados longitudinales (para ambas tapas)

	int c=0;
	for (j=0;j<num;j++){					// para cada uno de los lados longitudinales 
		for (int i=0; i<num_aux-1;i++){    // para cada vértice 
											// recordar que caras guarda los índices de los vértices
			caras[c]._0 = i+j*num_aux;
			caras[c]._1 = i+((j+1)%num)*num_aux; 
			caras[c]._2 = i+j*num_aux+1; 
			c+=1;
			caras[c]._0 = i+((j+1)%num)*num_aux; 
			caras[c]._1 = i+((j+1)%num)*num_aux+1;  
			caras[c]._2 = i+j*num_aux+1; 
			c+=1;
		}
	}

	
	if (tapa_in) {

		// tapa inferior
		vertices[num_aux*num].x = 0.0; 
		if (tipo == 2) // si es una esfera
			vertices[num_aux*num].y = -radio;
		else
			vertices[num_aux*num].y = perfil[0].y; // proyección sobre el eje de rotación (Y) del primer punto del perfil 
		vertices[num_aux*num].z = 0.0; 

		for (j=0;j<num;j++){					// para cada lado longitudinal
				caras[c]._0 = j*num_aux;           // primer punto de primer perfil 
				caras[c]._1 = ((j+1)%num)*num_aux; // primer punto del perfil siguiente al primero
				caras[c]._2 = num_aux*num; //      // punto inferior que hemos añadido en vértices
				c+=1;
		}

	}


	if (tapa_su){

		// tapa superior
		// proyección sobre el eje de rotación (Y) del último punto del perfil
		vertices[num_aux*num+1].x = 0.0;
		if (tipo==0)											// para caso habitual
			vertices[num_aux*num+1].y = perfil[num_aux-1].y;  
		else if (tipo==1)											// si es un cono 
			vertices[num_aux*num+1].y = perfil[1].y;       // será la punta del cono
		else if (tipo=2)											// si es una esfera
			vertices[num_aux*num+1].y = radio;			
		vertices[num_aux*num+1].z = 0.0; 

		for (j=0;j<num;j++){
				caras[c]._0 = j*num_aux+num_aux-1;			// último punto del primer perfil 
				caras[c]._1 = ((j+1)%num)*num_aux+num_aux-1; // último punto del perfil siguiente al primero
				caras[c]._2 = num_aux*num+1; 				// punto superior que hemos añadido en vértices
				c+=1;
		}

	}


	// pruebas
	/*
	for (i=0; i<vertices.size(); i++){
		cout << "El vértice " << i << " formado por:\n";
		cout << "x= " << vertices[i].x << "\n";
		cout << "y= " << vertices[i].y << "\n";
		cout << "z= " << vertices[i].z << "\n";
		cout << "\n\n";

	}
	*/


	// PARTE para COLORES 

	calcular_normales_caras();
	calcular_normales_vertices(0);

	colors_random();

}

_cilindro::_cilindro(float radio, float altura, int num){
	vector<_vertex3f> perfil;
	_vertex3f aux;

	aux.x=radio; aux.y=-altura/2.0; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=radio; aux.y=altura/2.0; aux.z=0.0;
	perfil.push_back(aux);
	parametros(perfil,num,0,1,1); //tipo, tapa_in, tapa_sup
	calcular_normales_caras();
	calcular_normales_vertices(0);
}

_cono::_cono(float radio, float altura, int num){
	vector<_vertex3f> perfil;
	_vertex3f aux;

	aux.x=radio; aux.y=0; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0; aux.y=altura; aux.z=0.0;
	perfil.push_back(aux);
	parametros(perfil,num,1,1,1);
	calcular_normales_caras();
	calcular_normales_vertices(0);
}

_esfera::_esfera(float radio, int num1, int num2){
	vector<_vertex3f> perfil;
	_vertex3f aux;
	int i;
	for (i=1;i<num1;i++){
		aux.x=radio*cos(M_PI*i/(num1*1.0)-M_PI/2.0);
		aux.y=radio*sin(M_PI*i/(num1*1.0)-M_PI/2.0);
		aux.z=0.0;
		perfil.push_back(aux);
	}
	parametros(perfil, num2, 2,1,1);
	calcular_normales_caras();
	calcular_normales_vertices(1);
}



//************************************************************************
// objeto por rotación a través de archivo PLY
//************************************************************************

_rotacion_ply::_rotacion_ply()
{

}

void _rotacion_ply::parametros_rotacion_ply(char *fichero, int num)
{
	int i, num_ver;
	vector<float> vertices_ply;
	vector<int> caras_ply;
	vector<_vertex3f> perfil;
	_vertex3f aux;

	_file_ply::read(fichero, vertices_ply, caras_ply);

	num_ver = vertices_ply.size()/3;

	vertices.resize(num_ver);

	// tratamiento de los vértices

	for (i=0; i<num_ver; i++){
		aux.x=vertices_ply[3*i];
		aux.y=vertices_ply[3*i+1];
		aux.z=vertices_ply[3*i+2];
		perfil.push_back(aux);
	}
	parametros(perfil,num,0,1,0);  // he creado una copa, con lo cual no le pongo tapa superior 
	calcular_normales_caras();
	calcular_normales_vertices(0);
}


//************************************************************************
// objeto por extrusión
//************************************************************************


_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
int i;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;


// tratamiento de los vértice

num_aux=poligono.size();
int iter = num_aux*2; // añadido
vertices.resize(num_aux*2);
for (i=0;i<num_aux;i++)
    {
      vertices[2*i]=poligono[i];
      vertices[2*i+1].x=poligono[i].x+x;
      vertices[2*i+1].y=poligono[i].y+y;
      vertices[2*i+1].z=poligono[i].z+z;
    }
    
// tratamiento de las caras 

caras.resize(num_aux*2);
int c=0;
for (i=0;i<num_aux;i++)         
  {
   caras[c]._0=i*2;
   caras[c]._1=(i*2+2)%(num_aux*2);
   caras[c]._2=i*2+1;    
   c=c+1;
   caras[c]._0=(i*2+2)%(num_aux*2);
   caras[c]._1=(i*2+2)%(num_aux*2)+1;
   caras[c]._2=i*2+1;    
   c=c+1;    
      
   }


  colores_caras.resize(iter);

  for (int i=0; i<iter; i++){
    colores_caras[i].r=rand()%1000/1000.0; // añadido para colorear en modo solido colores
    colores_caras[i].g=rand()%1000/1000.0;
    colores_caras[i].b=rand()%1000/1000.0;
  }   

  	calcular_normales_caras();
	calcular_normales_vertices(0);
      
}



//************************************************************************
// práctica 3, objeto jerárquico articulado
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

_pala::_pala(float radio, float ancho, int num)
{
vector<_vertex3f> perfil;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int i, j;

vertice_aux.x=radio; vertice_aux.y=0; vertice_aux.z=-ancho/2.0;
perfil.push_back(vertice_aux);
vertice_aux.z=ancho/2.0;
perfil.push_back(vertice_aux);

// tratamiento de los vértices

for (j=0;j<=num;j++)
  {for (i=0;i<2;i++)	
     {
      vertice_aux.x=perfil[i].x*cos(M_PI*j/(1.0*num))-
                    perfil[i].y*sin(M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].x*sin(M_PI*j/(1.0*num))+
                    perfil[i].y*cos(M_PI*j/(1.0*num));
      vertice_aux.z=perfil[i].z;
      vertices.push_back(vertice_aux);
     }
  }
  
// tratamiento de las caras 

for (j=0;j<num;j++)
   {cara_aux._0=j*2;
    cara_aux._1=(j+1)*2;
    cara_aux._2=(j+1)*2+1;
    caras.push_back(cara_aux);
    
    cara_aux._0=j*2;
    cara_aux._1=(j+1)*2+1;
    cara_aux._2=j*2+1;
    caras.push_back(cara_aux);
   }
   
// tapa inferior
vertice_aux.x=0;
vertice_aux.y=0;
vertice_aux.z=-ancho/2.0;
vertices.push_back(vertice_aux); 

for (j=0;j<num;j++)
   {cara_aux._0=j*2;
    cara_aux._1=(j+1)*2;
    cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);
   }
  
// tapa superior
vertice_aux.x=0;
vertice_aux.y=0;
vertice_aux.z=ancho/2.0;
vertices.push_back(vertice_aux); 

for (j=0;j<num;j++)
   {cara_aux._0=j*2+1;
    cara_aux._1=(j+1)*2+1;
    cara_aux._2=vertices.size()-1;
    caras.push_back(cara_aux);
   }
  
colors_chess(1.0,1.0,0.0,0.0,0.0,1.0);
}

//************************************************************************
// brazo
//************************************************************************

_brazo::_brazo()
{
ancho=0.6;
alto=0.1;
fondo=0.1;
colors_chess(1.0,1.0,0.0,0.0,0.0,1.0);
};

void _brazo::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(ancho, alto, fondo);
glTranslatef(0.5,0,0);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();
};

//************************************************************************
// cabina
//************************************************************************

_cabina::_cabina()
{
ancho=0.4;
alto=0.6;
fondo=0.4;
cubo.colors_chess(1.0,1.0,0.0,0.0,0.0,1.0);
};

void _cabina::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glScalef(ancho, alto, fondo);
cubo.draw(modo, r, g, b, grosor);
glPopMatrix();
};

//************************************************************************
// sustentación
//************************************************************************

_sustentacion::_sustentacion()
{
ancho=1.2;
alto=0.3;
fondo=0.8;
radio=0.15;
base.colors_chess(1.0,1.0,0.0,0.0,0.0,1.0);
};

void _sustentacion::draw(_modo modo, float r, float g, float b, float grosor)
{
glPushMatrix();
glTranslatef(2*ancho/6,-alto/2.0,0);
glRotatef(90,1,0,0);
glScalef(radio, fondo/2.2, radio);
rueda.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-2*ancho/6,-alto/2.0,0);
glRotatef(90,1,0,0);
glScalef(radio, fondo/2.2, radio);
rueda.draw(modo, r, g, b, grosor);
glPopMatrix();

glPushMatrix();
glScalef(ancho, alto, fondo);
base.draw(modo, r, g, b, grosor);
glPopMatrix();
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

_excavadora::_excavadora()
{
giro_cabina = 0.0;
giro_primer_brazo = 0.0;
giro_primer_brazo_max = 0;
giro_primer_brazo_min = -90;
giro_segundo_brazo = 0.0;
giro_segundo_brazo_max = 30;
giro_segundo_brazo_min = 0;
giro_pala = 0.0;
giro_pala_max = 50.0;
giro_pala_min = -90.0;

tamanio_pala=0.15;


int color=80;
piezas=5;
grosor_select=2;
color_pick=_vertex3f(1.0,0.0,0.0); 
color_select.resize(piezas);
activo.resize(piezas);

for (int i=0;i<piezas;i++)
  {activo[i]=0;
   color_select[i].r=color_select[i].g=color_select[i].b=color;
   color+=20;
  }
};

//************************************************************************

void _excavadora::draw(_modo modo, float r, float g, float b, float grosor)
{
float r_p,g_p,b_p;
int tam=2;

r_p=color_pick.r;
g_p=color_pick.g;
b_p=color_pick.b;

glPushMatrix();

if (activo[0]==1) sustentacion.draw(EDGES, r_p, g_p, b_p, grosor_select);
else sustentacion.draw(modo, r, g, b, grosor);

glTranslatef(0,(cabina.alto+sustentacion.alto)/2.0,0);
glRotatef(giro_cabina,0,1,0);
if (activo[1]==1) cabina.draw(EDGES, r_p, g_p, b_p, grosor_select);
else cabina.draw(modo, r, g, b, grosor);

glTranslatef(cabina.ancho/2.0,0,0);
glRotatef(giro_segundo_brazo,0,0,1);
if (activo[2]==1) brazo.draw(EDGES, r_p, g_p, b_p, grosor_select);
else brazo.draw(modo, r, g, b, grosor);

glTranslatef(brazo.ancho,0,0);
glRotatef(giro_primer_brazo,0,0,1);
if (activo[3]==1) brazo.draw(EDGES, r_p, g_p, b_p, grosor_select);
else brazo.draw(modo, r, g, b, grosor);

glTranslatef(brazo.ancho,0,0);
glRotatef(giro_pala,0,0,1);
glTranslatef(tamanio_pala,0,0);
glScalef(tamanio_pala, tamanio_pala, tamanio_pala);
if (activo[4]==1) pala.draw(EDGES, r_p, g_p, b_p, grosor_select);
else pala.draw(modo, r, g, b, grosor);

glPopMatrix();
};

//************************************************************************

void _excavadora::seleccion()
{
_vertex3i color;

glPushMatrix();
color=color_select[0];
sustentacion.draw(SELECT, color.r, color.g, color.b, 1);

glTranslatef(0,(cabina.alto+sustentacion.alto)/2.0,0);
glRotatef(giro_cabina,0,1,0);
color=color_select[1];
cabina.draw(SELECT, color.r, color.g, color.b, 1);

glTranslatef(cabina.ancho/2.0,0,0);
glRotatef(giro_segundo_brazo,0,0,1);
color=color_select[2];
brazo.draw(SELECT, color.r, color.g, color.b, 1);

glTranslatef(brazo.ancho,0,0);
glRotatef(giro_primer_brazo,0,0,1);
color=color_select[3];
brazo.draw(SELECT, color.r, color.g, color.b, 1);

glTranslatef(brazo.ancho,0,0);
glRotatef(giro_pala,0,0,1);
glTranslatef(tamanio_pala,0,0);
glScalef(tamanio_pala, tamanio_pala, tamanio_pala);
color=color_select[4];
pala.draw(SELECT, color.r, color.g, color.b, 1);

glPopMatrix();
};



// DINOSAURIO



//************************************************************************
// caparazon
//************************************************************************

_caparazon::_caparazon(float rad, float ancho, int num)
{
	vector<_vertex3f> perfil;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int i, j;

	radio = rad;

	vertice_aux.x=radio; vertice_aux.y=0; vertice_aux.z=-ancho/2.0;
	perfil.push_back(vertice_aux);
	vertice_aux.z=ancho/2.0;
	perfil.push_back(vertice_aux);

	// tratamiento de los vértices

	for (j=0;j<=num;j++)
	{for (i=0;i<2;i++)	
		{
		vertice_aux.x=perfil[i].x*cos(M_PI*j/(1.0*num))-
						perfil[i].y*sin(M_PI*j/(1.0*num));
		vertice_aux.y=perfil[i].x*sin(M_PI*j/(1.0*num))+
						perfil[i].y*cos(M_PI*j/(1.0*num));
		vertice_aux.z=perfil[i].z;
		vertices.push_back(vertice_aux);
		}
	}
	
	// tratamiento de las caras 

	for (j=0;j<num;j++)
	{cara_aux._0=j*2;
		cara_aux._1=(j+1)*2;
		cara_aux._2=(j+1)*2+1;
		caras.push_back(cara_aux);
		
		cara_aux._0=j*2;
		cara_aux._1=(j+1)*2+1;
		cara_aux._2=j*2+1;
		caras.push_back(cara_aux);
	}

	// tapa inferior
	vertice_aux.x=0;
	vertice_aux.y=0;
	vertice_aux.z=-ancho/2.0;
	vertices.push_back(vertice_aux); 

	for (j=0;j<num;j++)
	{cara_aux._0=j*2;
		cara_aux._1=(j+1)*2;
		cara_aux._2=vertices.size()-1;
		caras.push_back(cara_aux);
	}


	// tapa superior
	vertice_aux.x=0;
	vertice_aux.y=0;
	vertice_aux.z=ancho/2.0;
	vertices.push_back(vertice_aux); 

	for (j=0;j<num;j++)
	{cara_aux._0=j*2+1;
		cara_aux._1=(j+1)*2+1;
		cara_aux._2=vertices.size()-1;
		caras.push_back(cara_aux);
	}

	// colores

	int n_c;
	n_c=caras.size();
	colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){
		colores_caras[i].r=0.6;
		colores_caras[i].g=0.5;
		colores_caras[i].b=0.1;
	}

	an = 1.0;
	al = 0.25;
	fo = 1.0;

	calcular_normales_caras();
	calcular_normales_vertices(0);

}

//************************************************************************
// pinchos
//************************************************************************

_pincho::_pincho()
{
	ancho=0.1;
	alto=0.1;
	fondo=0.1;
	// colores
	int n_c;
	n_c=piramide.caras.size();
	piramide.colores_caras.resize(n_c);
	srand (time(NULL));
	for (int i=0;i<n_c;i++){
		piramide.colores_caras[i].r=0.6;
		piramide.colores_caras[i].g=0.2;
		piramide.colores_caras[i].b=0.2;
	} 


	/* DEFINICIÓN DE MATERIALES */

	piramide.ambiente = _vertex4f(0.1745,0.01175,0.01175,0.55);  
	piramide.difuso = _vertex4f(0.61424,0.04136,0.04136,0.55);  
	piramide.especular = _vertex4f(0.727811,0.626959,0.626959,0.55);       // material rubí
	piramide.brillo = 76.8;
};

void _pincho::draw(_modo modo, float r, float g, float b, float grosor)
{
	glPushMatrix();
	glScalef(ancho, alto, fondo);
	piramide.draw(modo, r, g, b, grosor);
	glPopMatrix();
};

//************************************************************************
// cuerpo
//************************************************************************

_cuerpo::_cuerpo()
{
	ancho=1.0;
	alto=0.1;
	fondo=0.6;
	// colores
	int n_c;
	n_c=base.caras.size();
	base.colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){
		base.colores_caras[i].r=0.7;
		base.colores_caras[i].g=0.5;
		base.colores_caras[i].b=0.1;
	}
};

void _cuerpo::draw(_modo modo, float r, float g, float b, float grosor)
{
	glPushMatrix();
	glScalef(ancho,alto,fondo);
	base.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,alto/2.0,0);
	glScalef(caparazon.an,caparazon.al+0.3,caparazon.fo);
	caparazon.draw(modo, r, g, b, grosor);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,alto/2+0.27,0);              
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ancho/4,alto/2+0.23,0);
	glRotatef(-20,0,0,1);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ancho/2.2,1.5*alto,0);
	glRotatef(-50,0,0,1);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-ancho/4,alto/2+0.23,0);  
	glRotatef(20,0,0,1);            
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-ancho/2.2,1.5*alto,0);
	glRotatef(50,0,0,1);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,alto/2+0.27,fondo/2-0.12);              
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ancho/4,alto/2+0.23,fondo/2-0.12);
	glRotatef(-20,0,0,1);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ancho/2.2,1.5*alto,fondo/2-0.12);
	glRotatef(-50,0,0,1);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-ancho/4,alto/2+0.23,fondo/2-0.12);  
	glRotatef(20,0,0,1);            
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-ancho/2.2,1.5*alto,fondo/2-0.12);
	glRotatef(50,0,0,1);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,alto/2+0.27,-fondo/2+0.12);              
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ancho/4,alto/2+0.23,-fondo/2+0.12);
	glRotatef(-20,0,0,1);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ancho/2.2,1.5*alto,-fondo/2+0.12);
	glRotatef(-50,0,0,1);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-ancho/4,alto/2+0.23,-fondo/2+0.12);  
	glRotatef(20,0,0,1);            
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-ancho/2.2,1.5*alto,-fondo/2+0.12);
	glRotatef(50,0,0,1);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

};

//************************************************************************
// patas
//************************************************************************

_patas::_patas()
{
	ancho_sup=0.1;
	alto_sup=0.1;
	fondo_sup=0.1;
	ancho_inf=0.1;
	alto_inf=0.1;
	fondo_inf=0.1;
	ancho_pez=0.15;
	alto_pez=0.03;
	fondo_pez=0.1;

	int n_c;
	n_c=superior.caras.size();
	superior.colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){
		superior.colores_caras[i].r=0.7;
		superior.colores_caras[i].g=0.5;
		superior.colores_caras[i].b=0.1;

		inferior.colores_caras[i].r=0.6;
		inferior.colores_caras[i].g=0.5;
		inferior.colores_caras[i].b=0.1;
		
		pezunia.colores_caras[i].r=0.54;
		pezunia.colores_caras[i].g=0.17;
		pezunia.colores_caras[i].b=0.02;

	}

	/* DEFINICIÓN DE MATERIALES */


	inferior.ambiente = _vertex4f(0.1,0.18725,0.1745,0.8);  
	inferior.difuso = _vertex4f(0.396,0.74151,0.69102,0.8);  
	inferior.especular = _vertex4f(0.297254,0.30829,0.306678,0.8);       // material turquesa
	inferior.brillo = 12.8;

	pezunia.ambiente = _vertex4f(0.1,0.18725,0.1745,0.8); 
	pezunia.difuso = _vertex4f(0.396,0.74151,0.69102,0.8); 
	pezunia.especular = _vertex4f(0.297254,0.30829,0.306678,0.8);       // material turquesa
	pezunia.brillo = 12.8;

};

void _patas::draw(_modo modo, float r, float g, float b, float grosor)
{
	glPushMatrix();
	glScalef(ancho_sup, alto_sup, fondo_sup);
	superior.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,(-alto_inf-alto_sup)/2,0);
	glScalef(ancho_inf, alto_inf, fondo_inf);
	inferior.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ancho_pez/6,-alto_sup/2-alto_inf-alto_pez/2,0);
	glScalef(ancho_pez, alto_pez, fondo_pez);
	pezunia.draw(modo, r, g, b, grosor);
	glPopMatrix();
};

//************************************************************************
// cuello
//************************************************************************

_cuello::_cuello()
{
	ancho=0.1;
	alto=0.05;
	fondo=0.05;
	int n_c;
	n_c=cuello.caras.size();
	cuello.colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){
		cuello.colores_caras[i].r=0.7;
		cuello.colores_caras[i].g=0.5;
		cuello.colores_caras[i].b=0.1;
	}
};

void _cuello::draw(_modo modo, float r, float g, float b, float grosor)
{
	glPushMatrix();
	glScalef(ancho, alto, fondo);
	glRotatef(-90,0,0,1);
	cuello.draw(modo, r, g, b, grosor);
	glPopMatrix();

	/* DEFINICIÓN DE MATERIALES */

	cuello.ambiente = _vertex4f(0.24725,0.1995,0.0745,1.0); 
	cuello.difuso = _vertex4f(0.75164,0.60648,0.22648,1.0); 
	cuello.especular = _vertex4f(0.628281,0.555802,0.366065,1.0);       // material oro
	cuello.brillo = 51.2;
};

//************************************************************************
// cabeza
//************************************************************************

_cabeza::_cabeza()
{
	ancho=0.22;
	alto=0.15;
	fondo=0.15;
	int n_c;
	n_c=craneo.caras.size();
	craneo.colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){
		craneo.colores_caras[i].r=0.7;
		craneo.colores_caras[i].g=0.5;
		craneo.colores_caras[i].b=0.1;
	}

	n_c=ojo.caras.size();
	ojo.colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){
		ojo.colores_caras[i].r=1;
		ojo.colores_caras[i].g=1;
		ojo.colores_caras[i].b=1;
	}

	n_c=pupila.caras.size();
	pupila.colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){
		pupila.colores_caras[i].r=0;
		pupila.colores_caras[i].g=0;
		pupila.colores_caras[i].b=0;
	}

	n_c=pincho.caras.size();
	pincho.colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){
		pincho.colores_caras[i].r=0.5;
		pincho.colores_caras[i].g=0.5;
		pincho.colores_caras[i].b=0;
	}

	n_c=boca_lado.caras.size();
	boca_centro.colores_caras.resize(n_c);
	boca_lado.colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){

		boca_centro.colores_caras[i].r=0;
		boca_centro.colores_caras[i].g=0;
		boca_centro.colores_caras[i].b=0;

		boca_lado.colores_caras[i].r=0;
		boca_lado.colores_caras[i].g=0;
		boca_lado.colores_caras[i].b=0;
	}

	/* DEFINICIÓN DE MATERIALES */

	craneo.ambiente = _vertex4f(0.24725,0.1995,0.0745,1.0); 
	craneo.difuso = _vertex4f(0.75164,0.60648,0.22648,1.0); 
	craneo.especular = _vertex4f(0.628281,0.555802,0.366065,1.0);       // material oro
	craneo.brillo = 51.2;
};

void _cabeza::draw(_modo modo, float r, float g, float b, float grosor)
{
	glPushMatrix();
	glScalef(ancho, alto, fondo);
	craneo.draw(modo, r, g, b, grosor);
	glPopMatrix();


	glPushMatrix();
	glScalef(0.15, 0.1, 0.1);
	glTranslatef(-ancho*2,2*alto,5*fondo);
	glRotatef(-25,0,0,1);
	ojo.draw(modo, r, g, b, grosor);

	glScalef(0.7, 0.4, 0.4);
	glTranslatef(0,0,0.2);
	pupila.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.15, 0.1, 0.1);
	glTranslatef(-ancho*2,2*alto,-5*fondo);
	glRotatef(-25,0,0,1);
	ojo.draw(modo, r, g, b, grosor);

	glScalef(0.7, 0.4, 0.4);
	glTranslatef(0,0,-0.2);
	pupila.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.4, 0.4);
	glTranslatef(-ancho/2+ancho/10,alto+alto/5,fondo-fondo/4);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.4, 0.4);
	glTranslatef(-ancho/2+ancho/10,alto+alto/5,-fondo+fondo/4);
	pincho.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.08, 0.018, 0.005);
	glTranslatef(4*ancho,-10*alto,15);
	boca_lado.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.08, 0.018, 0.005);
	glTranslatef(4*ancho,-10*alto,-15);
	boca_lado.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.005,  0.018, 0.15);
	glTranslatef(22,-10*alto,0);
	boca_centro.draw(modo, r, g, b, grosor);
	glPopMatrix();


};

//************************************************************************
// cola
//************************************************************************

_tail::_tail()
{
	ancho=0.2;
	alto=0.8;
	fondo=0.8;
	int n_c;
	n_c=tail.caras.size();
	tail.colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){
		tail.colores_caras[i].r=0.7;
		tail.colores_caras[i].g=0.5;
		tail.colores_caras[i].b=0.1;
	}

	n_c=mazo.caras.size();
	mazo.colores_caras.resize(n_c);
	for (int i=0;i<n_c;i++){
		mazo.colores_caras[i].r=0.54;
		mazo.colores_caras[i].g=0.17;
		mazo.colores_caras[i].b=0.02;
	}


	/* DEFINICIÓN DE MATERIALES */

	tail.ambiente = _vertex4f(0.24725,0.1995,0.0745,1.0); 
	tail.difuso = _vertex4f(0.75164,0.60648,0.22648,1.0); 
	tail.especular = _vertex4f(0.628281,0.555802,0.366065,1.0);       // material oro
	tail.brillo = 51.2;


	mazo.ambiente = _vertex4f(0.19225,0.19225,0.19225,1.0); 
	mazo.difuso = _vertex4f(0.50754,0.50754,0.50754,1.0); 
	mazo.especular = _vertex4f(0.508273, 0.508273,0.508273,1.0);       // material plata
	mazo.brillo = 51.2;
};

void _tail::draw(_modo modo, float r, float g, float b, float grosor)
{
	glPushMatrix();
	glScalef(ancho, alto, fondo);
	glRotatef(90,0,0,1);
	tail.draw(modo, r, g, b, grosor);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.07, 0.15);
	glRotatef(90,0,0,1);
	glRotatef(90,1,0,0);
	glTranslatef(0,0,-9);
	mazo.draw(modo, r, g, b, grosor);
	glPopMatrix();	
};


//************************************************************************
// dinosaurio (montaje del objeto final)
//************************************************************************

_dinosaurio::_dinosaurio()
{

	giro_cuello_vertical = 0.0;
	giro_cuello_vertical_max = 8;
	giro_cuello_vertical_min = -8;

	giro_cuello_horizontal = 0.0;
	giro_cuello_horizontal_max = 16;
	giro_cuello_horizontal_min = -16;

	giro_cabeza = 0.0;
	giro_cabeza_min = -35;
	giro_cabeza_max = 15;

	giro_cola_vertical = 0.0;
	giro_cola_vertical_max = 10;
	giro_cola_vertical_min = -10;

	giro_cola_horizontal= 0.0;
	giro_cola_horizontal_max = 20;
	giro_cola_horizontal_min = -20;

	giro_pata1 = 0.0;
	giro_pata_max1 = 15;
	giro_pata_min1 = -15;

	giro_pata2 = 0.0;
	giro_pata_max2 = 15;
	giro_pata_min2 = -15;

	int color=80;
	piezas=8;
	grosor_select=2;
	color_pick=_vertex3f(1.0,0.0,0.0); 
	color_select.resize(piezas);
	activo.resize(piezas);

	for (int i=0;i<piezas;i++)
	{activo[i]=0;
	color_select[i].r=color_select[i].g=color_select[i].b=color;
	color+=20;
	}



};



void _dinosaurio::draw(_modo modo, float r, float g, float b, float grosor)
{
	float r_p,g_p,b_p;


	r_p=color_pick.r;
	g_p=color_pick.g;
	b_p=color_pick.b;


	glPushMatrix();


	if (activo[0]==1) cuerpo.draw(EDGES, r_p, g_p, b_p, grosor_select);
	else cuerpo.draw(modo, r, g, b, grosor);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(cuerpo.ancho/2,0,0);
	glRotatef(giro_cuello_horizontal,0,1,0);
	glTranslatef(cuello.ancho-0.02,0,0);
	if (activo[1]==1) cuello.draw(EDGES, r_p, g_p, b_p, grosor_select);
	else cuello.draw(modo, r, g, b, grosor);

	glTranslatef(cuello.ancho,0,0);
	glRotatef(giro_cabeza,0,0,1);
	glTranslatef(cabeza.ancho/2-0.02,0,0);
	if (activo[2]==1) cabeza.draw(EDGES, r_p, g_p, b_p, grosor_select);	
	else cabeza.draw(modo, r, g, b, grosor);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-cuerpo.ancho/2+pata.ancho_sup/2,-cuerpo.alto/2,(cuerpo.fondo-pata.fondo_sup)/2);
	glRotatef(giro_pata1,0,0,1);
	glTranslatef(0,-pata.alto_sup/2+0.02,0);
	if (activo[3]==1) pata.draw(EDGES, r_p, g_p, b_p, grosor_select);
	else pata.draw(modo, r, g, b, grosor);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-cuerpo.ancho/2+pata.ancho_sup/2,-cuerpo.alto/2,-(cuerpo.fondo-pata.fondo_sup)/2);
	glRotatef(giro_pata2,0,0,1);
	glTranslatef(0,-pata.alto_sup/2+0.02,0);
	if (activo[4]==1) pata.draw(EDGES, r_p, g_p, b_p, grosor_select);
	else pata.draw(modo, r, g, b, grosor);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(+cuerpo.ancho/2-pata.ancho_sup/2,-cuerpo.alto/2,-(cuerpo.fondo-pata.fondo_sup)/2);
	glRotatef(giro_pata1,0,0,1);
	glTranslatef(0,-pata.alto_sup/2+0.02,0);
	if (activo[5]==1) pata.draw(EDGES, r_p, g_p, b_p, grosor_select);
	else pata.draw(modo, r, g, b, grosor);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(+cuerpo.ancho/2-pata.ancho_sup/2,-cuerpo.alto/2,(cuerpo.fondo-pata.fondo_sup)/2);
	glRotatef(giro_pata2,0,0,1);
	glTranslatef(0,-pata.alto_sup/2+0.02,0);
	if (activo[6]==1) pata.draw(EDGES, r_p, g_p, b_p, grosor_select);
	else pata.draw(modo, r, g, b, grosor);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-cuerpo.ancho/2+0.05,cola.ancho/4,0);
	glRotatef(giro_cola_vertical,0,0,1);
	glRotatef(giro_cola_horizontal,0,1,0);
	if (activo[7]==1) cola.draw(EDGES, r_p, g_p, b_p, grosor_select);
	else cola.draw(modo, r, g, b, grosor);


	glPopMatrix();
};


//************************************************************************

void _dinosaurio::seleccion()
{
	_vertex3i color;


	glPushMatrix();

	color=color_select[0];
	cuerpo.draw(SELECT, color.r, color.g, color.b, 1);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(cuerpo.ancho/2,0,0);
	glRotatef(giro_cuello_horizontal,0,1,0);
	glTranslatef(cuello.ancho-0.02,0,0);
	color=color_select[1];
	cuello.draw(SELECT, color.r, color.g, color.b, 1);

	glTranslatef(cuello.ancho,0,0);
	glRotatef(giro_cabeza,0,0,1);
	glTranslatef(cabeza.ancho/2-0.02,0,0);
	color=color_select[2];
	cabeza.draw(SELECT, color.r, color.g, color.b, 1);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-cuerpo.ancho/2+pata.ancho_sup/2,-cuerpo.alto/2,(cuerpo.fondo-pata.fondo_sup)/2);
	glRotatef(giro_pata1,0,0,1);
	glTranslatef(0,-pata.alto_sup/2+0.02,0);
	color=color_select[3];
	pata.draw(SELECT, color.r, color.g, color.b, 1);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-cuerpo.ancho/2+pata.ancho_sup/2,-cuerpo.alto/2,-(cuerpo.fondo-pata.fondo_sup)/2);
	glRotatef(giro_pata2,0,0,1);
	glTranslatef(0,-pata.alto_sup/2+0.02,0);
	color=color_select[4];
	pata.draw(SELECT, color.r, color.g, color.b, 1);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(+cuerpo.ancho/2-pata.ancho_sup/2,-cuerpo.alto/2,-(cuerpo.fondo-pata.fondo_sup)/2);
	glRotatef(giro_pata1,0,0,1);
	glTranslatef(0,-pata.alto_sup/2+0.02,0);
	color=color_select[5];
	pata.draw(SELECT, color.r, color.g, color.b, 1);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(+cuerpo.ancho/2-pata.ancho_sup/2,-cuerpo.alto/2,(cuerpo.fondo-pata.fondo_sup)/2);
	glRotatef(giro_pata2,0,0,1);
	glTranslatef(0,-pata.alto_sup/2+0.02,0);
	color=color_select[6];
	pata.draw(SELECT, color.r, color.g, color.b, 1);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-cuerpo.ancho/2+0.05,cola.ancho/4,0);
	glRotatef(giro_cola_vertical,0,0,1);
	glRotatef(giro_cola_horizontal,0,1,0);
	color=color_select[7];
	cola.draw(SELECT, color.r, color.g, color.b, 1);


	glPopMatrix();
};