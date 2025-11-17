/*
El archivo .h que define la existencias de los usuarios.
*/

#include <string>

#ifndef USUARIOS_H
#define USUARIOS_H

class Plan;

class Usuario{
  private:
    std::string nombre;
    int identificador;
    Plan* tipo_cuenta;

  public:
    Usuario(std::string nombre, int identificador);
    ~Usuario();

    std::string obtener_nombre();
    Plan* obtener_plan();
    int obtener_identificacdor();
    void cambiar_plan();
};

#endif