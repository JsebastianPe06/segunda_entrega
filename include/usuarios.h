/*
El archivo .h que define la existencias de los usuarios.
*/

#ifndef USUARIOS_H
#define USUARIOS_H

#include "plataforma.h"

class Usuario{
  private:
    std::string nombre;
    int identificador;
    Plan tipo_cuenta;

  public:
    Usuario(std::string nombre, int identificador, Plan tipo_cuenta);
};

#endif