/*
Árbol Binario de Búsqueda para optimizar búsquedas de contenido
por valoración. Permite búsquedas por rango y mantiene el contenido
ordenado para acceso eficiente.
*/

#ifndef BST_CONTENIDO_H
#define BST_CONTENIDO_H

#include <list>
#include <functional>
#include "contenidos.h"

// Nodo del árbol binario de búsqueda
class NodoContenido {
public:
    Contenido* contenido;
    NodoContenido* izquierdo;
    NodoContenido* derecho;
    int altura;  // Para balanceo AVL (opcional)
    
    NodoContenido(Contenido* c) 
        : contenido(c), izquierdo(nullptr), derecho(nullptr), altura(1) {}
    
    ~NodoContenido() {
        // No borramos contenido, solo el nodo
        // El contenido lo maneja Plataforma
    }
};

// Árbol binario de búsqueda para contenido
class ArbolContenido {
private:
    NodoContenido* raiz;
    int total_nodos;
    
    // Funciones auxiliares recursivas
    NodoContenido* insertar_recursivo(NodoContenido* nodo, Contenido* c, 
                                      std::function<bool(Contenido*, Contenido*)> comparador);
    
    void inorden_recursivo(NodoContenido* nodo, std::list<Contenido*>& lista);
    
    void buscar_rango_recursivo(NodoContenido* nodo, float min, float max, 
                                std::list<Contenido*>& resultados);
    
    NodoContenido* encontrar_max(NodoContenido* nodo);
    NodoContenido* encontrar_min(NodoContenido* nodo);
    
    void destruir_recursivo(NodoContenido* nodo);
    
    // Para balanceo AVL
    int obtener_altura(NodoContenido* nodo);
    int obtener_balance(NodoContenido* nodo);
    NodoContenido* rotar_derecha(NodoContenido* y);
    NodoContenido* rotar_izquierda(NodoContenido* x);
    
public:
    ArbolContenido();
    ~ArbolContenido();
    
    // Inserción con criterio personalizable
    void insertar_por_valoracion(Contenido* c);
    void insertar_por_nombre(Contenido* c);
    void insertar_custom(Contenido* c, std::function<bool(Contenido*, Contenido*)> comparador);
    
    // Búsquedas
    std::list<Contenido*> buscar_rango_valoracion(float min, float max);
    Contenido* buscar_mejor_valorado();
    Contenido* buscar_peor_valorado();
    std::list<Contenido*> obtener_top_n(int n);
    std::list<Contenido*> obtener_todo_ordenado();
    
    // Estadísticas
    int obtener_cantidad();
    bool esta_vacio();
    float promedio_valoracion();
};

// Árbol especializado para rankings múltiples
class SistemaRankings {
private:
    ArbolContenido* arbol_por_valoracion;
    ArbolContenido* arbol_por_popularidad;  // Basado en visualizaciones
    
public:
    SistemaRankings();
    ~SistemaRankings();
    
    void agregar_contenido(Contenido* c, int num_visualizaciones);
    
    std::list<Contenido*> top_mejor_valorados(int n);
    std::list<Contenido*> top_mas_populares(int n);
    std::list<Contenido*> contenido_premium(float min_rating, int min_views);
};

#endif