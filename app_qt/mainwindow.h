#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTimer>

#include "../core/include/plataforma.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override; // Guardar datos al cerrar

private:
    // Backend
    Plataforma plataforma;
    Usuario* usuario_actual = nullptr;

    // Login
    QWidget *loginWidget;
    QLineEdit *txtUsuario;
    QPushButton *btnEntrar;

    // Main UI
    QWidget *mainWidget;
    QLineEdit *txtBuscarNombre;
    QLineEdit *txtBuscarEtiqueta;
    QLineEdit *txtBuscarDuracionMin;
    QLineEdit *txtBuscarDuracionMax;
    QLineEdit *txtBuscarValoracionMin;
    QLineEdit *txtBuscarValoracionMax;
    QPushButton *btnBuscarNombre;
    QPushButton *btnBuscarEtiqueta;
    QPushButton *btnRecomendaciones;
    QPushButton *btnBuscarDuracion;
    QPushButton *btnBuscarValoracion;
    QTableWidget *tblResultados;
    QLabel *lblUsuario;
    QLabel *lblPlanActual;

    QVBoxLayout *mainLayout;

    // Métodos auxiliares
    void mostrarLogin();
    void mostrarMainUI();
    void actualizarTabla(const std::list<Contenido*>& lista);
    void actualizarUsuarioInfo();

private slots:
    void entrarUsuario();
    void buscarPorNombre();
    void buscarPorEtiqueta();
    void buscarPorDuracion();
    void buscarPorValoracion();
    void mostrarRecomendaciones();
    void calificarContenido(int fila);
};

#endif
