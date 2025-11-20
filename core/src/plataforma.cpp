/*
Los métodos de las clases Plan y Plataforma
*/
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "../include/EigenConfig.h"
#include "../include/plataforma.h"
#include <Eigen/SparseCore>
#include <nlohmann/json.hpp>

// ===========================================================================
// Clase Plan

/*
Constructor de Plan
*/
Plan::Plan(std::string nombre, int costo){
  this->nombre = nombre;
  this->costo = costo;
};

Plan::~Plan(){
};

std::string Plan::obtener_nombre(){
  return nombre;
};

// =========================
// Clase Basico
// =========================

/*
Constructor de Basico
*/
Basico::Basico()
  :Plan("Básico", 12000){ 
};

/*
Destructor de Basico
*/
Basico::~Basico(){
};

// =========================
// Clase Premium
// =========================

/*
Constructor de Premium
*/
Premium::Premium()
  :Plan("Premium", 29000){
}

/*
Destructor de Premium
*/
Premium::~Premium(){
};
// ===========================================================================
// ===========================================================================
// Clase Plataforma

/*
Constructor de Plataforma, cargo los datos de un json en la carpeta data
*/
Plataforma::Plataforma(){
  try {
    // Cargar etiquetas
    std::ifstream f_et("../../../../core/data/etiquetas.json");
    if (!f_et.is_open())
        throw std::runtime_error("No se pudo abrir data/etiquetas.json");
    nlohmann::json j_et;
    f_et >> j_et;
    cargar_etiquetas(j_et);
    // Cargar contenidos
    std::ifstream f_con("../../../../core/data/contenidos.json");
    if (!f_con.is_open())
        throw std::runtime_error("No se pudo abrir data/contenidos.json");
    nlohmann::json j_con;
    f_con >> j_con;
    cargar_contenidos(j_con);
    // Cargar usuarios
    std::ifstream f_us("../../../../core/data/usuarios.json");
    if (!f_us.is_open())
        throw std::runtime_error("No se pudo abrir data/usuarios.json");
    nlohmann::json j_us;
    f_us >> j_us;
    cargar_usuarios(j_us);
    // Cargar secciones (etiqueta-contenido)
    std::ifstream f_sec("../../../../core/data/secciones.json");
    if (!f_sec.is_open())
        throw std::runtime_error("No se pudo abrir data/secciones.json");
    nlohmann::json j_sec;
    f_sec >> j_sec;
    cargar_secciones(j_sec);
    // Cargar datos de usuarios
    std::ifstream f_dat("../../../../core/data/datos_usuarios.json");
    if (!f_dat.is_open())
        throw std::runtime_error("No se pudo abrir data/datos_usuarios.json");
    nlohmann::json j_dat;
    f_dat >> j_dat;
    cargar_datos_usuarios(j_dat);
    std::cout << "Datos cargados correctamente.\n";
}
catch (nlohmann::json::parse_error& e) {
  throw std::runtime_error("ERROR: Uno de los archivos JSON está corrupto: " + std::string(e.what()));
}
catch (std::exception& e) {
  throw std::runtime_error("ERROR al cargar los datos de la plataforma: " + std::string(e.what()));
  }
};

/*
El destructor de la Platoforma, guarda en json los cambios
*/
Plataforma::~Plataforma(){
};

/*
guarda en json las etiquetas de la plataforma en la ruta data/etiquetas.json
*/
void Plataforma::guardar_etiquetas(){
  nlohmann::json j;
  for (const auto& par:etiquetas){
    Etiqueta* et = par.second;
    nlohmann::json jc;
    jc["id"] = et->obtener_identificador();
    jc["nombre"] = et->obtener_etiqueta();
    j.push_back(jc);
}
  std::ofstream f("../../../../core/data/etiquetas.json");
  if(!f.is_open())
    throw std::runtime_error("No se pudo abrir data/etiquetas.json");
  f << std::setw(4) << j;
};

/*
guarda en json los contenidos de la plataforma en la ruta data/contenidos.json
*/
void Plataforma::guardar_contenidos(){
  nlohmann::json j;
  for (const auto& par:catalogo){
    Contenido* c = par.second;
    nlohmann::json jc;
    jc["id"] = c->obtener_identificador();
    jc["nombre"] = c->obtener_nombre();
    jc["valoracion"] = c->obtener_valoracion();
    jc["duracion"] = c->obtener_duracion();
    // Etiquetas asociadas al contenido
    for(auto& et:c->obtener_categorias()){
      jc["etiquetas"].push_back(et);
    }
    jc["tipo"] = c->tipo()? "Pelicula":"Serie";
    j.push_back(jc);
  }
  std::ofstream f("../../../../core/data/contenidos.json");
  if(!f.is_open())
    throw std::runtime_error("No se pudo abrir data/contenidos.json");
  f << std::setw(4) << j;
};

