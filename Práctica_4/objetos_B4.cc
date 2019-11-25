//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"


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
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size());

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{

  b_normales_caras=false;
  b_normales_vertices=false;
  ambiente_difusa=_vertex4f(0.2,0.4,0.9,1.0);
  especular=_vertex4f(0.7,0.7,0.7,1.0);
  brillo=40;
}


//*************************************************************************
// dibujar en modo iluminacion plana
//*************************************************************************
void _triangulos3D::draw_iluminacion_plana(){
  int i;
  GLfloat ambient_component[4]={1,1,1,1};
  if(b_normales_caras==false){
    calcular_normales_caras();
  }
  glShadeModel(GL_FLAT);
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,brillo);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for(int i=0;i<caras.size();i++){
    glNormal3fv((GLfloat *) &normales_caras[i]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }
  glEnd();
  glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar en modo iluminacion plana
//*************************************************************************
void _triangulos3D::draw_iluminacion_suave(){
  int i;
  GLfloat ambient_component[4]={1,1,1,1};
  if(b_normales_vertices==false){
    calcular_normales_vertices();
  }
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,brillo);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for(int i=0;i<caras.size();i++){
    glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
      glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
      glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
      glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
      glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
      glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }
  glEnd();
  glDisable(GL_LIGHTING);

}
void _triangulos3D::calcular_normales_caras(){

  normales_caras.resize(caras.size());

  for(unsigned long i=0; i<caras.size(); ++i){
    // obtener dos vectores en el triangulo y calcular su producto vectorial
    _vertex3f a1=vertices[caras[i]._1]-vertices[caras[i]._0];
    _vertex3f a2=vertices[caras[i]._2]-vertices[caras[i]._0];
    _vertex3f n=a1.cross_product(a2);

    
    //modulo
    float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
    //normalizacion
    normales_caras[i]=_vertex3f(n.x/m, n.y/m, n.z/m);
  }

  b_normales_caras=true;
  
}

void _triangulos3D::calcular_normales_vertices(){

    if(b_normales_caras==false){
    calcular_normales_caras();
  }
    normales_vertices.resize(vertices.size());

  for(int i=0; i<vertices.size(); i++)
  {
    normales_vertices[i].x = 0.0;
    normales_vertices[i].y = 0.0;
    normales_vertices[i].z = 0.0;
  }

  for(int i=0; i<caras.size(); i++)
  {
    normales_vertices[caras[i]._0]+=normales_caras[i];
    normales_vertices[caras[i]._1]+=normales_caras[i];
    normales_vertices[caras[i]._2]+=normales_caras[i];
  }

  //Normalizacion
  for(int i=0; i<vertices.size(); i++)
  {
    normales_vertices[i].normalize();
  }

  b_normales_vertices=true;

}


void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}


