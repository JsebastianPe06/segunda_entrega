/*
El archivo .h que define la existencia de la plataforma de streaming tipo netflix
con clases contenedoras del contenido, apoyadoras al usuario y la clase de la propia
platforma en sí.
*/

#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <string>
#include <map> //Diccionarios ordenados
#include <unordered_map> //Tablas hash

#include <Eigen/SparseCore> //Lbrería externa para usar matrices y vectores dispersos
#include <nlohmann/json.hpp> //Librería externa para usar json

#include "contenidos.h"
#include "usuarios.h"

class Plan{
	protected:
		std::string nombre;
		int costo; //costo en cop
	
	public:
		Plan(std::string nombre, int costo);
		virtual ~Plan();

		std::string obtener_nombre();
};

class Basico: public Plan{
	public:
		Basico();
		~Basico();
};

class Premium: public Plan{
	public:
		Premium();
		~Premium();
};


class Plataforma{
	public:
		std::unordered_map<std::string, Contenido*> catalogo; //todo el contenido de la plataforma
		std::unordered_map<std::string, Etiqueta*> etiquetas;
		std::unordered_map<std::string, Usuario*> usuarios;
		Eigen::SparseMatrix<int> secciones_eti_cont; //1 si la etiqueta se relaciona al contenido, 0 si no
		Eigen::SparseMatrix<float> datos_usuario; //Relaciona usuarios con contenido de si vió o no algo

	public:
		Plataforma();
		~Plataforma();

		void anadir_etiqueta(std::string nombre);
		void anadir_contenido(std::string nombre, int duracion, float valoracion,
			std::list<std::string> tag, bool es_pelicula); //este método también trata las etiquetas
		void anadir_usuario(std::string nombre);

		//formato json guardado en data

		void guardar_datos();
		void guardar_usuarios();
		void guardar_etiquetas();
		void guardar_contenidos();
		void guardar_secciones();
		void guardar_datos_usuarios();

		void cargar_usuarios(const nlohmann::json& j);
		void cargar_etiquetas(const nlohmann::json& j);
		void cargar_contenidos(const nlohmann::json& j);
		void cargar_secciones(const nlohmann::json& j);
		void cargar_datos_usuarios(const nlohmann::json& j);
};

#endif