/*
guarda en json los usuarios de la plataforma en la ruta data/usuarios.json
*/
void Plataforma::guardar_usuarios(){
  nlohmann::json j;
  for(const auto& par:usuarios){
    Usuario* u = par.second;
    nlohmann::json jc;
    jc["id"] = u->obtener_identificacdor();
    jc["nombre"] = u->obtener_nombre();
    jc["plan"] = u->obtener_plan()->obtener_nombre();
    j.push_back(jc);
  }
  std::ofstream f("../../../../core/data/usuarios.json");
  if(!f.is_open())
    throw std::runtime_error("No se pudo abrir data/usuarios.json");
  f << std::setw(4) << j;
};

/*
guarda en json las secciones de la plataforma en la ruta data/secciones.json,
las secciones son la relación entre etiquetas y contenidos de la plataforma
*/
void Plataforma::guardar_secciones(){
  nlohmann::json j;
  // matriz sparse etiqueta-contenido
  for(int k=0; k<secciones_eti_cont.outerSize(); ++k){
    for(Eigen::SparseMatrix<int>::InnerIterator it(secciones_eti_cont, k); it; ++it){
      nlohmann::json jc;
      jc["fila"] = it.row();
      jc["columna"]= it.col();
      jc["valor"] = it.value();
      j.push_back(jc);
    }
  }
  std::ofstream f("../../../../core/data/secciones.json");
  if(!f.is_open())
    throw std::runtime_error("No se pudo abrir data/secciones.json");
  f << std::setw(4) << j;
};

/*
guarda en json los datos de los usuarios plataforma en la ruta
data/datos_usuarios.json, los datos son la relación entre los usuarios y contenidos
*/
void Plataforma::guardar_datos_usuarios(){
  nlohmann::json j;
  // matriz sparse usuario → contenido visto
  for(int k=0; k<datos_usuario.outerSize(); ++k){
    for (Eigen::SparseMatrix<float>::InnerIterator it(datos_usuario, k); it; ++it){
      nlohmann::json jc;
      jc["usuario"] = it.row();
      jc["contenido"] = it.col();
      jc["valor"] = it.value();
      j.push_back(jc);
    }
  }
  std::ofstream f("../../../../core/data/datos_usuarios.json");
  if(!f.is_open())
    throw std::runtime_error("No se pudo abrir data/datos_usuarios.json");
  f << std::setw(4) << j;
};

/*
Guarda los cambios y añadidos que se hacen en las estructuras y se guardan en
los json
*/
void Plataforma::guardar_datos(){
  guardar_etiquetas();
  guardar_contenidos();
  guardar_usuarios();
  guardar_secciones();
  guardar_datos_usuarios();
};

/*
Cargar etiquetas desde data/etiquetas.json
*/
void Plataforma::cargar_etiquetas(const nlohmann::json& j) {
  etiquetas.clear();
    for (const auto& et_json : j) {
    int id = et_json["id"];
    std::string nombre = et_json["nombre"];
    Etiqueta* et = new Etiqueta(nombre, id);
    etiquetas[nombre] = et;
  }
}

/*
Cargar contenidos desde data/contenidos.json
*/
void Plataforma::cargar_contenidos(const nlohmann::json& j) {
  catalogo.clear();
  for (const auto& c_json:j){
    std::list<std::string> l;
    // Asociar etiquetas
    for(const auto& et:c_json["etiquetas"]){
      l.push_back(et);
    }
    int id = c_json["id"];
    std::string nombre = c_json["nombre"];
    float valoracion = c_json["valoracion"];
    int d = c_json["duracion"];
    if(c_json["tipo"]=="Pelicula"){
      Contenido* c = new Pelicula(nombre, valoracion, d, id, l);
      catalogo[nombre] = c;
    }
    else{
      Contenido* c = new Serie(nombre, valoracion, d, id, l);
      catalogo[nombre] = c;
    }
    indice_duracion.insert({d, nombre});
    indice_valoracion.insert({valoracion, nombre});
  }
};

/*
Cargar usuarios desde data/usuarios.json
*/
void Plataforma::cargar_usuarios(const nlohmann::json& j){
  usuarios.clear();
  for (const auto& u_json:j){
    int id = u_json["id"];
    std::string nombre = u_json["nombre"];
    std::string plan_nombre = u_json["plan"];
    Usuario* u = new Usuario(nombre, id);
    if(plan_nombre == "Premium") u->cambiar_plan();
    usuarios[nombre] = u;
  }
};

