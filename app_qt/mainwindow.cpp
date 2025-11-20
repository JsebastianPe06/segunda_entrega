#include "mainwindow.h"
#include <QHeaderView>
#include <QInputDialog>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Plataforma Multimedia");
    resize(800,600);

    mostrarLogin();
}

MainWindow::~MainWindow() {}

void MainWindow::mostrarLogin() {
    loginWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(loginWidget);

    QLabel *lbl = new QLabel("Ingrese su nombre de usuario:");
    txtUsuario = new QLineEdit();
    btnEntrar = new QPushButton("Entrar");

    layout->addWidget(lbl);
    layout->addWidget(txtUsuario);
    layout->addWidget(btnEntrar);

    setCentralWidget(loginWidget);

    connect(btnEntrar, &QPushButton::clicked, this, &MainWindow::entrarUsuario);
}

void MainWindow::entrarUsuario() {
    std::string nombre = txtUsuario->text().toStdString();
    std::string nombre_lower = nombre;
    std::transform(nombre_lower.begin(), nombre_lower.end(), nombre_lower.begin(), ::tolower);

    usuario_actual = nullptr;
    for (const auto& par : plataforma.usuarios) {
        std::string u_name = par.second->obtener_nombre();
        std::string u_lower = u_name;
        std::transform(u_lower.begin(), u_lower.end(), u_lower.begin(), ::tolower);
        if (u_lower == nombre_lower) {
            usuario_actual = par.second;
            break;
        }
    }

    if (!usuario_actual) {
        QMessageBox::warning(this, "Usuario no encontrado", "El usuario ingresado no existe.");
        return;
    }

    mostrarMainUI();
}

void MainWindow::mostrarMainUI() {
    mainWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(mainWidget);

    // Usuario info
    lblUsuario = new QLabel("Usuario: " + QString::fromStdString(usuario_actual->obtener_nombre()));
    lblPlanActual = new QLabel("Plan: " + QString::fromStdString(usuario_actual->obtener_plan()->obtener_nombre()));

    mainLayout->addWidget(lblUsuario);
    mainLayout->addWidget(lblPlanActual);

    // Buscador por nombre
    QHBoxLayout *hNombre = new QHBoxLayout();
    txtBuscarNombre = new QLineEdit();
    txtBuscarNombre->setPlaceholderText("Buscar contenido por nombre...");
    btnBuscarNombre = new QPushButton("Buscar");
    hNombre->addWidget(txtBuscarNombre);
    hNombre->addWidget(btnBuscarNombre);
    mainLayout->addLayout(hNombre);

    // Buscador por etiqueta
    QHBoxLayout *hEtiqueta = new QHBoxLayout();
    txtBuscarEtiqueta = new QLineEdit();
    txtBuscarEtiqueta->setPlaceholderText("Buscar contenido por etiqueta...");
    btnBuscarEtiqueta = new QPushButton("Buscar");
    hEtiqueta->addWidget(txtBuscarEtiqueta);
    hEtiqueta->addWidget(btnBuscarEtiqueta);
    mainLayout->addLayout(hEtiqueta);

    // Buscador por duración
    QHBoxLayout *hDuracion = new QHBoxLayout();
    txtBuscarDuracionMin = new QLineEdit();
    txtBuscarDuracionMin->setPlaceholderText("Duración mínima (minutos)...");
    txtBuscarDuracionMax = new QLineEdit();
    txtBuscarDuracionMax->setPlaceholderText("Duración máxima (minutos)...");
    btnBuscarDuracion = new QPushButton("Buscar");
    hDuracion->addWidget(txtBuscarDuracionMin);
    hDuracion->addWidget(txtBuscarDuracionMax);
    hDuracion->addWidget(btnBuscarDuracion);
    mainLayout->addLayout(hDuracion);


    // Buscador por valoración (rango)
    QHBoxLayout *hValoracion = new QHBoxLayout();
    txtBuscarValoracionMin = new QLineEdit();
    txtBuscarValoracionMin->setPlaceholderText("Valoración mínima (ej: 4.0)...");
    txtBuscarValoracionMax = new QLineEdit();
    txtBuscarValoracionMax->setPlaceholderText("Valoración máxima (ej: 9.5)...");
    btnBuscarValoracion = new QPushButton("Buscar");
    hValoracion->addWidget(txtBuscarValoracionMin);
    hValoracion->addWidget(txtBuscarValoracionMax);
    hValoracion->addWidget(btnBuscarValoracion);
    mainLayout->addLayout(hValoracion);

    // Recomendaciones
    btnRecomendaciones = new QPushButton("Mostrar recomendaciones");
    mainLayout->addWidget(btnRecomendaciones);

    // Tabla resultados
    tblResultados = new QTableWidget();
    tblResultados->setColumnCount(6);
    QStringList headers;
    headers << "Nombre" << "Tipo" << "Valoración" << "Duración" << "Etiquetas" << "Acción";
    tblResultados->setHorizontalHeaderLabels(headers);
    tblResultados->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(tblResultados);

    setCentralWidget(mainWidget);

    // Conexiones
    connect(btnBuscarNombre, &QPushButton::clicked, this, &MainWindow::buscarPorNombre);
    connect(btnBuscarEtiqueta, &QPushButton::clicked, this, &MainWindow::buscarPorEtiqueta);
    connect(btnBuscarDuracion, &QPushButton::clicked, this, &MainWindow::buscarPorDuracion);
    connect(btnBuscarValoracion, &QPushButton::clicked, this, &MainWindow::buscarPorValoracion);
    connect(btnRecomendaciones, &QPushButton::clicked, this, &MainWindow::mostrarRecomendaciones);

    // Mostrar recomendaciones al entrar
    mostrarRecomendaciones();
}

