#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <QFileDialog>
#include <string.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    std::string work_folder = "";
    ui->setupUi(this);
    QPixmap pix;
    player = new QMediaPlayer(this);

    ui->playlist_type->addItem("Pila");
    ui->playlist_type->addItem("Cola");
    ui->playlist_type->addItem("Circular");

    ////////////////////////////////////////////////////////    Current Song
    current_artist = NULL;
    current_album = NULL;
    current_song = NULL;

    ////////////////////////////////////////////////////////    Types of Reproduction (Lists)
    stack_playlist = (stack_Play*)malloc(sizeof(stack_Play));
    stack_playlist->head = NULL;

    cola_playlist = (queue_Play*)malloc(sizeof(queue_Play));
    cola_playlist->head = NULL;

    circular_playlist = (circle_double_list*)malloc(sizeof(circle_double_list));
    circular_playlist->head=NULL;
    circular_playlist->foot=NULL;


    canciones_top5 = (canciones*)malloc(sizeof(canciones));
    canciones_top5->head = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    player->stop();
    ui->txt_currentSong->setText("");
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    player->setVolume(position);
}

cancion* MainWindow::BuscarCancion(artistas *_artistas, char *_artista, char *_album, char *nombre){
    albums* new_albums;
    canciones* new_canciones;
    artista* a_tmp = search_cd(_artistas->head,_artistas->head,_artista);
    if(a_tmp!=NULL){
          album* al = search_d(a_tmp->_albums->head,a_tmp->_albums->head,_album);
           if(al!=NULL){
                cancion* canci = search(al->_canciones->head,al->_canciones->head,nombre);
                if(canci!=NULL){
                        return canci;
                }else{
                      QMessageBox::information(this,"!","La CANCION indicada NO existe en la Biblioteca");
                      return NULL;
                }
           }else{
                QMessageBox::information(this,"!","El ALBUM indicado NO existe en la Biblioteca");
                 return NULL;
           }
    }else{
        QMessageBox::information(this,"!","El ARTISTA indicado NO existe en la Biblioteca");
         return NULL;
    }
}

