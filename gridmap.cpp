#include "gridmap.h"

GridMap::GridMap(QObject *parent) : QObject(parent)
{

}
bool GridMap::uploadFile(QString str) {
    QFile file(str);
    if (file.open(QIODevice::ReadOnly)) { //открытие файла
    QDataStream dsfile(&file);  //чтение данных из потока
    dsfile.readRawData(&m_ID[0],sizeof (m_ID));
    dsfile.readRawData(reinterpret_cast<char*>(&m_NX),sizeof(m_NX));
    dsfile.readRawData(reinterpret_cast<char*>(&m_NY),sizeof(m_NY));
    dsfile.readRawData(reinterpret_cast<char*>(&m_XMin),sizeof(m_XMin));
    dsfile.readRawData(reinterpret_cast<char*>(&m_YMin),sizeof(m_YMin));
    dsfile.readRawData(reinterpret_cast<char*>(&m_deltaX),sizeof(m_deltaX));
    dsfile.readRawData(reinterpret_cast<char*>(&m_deltaY),sizeof(m_deltaY));
    dsfile.readRawData(reinterpret_cast<char*>(&m_LatOrigin),sizeof(m_LatOrigin));
    dsfile.readRawData(reinterpret_cast<char*>(&m_LonOrogin),sizeof(m_LonOrogin));
    dsfile.readRawData(reinterpret_cast<char*>(&m_H),sizeof(m_H));
    dsfile.readRawData(reinterpret_cast<char*>(&m_TMin),sizeof(m_TMin));
    dsfile.readRawData(reinterpret_cast<char*>(&m_TMax),sizeof(m_TMax));
    dsfile.skipRawData(24);
    m_Tij.resize(m_NX*m_NY); //формирование контейнера с измерениями
    for (int i = 0; i<m_Tij.size(); i++) {
         dsfile.readRawData(reinterpret_cast<char*>(&m_Tij[i]),sizeof(m_Tij[i]));
            }
    return true;
        }
    return false;
};

