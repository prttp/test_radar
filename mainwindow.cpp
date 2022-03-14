#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QwtPlotGrid *grid = new QwtPlotGrid(); //сетап сетки
    grid->setMajorPen( Qt::black, 0, Qt::SolidLine );
    grid->setMinorPen( Qt::gray, 0 , Qt::SolidLine );
    grid->enableX( true );
    grid->enableXMin( false );
    grid->enableY( true );
    grid->enableYMin( false );
    grid->attach(ui->mapQwtPlot );
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_uploadFileAction_triggered()
{
     QString str = QFileDialog::getOpenFileName(this, "Открыть файл", QCoreApplication::applicationDirPath(), "*.grid"); //диалоговое окно выбора файла
     if (m_GMap.uploadFile(str)) { //при успешном открытии:
     QwtPlotSpectrogram *spectrogram = new QwtPlotSpectrogram; //карта-спектрограмма
     spectrogram->setColorMap( new ColorMap() );
     spectrogram->setData( new RasterData(&m_GMap) );
     spectrogram->attach(ui->mapQwtPlot);
     ui->mapQwtPlot->setAxisScaleDraw(QwtPlot::xBottom, new QConversionScaleDraw(m_GMap.getDeltaY(),m_GMap.getYMin()) ); // изменение отображаемой шкалы осей
     ui->mapQwtPlot->setAxisScaleDraw(QwtPlot::yLeft, new QConversionScaleDraw(m_GMap.getDeltaX(),m_GMap.getXMin()) );
     const QwtInterval zInterval = spectrogram->data()->interval( Qt::ZAxis ); //построение цветовой шкалы в правой части виджета
     QwtScaleWidget* rightAxis = ui->mapQwtPlot->axisWidget(QwtAxis::YRight);
     rightAxis->setColorBarEnabled( true );
     rightAxis->setColorBarWidth( 40 );
     rightAxis->setColorMap( zInterval, new ColorMap() );
     ui->mapQwtPlot->setAxisScale( QwtAxis::YRight, zInterval.minValue(), zInterval.maxValue() );
     ui->mapQwtPlot->setAxisVisible( QwtAxis::YRight );
     QwtPlotMagnifier* magnifier = new QwtPlotMagnifier(ui->mapQwtPlot->canvas()); //зум
     magnifier->setAxisEnabled( QwtAxis::YRight, false );
     QwtPlotPanner* panner = new QwtPlotPanner(ui->mapQwtPlot->canvas()); // перетаскивание
     panner->setAxisEnabled( QwtAxis::YRight, false );
     MyPicker* picker = new MyPicker(ui->mapQwtPlot->canvas(),spectrogram->data()); //кастомный пикер
     ui->mapQwtPlot->replot();
     ui->uploadFileAction->setDisabled(true);
     }

}


void MainWindow::on_closeAction_triggered()
{
    this->close();
}


void MainWindow::on_aboutAction_triggered()
{
    QMessageBox::about(this, "О программе", "Тестовое задание Мишин");
}

