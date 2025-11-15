/*
Archivo .h que indica la existencia del contenido del contenido de la plataforma.
decimos que el contenido se refiere a las películas y series que tiene la plataforma,
las cuales tienen etiquetas que indica su tipo de contenido.
*/

#ifndef CONTENIDOS_H
#define CONTENIDOS_H

#include <string>
#include <list>

class Etiqueta{
	private:
		std::string nombre; //un nombre que define a que tipo de contenido hace referencia

	public:
		Etiqueta(std::string nombre);
		~Etiqueta();

		std::string obtener_etiqueta();
};

class Contenido{
	private:
		std::string nombre;
		float valoracion; //calificación según tipo de 0.0 a 5.0
		std::list<Etiqueta> categoria; 

	public:
		Contenido(std::string nombre, float valoracion);
		~Contenido();
};

#endif