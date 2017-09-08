#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

#include <iostream>
#include <string.h>
extern "C" {
#include <canciones.h>
#include<albums.h>
#include<artistas.h>
#include<stack.h>
#include<queue.h>
#include<circle_double_list.h>
}
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_5_clicked();

    void on_accionMontar_triggered();

    void AgregarCancion(artistas* _artistas, char* _artista, char* _album, char* nombre, char* path, char* valuacion);

    cancion* BuscarCancion(artistas *_artistas, char *_artista, char *_album, char *nombre);

    void EliminarCancion(artistas *_artistas, char *_artista, char *_album, char *nombre);

    void MontarArchivo(artistas* _artistas, string path);

    void on_ARTISTAS_currentTextChanged(const QString &arg1);

    void on_ALBUMS_currentTextChanged(const QString &arg1);

    void on_CANCIONES_currentTextChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_btn_Eliminar_clicked();

    void on_pushButton_2_clicked();

    void on_playlist_type_currentTextChanged(const QString &arg1);

    void on_playlist_type_currentIndexChanged(int index);

    void on_actionTop_5_Canciones_2_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    artistas* Artistas;

    artista* current_artist;
    album* current_album;
    cancion* current_song;
    stack_Play* stack_playlist;
    queue_Play* cola_playlist;
    canciones* canciones_top5;
    circle_double_list* circular_playlist;

};

#endif // MAINWINDOW_H
