#include <string>

#include "usuarios.h"
#include "plataforma.h"

/*
Constructor de Usuario
*/
Usuario::Usuario(std::string nombre, int identificador){
  this->nombre = nombre;
  this->identificador = identificador;
  this->tipo_cuenta = new Basico(); // Siempre inicia en básico
}

/*
Destructor de usuario
*/
Usuario::~Usuario(){
  delete tipo_cuenta; // No hace falta apuntar a nullptr porque en si los usuarios se borran
}

/*
Este método retorna el nombre del usuario
*/
std::string Usuario::obtener_nombre(){
  return nombre;
};

/*
Este método retorna el tipo de plan del usuario
*/
Plan* Usuario::obtener_plan(){
  return tipo_cuenta;
};

/*
Este método retorna el identificador del usuario
*/
int Usuario::obtener_identificacdor(){
  return identificador;
};

/*
Este método cambia de un plan a otro, o sea de básico a premium y viseversa
*/
void Usuario::cambiar_plan(){
  if(tipo_cuenta->obtener_nombre()=="Básico"){
    delete tipo_cuenta;
    tipo_cuenta = new Premium();
  }
  else{
    delete tipo_cuenta;
    tipo_cuenta = new Basico();
  }
};