void MainWindow::EliminarCancion(artistas *_artistas, char *_artista, char *_album, char *nombre){
    albums* new_albums;
    canciones* new_canciones;
    artista* a_tmp = search_cd(_artistas->head,_artistas->head,_artista);
    if(a_tmp!=NULL){
          album* al = search_d(a_tmp->_albums->head,a_tmp->_albums->head,_album);
           if(al!=NULL){
                cancion* canci = search(al->_canciones->head,al->_canciones->head,nombre);
                if(canci!=NULL){
                        remove_any(al->_canciones,nombre);
                        if(al->_canciones->head==NULL){
                            remove_any_d(a_tmp->_albums,al->nombre);
                        }
                        if(a_tmp->_albums->head==NULL){
                           remove_any_cd(Artistas,a_tmp->nombre);
                        }
                }else{
                      QMessageBox::information(this,"!","La CANCION indicada NO existe en la Biblioteca");
                }
           }else{
                QMessageBox::information(this,"!","El ALBUM indicado NO existe en la Biblioteca");
           }
    }else{
        QMessageBox::information(this,"!","El ARTISTA indicado NO existe en la Biblioteca");
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    player->stop();
    ui->txt_currentSong->setText("");
    QString temp= ui->txt_Buscar->text();
    QStringList parametros = temp.split("_");
    char* _artista=(char*)malloc(100);
    char* _album = (char*)malloc(100);
    char* _cancion = (char*)malloc(100);


    QString a = parametros[0];
    QByteArray ba=a.toLatin1();
    strcpy(_artista,ba.data());

    QString b = parametros[1];
    QByteArray bab=b.toLatin1();
    strcpy(_album,bab.data());

    QString c = parametros[2];
    QByteArray bac=c.toLatin1();
    strcpy(_cancion,bac.data());

    current_song = BuscarCancion(Artistas,_artista,_album,_cancion); //////////////////////////////////// search the song
    if(current_song!=NULL){
       if(ui->playlist_type->currentText()=="Pila"){                 //////////////////////////////////// verify playlist type
           push_song(stack_playlist,current_song->nombre,current_song->path,current_song->path,stack_playlist->head);
           generar_imagen_stack(stack_playlist);
           QPixmap pix("/home/ferflo/Música/stack.png");            //////////////////////////////////// and refresh the playlist
           ui->img_playlist->setPixmap(pix);
       }else if(ui->playlist_type->currentText()=="Cola"){          //////////////////////////////////// verify playlist type
           eque_song(cola_playlist,current_song->nombre,current_song->path,current_song->path,NULL);
           generar_imagen_queue(cola_playlist);
           QPixmap pix("/home/ferflo/Música/queue.png");            //////////////////////////////////// and refresh the playlist
           ui->img_playlist->setPixmap(pix);
       }else if(ui->playlist_type->currentText()=="Circular"){      //////////////////////////////////// verify playlist type
           insert_front_d_song(circular_playlist,current_song);
            generar_imagen_circular(circular_playlist);
            QPixmap pix("/home/ferflo/Música/circular.png");        //////////////////////////////////// and refresh the playlist
            ui->img_playlist->setPixmap(pix);
       }
    }

}

void MainWindow::on_accionMontar_triggered()
{
    //////////////////////////////////////////////////////// Initialize the Artist List
    Artistas = (artistas*)malloc(sizeof(artistas));
    Artistas->head = NULL;
    Artistas->foot = NULL;

    //////////////////////////////////////////////////////// Calls File chooser
    QString file_name = QFileDialog::getOpenFileName(this,"Seleccionar un Archivo","/home/ferflo/Música");


    //////////////////////////////////////////////////////// Gets the selected path
    QByteArray array = file_name.toUtf8();
    char* path = array.data();

    //////////////////////////////////////////////////////// Generete the image
    MontarArchivo(Artistas, path);
    generar_imagen(Artistas);

    //////////////////////////////////////////////////////// Add all data into combo box
    QPixmap pix("/home/ferflo/Música/estructura.png");
    ui->img_estructura->setPixmap(pix);
    artista* cursor = Artistas->head;
    if(Artistas->head != NULL){
        if(cursor->next == Artistas->head){
            ui->ARTISTAS->addItem(cursor->nombre);
        }
        while(cursor->next != Artistas->head)
        {
            ui->ARTISTAS->addItem(cursor->nombre);
            cursor = cursor->next;
            if(cursor->next == Artistas->head){
                ui->ARTISTAS->addItem(cursor->nombre);
            }
        }
    }

}

void MainWindow::AgregarCancion(artistas *_artistas, char *_artista, char *_album, char *nombre, char *path, char *valuacion){
    albums* new_albums;
    canciones* new_canciones;
    artista* a_tmp = search_cd(_artistas->head,_artistas->head,_artista);
    if(a_tmp!=NULL){
          album* al = search_d(a_tmp->_albums->head,a_tmp->_albums->head,_album);
           if(al!=NULL){
                insert_back(al->_canciones,nombre,path,valuacion);
           }else{
               new_canciones = (canciones*)malloc(sizeof(canciones));
               new_canciones->head=NULL;
               insert_back(new_canciones,nombre,path,valuacion);
               insert_back_d(a_tmp->_albums,_album,new_canciones);
           }
    }else{
        new_albums = (albums*)malloc(sizeof(albums));
        new_albums->head = NULL;

        new_canciones = (canciones*)malloc(sizeof(canciones));
        new_canciones->head=NULL;
        insert_back(new_canciones,nombre,path,valuacion);
        insert_back_d(new_albums,_album,new_canciones);
        insert_back_cd(_artistas,new_albums,_artista);
    }
}

void MainWindow::MontarArchivo(artistas *_artistas, string path){
    stack* _stack = (stack*)malloc(sizeof(stack));
    _stack->head=NULL;
    int c;
    FILE *file;
    file = fopen(path.c_str(), "r");
    string tmp;
    char* TMP=(char*)malloc(sizeof(char)*100);
    if (file) {                                 //if file exist
        c = getc(file);                         //get the first char
        while (c != EOF){                       //while file have more chars
            if(c!=';'&&c!='_'&&c!=10){
                tmp += c;
            }else{
                strcpy(TMP, tmp.c_str());
                push(_stack,TMP);          //List insertion
                tmp = "";
                TMP = (char*)malloc(sizeof(char)*100);
            }
            c = getc(file);
        }
        fclose(file);                           //Close file
    }

    int pos = 0;
    char* _artista;
    char* _album;
    char* _nombre;
    char* _path;
    char* _val;
    pop(_stack);
    //////////////////////////////////////////////////////// Read all data and save it into vars
    while(_stack->head!=NULL){
        if(pos!=5){
            printf("stack %d: %s - ",pos,top(_stack)->data);
            if(pos==0){
                printf("_val\n");
                _val = top(_stack)->data;                   //valoracion
            }else if(pos==1){
                printf("_path\n");
                _path = top(_stack)->data;                  //path
            }else if(pos==2){
                printf("_nombre\n");
                _nombre = top(_stack)->data;                //name
            }else if(pos==3){
                printf("_album\n");
                _album = top(_stack)->data;                 //album
            }else if(pos==4){
                printf("_artista\n");
                _artista = top(_stack)->data;
                AgregarCancion(_artistas,_artista,_album,_nombre,_path,_val); //Inserts all information into the structure
            }
        }else{
            pos=-1;
        }
        pop(_stack);
        pos++;
    }
}

void MainWindow::on_ARTISTAS_currentTextChanged(const QString &arg1)    //Refresh Selected Artist
{
    if(arg1!=""){
        QByteArray artist = arg1.toUtf8();
        current_artist = search_cd(Artistas->head,Artistas->head,artist.data());

        ui->ALBUMS->clear();

        albums* _albums = current_artist->_albums;

        album* cursor = _albums->head;
        if(_albums->head != NULL){
            if(cursor->next == NULL){
                ui->ALBUMS->addItem(cursor->nombre);
            }
            while(cursor->next != NULL)
            {
                ui->ALBUMS->addItem(cursor->nombre);
                cursor = cursor->next;
                if(cursor->next == NULL){
                    ui->ALBUMS->addItem(cursor->nombre);
                }
            }
        }
    }
}

void MainWindow::on_ALBUMS_currentTextChanged(const QString &arg1)  //Refresh Selected Album
{
    if(arg1!=""){
        QByteArray albu = arg1.toUtf8();
        current_album = search_d(current_artist->_albums->head,current_artist->_albums->head,albu.data());

        ui->CANCIONES->clear();

        canciones* _canciones = current_album->_canciones;

        cancion* cursor = _canciones->head;
        if(_canciones->head != NULL){
            if(cursor->next == NULL){
                ui->CANCIONES->addItem(cursor->nombre);
            }
            while(cursor->next != NULL)
            {
                ui->CANCIONES->addItem(cursor->nombre);
                cursor = cursor->next;
                if(cursor->next == NULL){
                    ui->CANCIONES->addItem(cursor->nombre);
                }
            }
        }
    }
}

void MainWindow::on_CANCIONES_currentTextChanged(const QString &arg1)   //Refresh Selected Song
{
     if(arg1!=""){
            QByteArray song = arg1.toUtf8();
            current_song = search(current_album->_canciones->head,current_album->_canciones->head,song.data());

            QString a="";
            a += ui->ARTISTAS->currentText();
            a += "_";
            a += ui->ALBUMS->currentText();
            a += "_";
            a += ui->CANCIONES->currentText();
            ui->txt_Buscar->setText(a);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->playlist_type->currentText()=="Pila"){/////////////////////////////////////////// If its a stack
        if(top_song(stack_playlist)!=NULL){      /////////////////////////////////////////// gets the top
        current_song = top_song(stack_playlist);
        std::string name;
        name+= current_song->nombre;
        player-> setMedia(QUrl::fromLocalFile(current_song->path));
        player->play();                         /////////////////////////////////////////// and play it
        ui->txt_currentSong->setText(name.c_str());
        }else{
            QMessageBox::information(this,"!","Lo sentimos, la playlist actual se Acabo. :(");
            player->stop();
            ui->txt_currentSong->setText("");
        }
    }else if(ui->playlist_type->currentText()=="Cola"){//////////////////////////////////// If its a queue
        if(front_song(cola_playlist)!=NULL){           //////////////////////////////////// gets the front
        current_song = front_song(cola_playlist);
        std::string name;
        name+= current_song->nombre;
        player-> setMedia(QUrl::fromLocalFile(current_song->path));
        player->play();                                //////////////////////////////////// and play it
        ui->txt_currentSong->setText(name.c_str());
        }else{
            QMessageBox::information(this,"!","Lo sentimos, la playlist actual se Acabo. :(");
            player->stop();
            ui->txt_currentSong->setText("");
        }
    }else if(ui->playlist_type->currentText()=="Circular"){/////////////////////////////// If its a circular list
        if(front_d_song(circular_playlist)!=NULL){         /////////////////////////////// gets the front
        current_song = front_d_song(circular_playlist);
        std::string name;
        name+= current_song->nombre;
        player-> setMedia(QUrl::fromLocalFile(current_song->path));
        player->play();                                    /////////////////////////////// and play it
        ui->txt_currentSong->setText(name.c_str());
        }else{
            QMessageBox::information(this,"!","Lo sentimos, la playlist actual se Acabo. :(");
            player->stop();
            ui->txt_currentSong->setText("");
        }
    }
}

void MainWindow::on_pushButton_3_clicked()             //////////////////////////////////// refresh the current playlist
{
    if(ui->playlist_type->currentText()=="Pila"){
        pop_song(stack_playlist);
        MainWindow::on_pushButton_clicked();

        generar_imagen_stack(stack_playlist);
        QPixmap pix("/home/ferflo/Música/stack.png");
        ui->img_playlist->setPixmap(pix);
    }else if(ui->playlist_type->currentText()=="Cola"){
        deque_song(cola_playlist);
        MainWindow::on_pushButton_clicked();

        generar_imagen_queue(cola_playlist);
        QPixmap pix("/home/ferflo/Música/queue.png");
        ui->img_playlist->setPixmap(pix);
    }else if(ui->playlist_type->currentText()=="Circular"){
        current_song = search_d_song(circular_playlist->head,circular_playlist->head,current_song->nombre)->next->data;
        if(front_d_song(circular_playlist)!=NULL){
        std::string name;
        name+= current_song->nombre;
        player-> setMedia(QUrl::fromLocalFile(current_song->path));
        player->play();
        ui->txt_currentSong->setText(name.c_str());
        }else{
            QMessageBox::information(this,"!","Lo sentimos, la playlist actual se Acabo. :(");
            player->stop();
            ui->txt_currentSong->setText("");
        }
    }
}


void MainWindow::on_btn_Eliminar_clicked()
{
    QString temp= ui->txt_Buscar->text();
    QStringList parametros = temp.split("_");
    char* _artista=(char*)malloc(100);
    char* _album = (char*)malloc(100);
    char* _cancion = (char*)malloc(100);


    QString a = parametros[0];
    QByteArray ba=a.toLatin1();
    strcpy(_artista,ba.data());

    QString b = parametros[1];
    QByteArray bab=b.toLatin1();
    strcpy(_album,bab.data());

    QString c = parametros[2];
    QByteArray bac=c.toLatin1();
    strcpy(_cancion,bac.data());

    EliminarCancion(Artistas,_artista,_album,_cancion); //////////////////////////////////// search and delete the song
    ui->ARTISTAS->clear();
    ui->ALBUMS->clear();
    ui->CANCIONES->clear();


    generar_imagen(Artistas);
    QPixmap pix("/home/ferflo/Música/estructura.png"); //////////////////////////////////// refresh the structure

    ui->img_estructura->setPixmap(pix);
    artista* cursor = Artistas->head;
    if(Artistas->head != NULL){
        if(cursor->next == Artistas->head){
            ui->ARTISTAS->addItem(cursor->nombre);
        }
        while(cursor->next != Artistas->head)
        {
            ui->ARTISTAS->addItem(cursor->nombre);
            cursor = cursor->next;
            if(cursor->next == Artistas->head){
                ui->ARTISTAS->addItem(cursor->nombre);
            }
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->playlist_type->currentText()=="Circular"){
            current_song = search_d_song(circular_playlist->head,circular_playlist->head,current_song->nombre)->prev->data;
            if(front_d_song(circular_playlist)!=NULL){
            std::string name;
            name+= current_song->nombre;
            player-> setMedia(QUrl::fromLocalFile(current_song->path));
            player->play();
            ui->txt_currentSong->setText(name.c_str());
            }else{
                QMessageBox::information(this,"!","Lo sentimos, la playlist actual se Acabo. :(");
                player->stop();
                ui->txt_currentSong->setText("");
            }
        }
}

void MainWindow::on_playlist_type_currentTextChanged(const QString &arg1)
{

}

void MainWindow::on_playlist_type_currentIndexChanged(int index)
{

}

void MainWindow::on_actionTop_5_Canciones_2_triggered()
{
    artista* cursor = Artistas->head;
    album* al;
    cancion* canci;
    while(cursor->next != Artistas->head){
        al = cursor->_albums->head;
        while(al!=NULL){
            canci  = al->_canciones->head;
            while(canci!=NULL){
                printf(canci->nombre);
                printf("\n");
                insert_cancion_top(canciones_top5,canci);
                canci = canci->next;
            }
            al = al->next;
        }
        cursor=cursor->next;
        if(cursor->next==Artistas->head){
            al = cursor->_albums->head;
            while(al!=NULL){
                canci  = al->_canciones->head;
                while(canci!=NULL){
                    printf(canci->nombre);
                    printf("\n");
                    insert_cancion_top(canciones_top5,canci);
                    canci = canci->next;
                }
                al = al->next;
            }
        }
    }
    print(canciones_top5);
}