void MainWindow::actualizarTabla(const std::list<Contenido*>& lista) {
    tblResultados->setRowCount((int)lista.size());
    int row = 0;
    for (Contenido* c : lista) {
        tblResultados->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(c->obtener_nombre())));
        tblResultados->setItem(row, 1, new QTableWidgetItem(c->tipo() ? "Pelicula" : "Serie"));
        tblResultados->setItem(row, 2, new QTableWidgetItem(QString::number(c->obtener_valoracion())));
        tblResultados->setItem(row, 3, new QTableWidgetItem(QString::number(c->obtener_duracion())));

        // Etiquetas concatenadas
        std::string etiquetas;
        for (auto &e : c->obtener_categorias()) {
            etiquetas += e + ", ";
        }
        if (!etiquetas.empty()) etiquetas.pop_back(), etiquetas.pop_back();
        tblResultados->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(etiquetas)));

        // Botón acción: Ver contenido
        QPushButton *btnVer = new QPushButton("Ver");
        tblResultados->setCellWidget(row, 5, btnVer);
        connect(btnVer, &QPushButton::clicked, [=](){ calificarContenido(row); });

        row++;
    }
}

void MainWindow::buscarPorNombre() {
    std::string nombre = txtBuscarNombre->text().toStdString();
    auto lista = plataforma.buscar_por_nombre(nombre);
    actualizarTabla(lista);
}

void MainWindow::buscarPorEtiqueta() {
    std::string etiqueta = txtBuscarEtiqueta->text().toStdString();
    auto lista = plataforma.buscar_por_etiqueta(etiqueta);
    actualizarTabla(lista);
}

void MainWindow::mostrarRecomendaciones() {
    auto lista = plataforma.recomendar(usuario_actual->obtener_nombre());
    actualizarTabla(lista);
}

void MainWindow::buscarPorDuracion() {
    bool okMin, okMax;
    int minDur = txtBuscarDuracionMin->text().toInt(&okMin);
    int maxDur = txtBuscarDuracionMax->text().toInt(&okMax);

    if (!okMin || !okMax || minDur > maxDur) {
        QMessageBox::warning(this, "Error", "Ingrese un rango válido de duración.");
        return;
    }

    auto lista = plataforma.buscar_por_duracion(minDur, maxDur); // Función por rango
    actualizarTabla(lista);
}

void MainWindow::buscarPorValoracion() {
    bool okMin, okMax;
    float minVal = txtBuscarValoracionMin->text().toFloat(&okMin);
    float maxVal = txtBuscarValoracionMax->text().toFloat(&okMax);

    if (!okMin || !okMax || minVal > maxVal) {
        QMessageBox::warning(this, "Error", "Ingrese un rango válido de valoración.");
        return;
    }

    auto lista = plataforma.buscar_por_valoracion(minVal, maxVal); // Función por rango
    actualizarTabla(lista);
}

void MainWindow::calificarContenido(int fila) {
    // Obtener contenido
    QTableWidgetItem *item = tblResultados->item(fila,0);
    std::string nombreContenido = item->text().toStdString();
    Contenido* c = plataforma.catalogo[nombreContenido];

    // Simular ver contenido
    QMessageBox::information(this, "Viendo contenido", QString::fromStdString("Viendo: " + nombreContenido));

    // Pedir calificación
    bool ok;
    int calificacion = QInputDialog::getInt(this, "Calificar contenido", "Ingresa puntuación 1-10", 5, 1, 10, 1, &ok);
    if (ok) {
        int user_id = usuario_actual->obtener_identificacdor();
        int contenido_id = c->obtener_identificador();
        plataforma.datos_usuario.coeffRef(user_id, contenido_id) = calificacion;

        QMessageBox::information(this, "Calificado", "Calificación registrada.");
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    try {
        plataforma.guardar_datos();
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Error al guardar", e.what());
    }
    event->accept();
}
