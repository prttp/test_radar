#ifndef RASTERDATA_H
#define RASTERDATA_H
#include <qwt_raster_data.h>
#include <qwt_color_map.h>
#include <qwt_interval.h>
#include <QwtMatrixRasterData>
#include "gridmap.h"
#include <QwtScaleDraw>
#include <QwtText>
#include <QwtPlotPicker>
#include <QwtPickerDragPointMachine>
#include <QwtPlotCanvas>
#include <QwtPlot>
#include <QPen>
#include <QString>
class RasterData: public QwtMatrixRasterData //данные для построения карты
{
public:
    RasterData(const GridMap* gm)
    {

        QVector<float> temp(gm->getData());
        QVector< double > values;
        for (auto& i:temp) { //float =>double
            values.append(static_cast<double>(i));
        };
        const int numColumns = gm->getNY();
        setValueMatrix( values, numColumns );
        setInterval( Qt::XAxis,  QwtInterval(0, gm->getNY()) ); //интервалы отображения
        setInterval( Qt::YAxis,  QwtInterval(0, gm->getNX()) );
        setInterval( Qt::ZAxis, QwtInterval(gm->getMagMin(), gm->getMagMax() ) );
        this->setResampleMode(QwtMatrixRasterData::ResampleMode::BilinearInterpolation); //интерполяция

    }
};

class ColorMap : public QwtLinearColorMap //карта цветов для построения
{
  public:
    ColorMap()
        : QwtLinearColorMap( Qt::darkBlue, Qt::darkRed )
    {
        addColorStop( 0.2, Qt::blue );
        addColorStop( 0.4, Qt::cyan );
        addColorStop( 0.6, Qt::yellow );
        addColorStop( 0.8, Qt::red );
    }
};
class QConversionScaleDraw : public QwtScaleDraw //конвертер шкалы оси для отображения в метрах
{
    double m_conversionFactor;
    double m_handicap;
public:

    explicit QConversionScaleDraw(double conversionFactor, double handicap)
    : m_conversionFactor(conversionFactor), m_handicap(handicap)
    {

    };

    virtual QwtText label(double value) const override
    {
        return QwtScaleDraw::label((value * m_conversionFactor)+m_handicap); // множитель - шаг измерения, гандикап - начальная координата
    };


};

class MyPicker: public QwtPlotPicker //пикер для отображения значения АМПЗ в точке, куда указывает курсор
{QwtRasterData* m_data;
public:
    MyPicker(QWidget* pCanvas, QwtRasterData* data): QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand, QwtPicker::ActiveOnly, pCanvas), m_data(data)
    {
        this->setRubberBandPen(QPen(QColor( Qt::black )) );
        this->setTrackerPen( QPen(QColor( Qt::black )) );
        this->setStateMachine( new QwtPickerTrackerMachine() );

    }

  protected:
    virtual QwtText trackerTextF(const QPointF &pos) const
    {
      QString temp;
      temp.setNum(m_data->value(pos.x(),pos.y()));
      QwtText text(temp);
      return text;
    }

};



#endif // RASTERDATA_H
