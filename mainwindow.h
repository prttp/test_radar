#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QwtPlot>
#include <QFileDialog>
#include "gridmap.h"
#include "rasterdata.h"
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <QwtAxisId>
#include <QwtScaleWidget>
#include <QwtAxis>
#include <QwtPlotGrid>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    GridMap m_GMap;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_uploadFileAction_triggered();

    void on_closeAction_triggered();

    void on_aboutAction_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
