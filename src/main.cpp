#include <iostream>
#include <list>
#include "plataforma.h"

int main(){
  Plataforma p;
    // 1. Calcular max ID de etiqueta
    int max_etiqueta_id = -1;
    for (const auto& par : p.etiquetas)
        max_etiqueta_id = std::max(max_etiqueta_id, par.second->obtener_identificador());
    // 2. Calcular max ID de contenido
    int max_contenido_id = -1;
    for (const auto& par : p.catalogo)
        max_contenido_id = std::max(max_contenido_id, par.second->obtener_identificador());
    // 3. Dimensionar matriz con tamaño REAL
    p.secciones_eti_cont.resize(max_etiqueta_id + 1, max_contenido_id + 1);
    p.secciones_eti_cont.setZero();
    std::vector<Eigen::Triplet<int>> triplets;
    // 4. Rellenar matriz
    for (const auto& par : p.catalogo)
    {
        Contenido* cont = par.second;
        int col = cont->obtener_identificador();
        for (const auto& nombre_et : cont->obtener_categorias())
        {
            auto it = p.etiquetas.find(nombre_et);
            if (it == p.etiquetas.end())
            {
                std::cerr << "Advertencia: la etiqueta '" 
                          << nombre_et << "' no existe.\n";
                continue;
            }
            int fila = it->second->obtener_identificador();
            // Seguridad
            if (fila < 0 || col < 0) continue;
            triplets.emplace_back(fila, col, 1);
        }
    }
    // 5. Construir matriz dispersa
    p.secciones_eti_cont.setFromTriplets(triplets.begin(), triplets.end());
  p.guardar_secciones();
};