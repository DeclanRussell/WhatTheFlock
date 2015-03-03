#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGLFormat format;
    format.setVersion(4,1);
    format.setProfile(QGLFormat::CoreProfile);
    m_flockingSim = new flockingSim(format,this);
    ui->gridLayout->addWidget(m_flockingSim,0,0,1,1);
    
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_flockingSim;
}

void MainWindow::on_s_createParticlesBtn_clicked()
{
    m_flockingSim->createParticles();
}

void MainWindow::on_s_numParticlesSpn_valueChanged(int arg1)
{
    m_flockingSim->setNumParticles(arg1);
}

void MainWindow::on_s_sepSldr_sliderMoved(int position)
{
    m_flockingSim->m_flockSolver.setSeperationWeight((float)position/100.0);
    std::cout<<"sep"<<(float)position/100.0<<std::endl;
}

void MainWindow::on_s_alignSldr_sliderMoved(int position)
{
    m_flockingSim->m_flockSolver.setAlignmentWeight((float)position/100.0);
    std::cout<<"align"<<(float)position/100.0<<std::endl;
}

void MainWindow::on_s_cohesionSldr_sliderMoved(int position)
{
    m_flockingSim->m_flockSolver.setCohesionWeight((float)position/100.0);
    std::cout<<"cohesion"<<(float)position/100.0<<std::endl;
}

void MainWindow::on_s_goalSldr_sliderMoved(int position)
{
    m_flockingSim->m_flockSolver.setGoalWeight((float)position/100.0);
    std::cout<<"goal"<<(float)position/100.0<<std::endl;
}

void MainWindow::on_s_velocitySpn_valueChanged(double arg1)
{
    m_flockingSim->m_flockSolver.setVelocityScaler(arg1);
}
