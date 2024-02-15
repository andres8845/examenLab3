#ifndef CTUNES_H
#define CTUNES_H
#include <fstream>
#include "Generos.h"
#include "QString"
#include "QFile"

using namespace std;

class CTunes
{
public:
    CTunes();

    int getCodigo(long offset);
    void addSong(QString nombre,QString cantante,Generos::Genero generoCantante,double precio,QString duracion);
    QString infoSong(int codeSong);

    struct songFormat{
        int code;
        QString song;
        QString singer;
        QString duracion;
        QString gender;
        double price;
        int stars;
        int reviews;
    };
};



#endif // CTUNES_H