/*
Cargar matriz secciones (etiqueta → contenido) desde data/secciones.json
*/
void Plataforma::cargar_secciones(const nlohmann::json& j){
  int maxFila = 0;
  int maxCol  = 0;
  for(const auto& item:j){
    int fila=item["fila"];
    int col =item["columna"];
    if(fila>maxFila) maxFila = fila;
    if(col >maxCol ) maxCol  = col;
  }
  secciones_eti_cont.resize(maxFila+1, maxCol+1);
  secciones_eti_cont.setZero();
  for (const auto& item : j){
    int fila = item["fila"];
    int col = item["columna"];
    int valor = item["valor"];
    secciones_eti_cont.coeffRef(fila, col) = valor;
  }
};

/*
Cargar matriz datos de usuarios (usuario → contenido visto) desde data/datos_usuarios.json
*/
void Plataforma::cargar_datos_usuarios(const nlohmann::json& j){
  int maxFila = 0;
  int maxCol  = 0;
  for(const auto& item:j){
    int fila=item["usuario"];
    int col =item["contenido"];
    if(fila>maxFila) maxFila = fila;
    if(col >maxCol ) maxCol  = col;
  }
  datos_usuario.resize(usuarios.size()+1, catalogo.size()+1);
  datos_usuario.setZero();
  for(const auto& item : j){
    int fila = item["usuario"];
    int col = item["contenido"];
    float valor = item["valor"];
    datos_usuario.coeffRef(fila, col) = valor;
  }
}

/*
Añade una etiqueta a las disponables en la plataforma
*/
void Plataforma::anadir_etiqueta(std::string nombre){
  if(etiquetas.count(nombre)){
    throw std::runtime_error("La etiqueta ya existe: "+nombre);
  }
  int id = etiquetas.size();
  etiquetas[nombre] = new Etiqueta(nombre, id);
  secciones_eti_cont.conservativeResize(id+1, catalogo.size());
};

/*
Añade un nuevo conteido al catálogo
*/
void Plataforma::anadir_contenido(std::string nombre, int duracion, float valoracion,
	std::list<std::string> tag, bool es_pelicula){
    if(catalogo.count(nombre)){
      throw std::runtime_error("El contenido ya existe: "+nombre);
    }
    int id = catalogo.size();
    if(es_pelicula){
      catalogo[nombre] = new Pelicula(nombre, valoracion, duracion, id, tag);
    }
    else{
      catalogo[nombre] = new Serie(nombre, valoracion, duracion, id, tag);
    }
    secciones_eti_cont.conservativeResize(etiquetas.size(), id+1);
    datos_usuario.conservativeResize(usuarios.size(), id+1);
    for(const std::string& t:tag){
      if(!etiquetas.count(t)){
        throw std::runtime_error("Etiqueta no existe: "+t);
      }
      int id_tag = etiquetas[t]->obtener_identificador();
      secciones_eti_cont.insert(id_tag, id) = 1;
    }
    indice_duracion.insert({duracion, nombre});
    indice_valoracion.insert({valoracion, nombre});
};

/*
Añade un nuevo usuario a la plataforma
*/
void Plataforma::anadir_usuario(std::string nombre){
  if (usuarios.count(nombre)){
    throw std::runtime_error("El usuario ya existe: "+nombre);
  }
  int id = usuarios.size();
  usuarios[nombre] = new Usuario(nombre, id);
  datos_usuario.conservativeResize(id+1, catalogo.size());
};
/**
 * Convierte una cadena a minúsculas para búsqueda case-insensitive
 */
std::string a_minusculas(const std::string& str){
    std::string res = str;
    std::transform(res.begin(), res.end(), res.begin(), 
      [](unsigned char c){ return std::tolower(c); });
    return res;
}

/**
 * Busca contenidos por nombre (búsqueda case-insensitive)
 */
std::list<Contenido*> Plataforma::buscar_por_nombre(const std::string& nombre_busqueda){
  std::list<Contenido*> resultados;
  std::string nombre_lower = a_minusculas(nombre_busqueda);
  for (const auto& par : catalogo) {
    Contenido* contenido = par.second;
    std::string nombre_contenido = a_minusculas(contenido->obtener_nombre());
    
    if (nombre_contenido.find(nombre_lower) != std::string::npos) {
      resultados.push_back(contenido);
    }
  }
  return resultados;
}

/**
 * Busca contenidos por etiqueta/categoría
 */
