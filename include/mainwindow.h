#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "flockingsim.h"

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
    void on_s_createParticlesBtn_clicked();

    void on_s_numParticlesSpn_valueChanged(int arg1);

    void on_s_sepSldr_sliderMoved(int position);

    void on_s_alignSldr_sliderMoved(int position);

    void on_s_cohesionSldr_sliderMoved(int position);

    void on_s_goalSldr_sliderMoved(int position);

    void on_s_velocitySpn_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    flockingSim *m_flockingSim;
};

#endif // MAINWINDOW_H
