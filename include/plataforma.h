/*
El archivo .h que define la existencia de la plataforma de streaming tipo netflix
con clases contenedoras del contenido, apoyadoras al usuario y la clase de la propia
platforma en sí.
*/

#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <string>

#include "contenidos.h"

class Secciones{
	private:
		std::string nombre;
	
	public:
		Secciones(std::string nombre);
		~Secciones();
};

class Plan{
	protected:
		std::string nombre;
		int costo;
	
	public:
		Plan(std::string nombre, int costo);
		virtual ~Plan();
};

class Basico: public Plan{
	public:
		Basico();
};

class Premium: public Plan{
	public:
		Premium();
};


class Plataforma{
};

#endif