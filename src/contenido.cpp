/*
Los método de la clase contenido y sus hijos series/películas
*/

#include "contenidos.h"

//============================================================================
// Clase Etiqueta

/*
Constructor de etiqueta
*/
Etiqueta::Etiqueta(std::string nombre, int id){
  this->nombre = nombre;
  this->etiqueta_id = id;
};

Etiqueta::~Etiqueta(){
};

/*
Retorna la etiqueta (o sea su nombre)
*/
std::string Etiqueta::obtener_etiqueta(){
  return nombre;
};

int Etiqueta::obtener_identificador(){
  return etiqueta_id;
};
//============================================================================
//============================================================================
// Clase Contenido

/*
Constructor de Contenido
*/
Contenido::Contenido(std::string nombre, float valoracion, int id, std::list<std::string> tag){
  this->nombre = nombre;
  this->valoracion = valoracion;
  this->id_contenido = id;
  this->categorias = tag;
  this->es_pelicula = 0;
};

Contenido::~Contenido(){
};

/*
Método para obtener nombre de la serie/película
*/
std::string Contenido::obtener_nombre(){
  return nombre;
};

int Contenido::obtener_identificador(){
  return id_contenido;
};

/*
Método para obtener la valoración de la serie/película
*/
float Contenido::obtener_valoracion(){
  return valoracion;
};

/*
Método para obtener las categoráas de las etiquetas
*/
std::list<std::string> Contenido::obtener_categorias(){
  return categorias;
};

/*
Añade una etiqueta a la liste de etiquetas de la categoría
*/
void Contenido::anadir_categoria(Etiqueta categoria){
  categorias.push_back(categoria.obtener_etiqueta());
};

/*
Retorna si es película o serie (falso si es serie)
*/
bool Contenido::tipo(){
  return es_pelicula;
};
//============================================================================
//============================================================================
//Clases Serie y Pelicula

/*
Constructor de Pelicula
*/
Pelicula::Pelicula(std::string nombre, float valoracion, int minutos, int id,
  std::list<std::string> tag)
:Contenido(nombre, valoracion, id, tag){
  this->minutos = minutos; //duracion en minutos
  this->es_pelicula = 1;
};

Pelicula::~Pelicula(){
};

/*
Retorna los minutos que dura la película
*/
int Pelicula::obtener_duracion() const{
  return minutos;
};

/*
Constructor de Serie
*/
Serie::Serie(std::string nombre, float valoracion, int can_cap,
  int id, std::list<std::string> tag)
:Contenido(nombre, valoracion, id, tag){
  this->cantidad_cap = can_cap; //Cantidad de capítulos
};

Serie::~Serie(){
};

/*
Retorna la cantidad de capítulos de la pelicula
*/
int Serie::obtener_duracion() const{
  return cantidad_cap;
};