/*
Archivo .h que indica la existencia del contenido del contenido de la plataforma.
decimos que el contenido se refiere a las películas y series que tiene la plataforma,
las cuales tienen etiquetas que indica su tipo de contenido.
*/

#ifndef CONTENIDOS_H
#define CONTENIDOS_H

#include <string>
#include <list>

// ---------------------------------------------------------------------------
class Etiqueta{
	private:
		std::string nombre; //un nombre que define a que tipo de contenido hace referencia
		int etiqueta_id;

	public:
		Etiqueta(std::string nombre, int id);
		~Etiqueta();

		std::string obtener_etiqueta();
		int obtener_identificador();
};
// ---------------------------------------------------------------------------
class Contenido{
	protected:
		std::string nombre;
		float valoracion; //calificación según tipo de 1.0 a 10.0
		int id_contenido;
		bool es_pelicula;
		std::list<std::string> categorias;

	public:
		Contenido(std::string nombre, float valoracion, int id, std::list<std::string> tag);
		virtual ~Contenido();

		int obtener_identificador();
		std::string obtener_nombre();
		float obtener_valoracion();
		std::list<std::string> obtener_categorias();
		void anadir_categoria(Etiqueta e);
		bool tipo();
		virtual int obtener_duracion() const = 0;
};
// ---------------------------------------------------------------------------
class Pelicula: public Contenido{
	protected:
		int minutos;

	public:
		Pelicula(std::string nombre, float valoracion, int minutos, int id, std::list<std::string> tag);
		~Pelicula();

		int obtener_duracion() const override;
};
// ---------------------------------------------------------------------------
class Serie: public Contenido{
	protected:
		int cantidad_cap;

	public:
		Serie(std::string nombre, float valoracion, int can_cap, int id,
			std::list<std::string> tag);
		~Serie();

		int obtener_duracion() const override;
};
// ---------------------------------------------------------------------------
#endif