//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);
/*
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}



//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	caras_par.clear();
 caras_imp.clear();
 // divido las caras en par e impar
 for(int i=0; i<caras.size(); i++){
   if (i%2==0) caras_par.push_back(caras[i]);
   else caras_imp.push_back(caras[i]);
   }


glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glColor3f(r1,g1,b1);
glDrawElements(GL_TRIANGLES,caras_par.size()*3,GL_UNSIGNED_INT,&caras_par[0]);
glColor3f(r2,g2,b2);
glDrawElements(GL_TRIANGLES,caras_imp.size()*3,GL_UNSIGNED_INT,&caras_imp[0]);

	/*
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/

}


//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
    case SOLID_ILLUMINATED_FLAT: draw_iluminacion_plana();break;
    case SOLID_ILLUMINATED_GOURAUD: draw_iluminacion_suave();break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
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
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply()
{
   // leer lista de coordenadas de vértices y lista de indices de vértices

}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;

_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
	}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }

 // tapa inferior
if (fabs(perfil[0].x)>0.0 && tapa==1)
  {
  }

 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0 && tapa==1)
  {
  }
}
//*************************************************************************
// clase ESFERA
//*************************************************************************
_esfera:: _esfera(float radio,float latitud, float longitud){

	_vertex3f aux;
	num=longitud;
    for (int i=1;i<longitud;i++){
		aux.x=sin(M_PI*i/latitud)*-radio;
		aux.y=cos(M_PI*i/latitud)*-radio;
		aux.z=0.0;
		perfil.push_back(aux);
	}

    _rotacion::parametros(perfil,longitud,1);

}
//************************************************************************
// objeto articulado: tanque
//************************************************************************

_chasis::_chasis()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.107;aux.y=-0.5;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.107;aux.y=0.5;aux.z=0.0;
perfil.push_back(aux);
rodamiento.parametros(perfil,12,1);
altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(1.0,0.22,0.95);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.25,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(0.5,0.0,0.0);
glRotatef(90.0,1,0,0);
rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}



//************************************************************************

_torreta::_torreta()
{
altura=0.18;
anchura=0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.65,0.18,0.6);
base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.325,0,0);
glRotatef(90.0,0,0,1);
glScalef(0.18,0.16,0.6);
parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.04;aux.y=-0.4;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.04;aux.y=0.4;aux.z=0.0;
perfil.push_back(aux);
tubo_abierto.parametros(perfil,12,0);
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

glPushMatrix();
glTranslatef(0.4,0,0);
glRotatef(90.0,0,0,1);
tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}


//************************************************************************

_tanque::_tanque()
{
giro_tubo=2.0;
giro_torreta=0.0;
giro_tubo_min=-9;
giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

glRotatef(giro_torreta,0,1,0);
glPushMatrix();
glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();

glPushMatrix();
glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
glRotatef(giro_tubo,0,0,1);
tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
glPopMatrix();

};


//************************************************************************
// objeto articulado: gruaJuan
//************************************************************************
_base::_base(){
	altura=0.22;
};
void _base::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	glScalef(0.4,0.08,0.35);
	base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
};
_estructuraVertical::_estructuraVertical(){
	altura=1.07;
	anchura=0.55;
};
void _estructuraVertical::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	//cout <<"gg\n";
	glPushMatrix();
	glTranslatef(0,0.17,0);
	glScalef(0.4,0.3,0.35);
	trozos.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0.47,0);
	glScalef(0.4,0.3,0.35);
	trozos.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0.77,0);
	glScalef(0.4,0.3,0.35);
	trozos.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,1.07,0);
	glScalef(0.4,0.3,0.35);
	trozos.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,1.37,0);	//glRotate(90.0,1,0,0);
	glScalef(0.4,0.3,0.35);
	trozos.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,1.57,0);	//glRotate(90.0,1,0,0);
	glScalef(0.4,0.08,0.35);
	baseSuperior.draw_solido(1.0,1.0,0.0);
	glPopMatrix();
};
_estructuraHorizontal::_estructuraHorizontal(){

};
void _estructuraHorizontal::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){

	glPushMatrix();
	glTranslatef(-0.6,1.67,0);
	glScalef(0.3,0.2,0.25);
	trozo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3,1.67,0);
	glScalef(0.3,0.2,0.25);
	trozo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,1.67,0);
	glScalef(0.3,0.2,0.25);
	trozo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3,1.67,0);
	glScalef(0.3,0.2,0.25);
	trozo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6,1.67,0);
	glScalef(0.3,0.2,0.25);
	trozo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.9,1.67,0);
	glScalef(0.3,0.2,0.25);
	trozo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.2,1.67,0);
	glScalef(0.3,0.2,0.25);
	trozo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

};

_contraPeso::_contraPeso(){

};

void _contraPeso::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	glTranslatef(-0.6,1.67,0);
	glScalef(0.3,0.5,0.25);
	contra.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
};

_carro::_carro(){

};
void _carro::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	glTranslatef(0.32,1.47,0);
	glScalef(0.15,0.15,0.09);
	carro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
};

_cuerda::_cuerda(){

};
void _cuerda::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	//glTranslatef(0.32,1.0,0);
	//glScalef(0.03,0.75,0.05);
	cuerda.draw_solido(0.0,0.0,0.0);
	glPopMatrix();
};
_maza::_maza(){
	vector<_vertex3f> perfil;
	/*_vertex3f aux;
	aux.x=0.04;aux.y=-0.4;aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.04;aux.y=0.4;aux.z=0.0;
	perfil.push_back(aux);
	maza.parametros(perfil,12,0);
*/


	_vertex3f aux;

    for (int i=1;i<10;i++){
		aux.x=sin(M_PI*i/10)*-1;
		aux.y=cos(M_PI*i/10)*-1;
		aux.z=0.0;
		perfil.push_back(aux);
	}

    maza.parametros(perfil,10,1);
};
void _maza::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();

	glRotatef(90.0, 0, 1, 0);
	glScalef(0.15,0.185,0.15);
	//glScalef(10,10,10);
	maza.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
};
_grua::_grua(){
	giro_centro=1.0;
	moverCarro=0.1;
	moverCarroMax=0.9;
	moverCarroMin=0.1;
	moverCuerda=0.0;
	moverCuerdaMax=0.6;
	moverCuerdaMin=0.0;
};
void _grua::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	//esfera(1,10,10);
	glPushMatrix();
	base.draw(modo,r1,g1,b1,r2,g2,b2,grosor);

	glPushMatrix();
	glTranslatef(0.0,0.0,0.0);
	estructuraVertical.draw(EDGES,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glRotatef(giro_centro,0,1,0);
	glPushMatrix();
	glTranslatef(0.0,0.0,0.0);
	estructuraHorizontal.draw(EDGES,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	contraPeso.draw(modo,r1,g1,b1,r2,g2,b2,grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(moverCarro,0.0,0.0);
	glPushMatrix();
	carro.draw(modo,r1,g1,b1,r2,g2,b2,grosor);


	glPushMatrix();

    glTranslatef(0.32,1.0,0);
	glScalef(0.03,-abs(1.3*moverCuerda)+1,0.05);
    glTranslatef(0,moverCuerda+(moverCuerda*(0.4*moverCuerda)),0);
	cuerda.draw(SOLID,r1,g1,b1,r2,g2,b2,grosor);
    
	//glPopMatrix();
	glPushMatrix();
	glTranslatef(0.32,0.62,0);
	glRotatef(giroMaza, 0, 1, 0);
    glTranslatef(0,moverCuerda,0);

	maza.draw(modo,r1,g1,b1,r2,g2,b2,grosor);

	glPopMatrix();
	//glPopMatrix();
glPopMatrix();

};