std::list<Contenido*> Plataforma::buscar_por_etiqueta(const std::string& etiqueta_busqueda) {
  std::list<Contenido*> resultados;
  
  // Verificar si la etiqueta existe
  if (etiquetas.find(etiqueta_busqueda) == etiquetas.end()) {
    return resultados; // Retorna lista vacía si la etiqueta no existe
  }
  
  int id_etiqueta = etiquetas[etiqueta_busqueda]->obtener_identificador();
  
  // Buscar en la matriz de secciones
  for (int j = 0; j < secciones_eti_cont.cols(); ++j) {
    if (secciones_eti_cont.coeff(id_etiqueta, j) == 1) {
      // Encontrar el contenido con ID j
      for (const auto& par : catalogo) {
        Contenido* contenido = par.second;
        if (contenido->obtener_identificador() == j) {
          resultados.push_back(contenido);
          break;
        }
      }
    }
}
  return resultados;
}

/**
 * Sistema de recomendación basado en contenido visto y etiquetas
 */
std::list<Contenido*> Plataforma::recomendar(std::string nombre) {
  Usuario* usuario = usuarios[nombre];
  std::list<Contenido*> recomendaciones;
  if (!usuario || usuarios.find(usuario->obtener_nombre()) == usuarios.end()) {
    return recomendaciones; // Usuario no válido
  }
  int user_id = usuario->obtener_identificacdor();
  // 1. Obtener contenidos ya vistos por el usuario
  std::vector<int> contenidos_vistos;
  for (int j = 0; j < datos_usuario.cols(); ++j) {
    if (datos_usuario.coeff(user_id, j) > 0) {
      contenidos_vistos.push_back(j);
    }
  }
  // 2. Obtener etiquetas de los contenidos vistos
  std::vector<int> etiquetas_interes;
  for (int contenido_id : contenidos_vistos) {
    for (int i = 0; i < secciones_eti_cont.rows(); ++i) {
      if (secciones_eti_cont.coeff(i, contenido_id) == 1) {
        etiquetas_interes.push_back(i);
      }
    }
}
  // 3. Calcular puntuación para cada contenido no visto
  std::list<std::pair<float, Contenido*>> puntuaciones;
  for (const auto& par : catalogo) {
    Contenido* contenido = par.second;
    int contenido_id = contenido->obtener_identificador();
    // Saltar si ya fue visto
    if (std::find(contenidos_vistos.begin(), contenidos_vistos.end(), contenido_id) != contenidos_vistos.end()) {
        continue;
    }
    
    // Calcular puntuación basada en etiquetas comunes
    float puntuacion = 0;
    for (int i = 0; i < secciones_eti_cont.rows(); ++i) {
      if (secciones_eti_cont.coeff(i, contenido_id) == 1) {
        // La etiqueta i está en este contenido
        int count = std::count(etiquetas_interes.begin(), etiquetas_interes.end(), i);
        puntuacion += count;
      }
    }
    
    // Bonus por valoración alta
    puntuacion += contenido->obtener_valoracion() / 10.0f;
    
    if (puntuacion > 0) {
      puntuaciones.push_back({puntuacion, contenido});
    }
  }
  // 4. Ordenar por puntuación descendente
  puntuaciones.sort([](const std::pair<float, Contenido*>& a, const std::pair<float, Contenido*>& b) {
    return a.first > b.first;
  });
  // 5. Tomar los top 10
  int count = 0;
  for (const auto& pair : puntuaciones) {
    if (count >= 10) break;
    recomendaciones.push_back(pair.second);
    count++;
  }
  return recomendaciones;
}

Usuario* Plataforma::buscar_usuario(std::string nombre){
  auto it = usuarios.find(nombre);
  if (it != usuarios.end()){
    return it->second;
  }
  return nullptr;
};

/*
Busca contenido usando un rango de duracion
*/
std::list<Contenido*> Plataforma::buscar_por_duracion(int min_d, int max_d){
  std::list<Contenido*> resultados;
  auto it_low  = indice_duracion.lower_bound(min_d);
  auto it_high = indice_duracion.upper_bound(max_d);
  for (auto it = it_low; it != it_high; ++it) {
      const std::string& nombre_contenido = it->second;
      // Recuperar el Contenido desde catalogo
      if (catalogo.count(nombre_contenido)) {
          resultados.push_back(catalogo[nombre_contenido]);
      }
  }
  return resultados;
}

/*
Busca contenido por un rango de valoración
*/
std::list<Contenido*> Plataforma::buscar_por_valoracion(float min_v, float max_v){
  std::list<Contenido*> resultados;
  auto it_low  = indice_valoracion.lower_bound(min_v);
  auto it_high = indice_valoracion.upper_bound(max_v); 
  for (auto it = it_low; it != it_high; ++it) {
      const std::string& nombre = it->second;
      resultados.push_back(catalogo[nombre]);
  }
  return resultados;
}