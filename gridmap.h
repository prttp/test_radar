#ifndef GRIDMAP_H
#define GRIDMAP_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <qwt_matrix_raster_data.h>
#include <qwt_interval.h>
#include <qwt_raster_data.h>
class GridMap : public QObject
{
    Q_OBJECT
    char m_ID[8]; //Идентификатор формата файла “GMAMFSXY”
    unsigned short m_NX; //Число отсчетов по координате Х
    unsigned short m_NY; //Число отсчетов по координате Y
    float m_XMin; //Минимальное значение координаты Х, м
    float m_YMin; //Минимальное значение координаты Y, м
    float m_deltaX; //Шаг по координате Х, м
    float m_deltaY; //Шаг по координате Y, м
    double m_LatOrigin; //Значение широты начала системы координат, град
    double m_LonOrogin; //Значение долготы начала системы координат, град
    float m_H; //Высота «съемки»
    float m_TMin; //Минимальное значение величины АМПЗ
    float m_TMax; //Максимальное значение величины АМПЗ
    QVector<float> m_Tij; //Значения АМПЗ в точке с координатами  .


public:
    explicit GridMap(QObject *parent = nullptr);
    bool uploadFile(QString str);//метод открытия файла
    QVector<float> getData() const{return m_Tij;};
    int getNY() const {return m_NY;};
    int getNX() const {return m_NX;};
    float getMagMin() const {return m_TMin;};
    float getMagMax() const {return m_TMax;};
    float getDeltaY() const {return m_deltaY;};
    float getYMin() const {return m_YMin;};
    float getDeltaX() const {return m_deltaX;};
    float getXMin() const {return m_XMin;};
signals:

};

#endif // GRIDMAP_H
