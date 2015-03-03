#include "flockingsim.h"
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <boost/foreach.hpp>
#include <iostream>


//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
const static float ZOOM=0.5;

flockingSim::flockingSim(const QGLFormat _format, QWidget *_parent) : OpenGLWidget(_format,_parent)
{
    m_numParticles=100;
}
//--------------------------------------------------------------------------------------------------------------
flockingSim::~flockingSim(){
}
//--------------------------------------------------------------------------------------------------------------
void flockingSim::initializeGL(){
    OpenGLWidget::initializeGL();

    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["nglToonShader"]->use();
    shader->setShaderParam4f("Colour",1,1,0,1);
    shader->setShaderParam3f("lightPos",1,1,1);
    shader->setShaderParam4f("Colour",0,255,255,1.0);

    //set the zoom so we're not so close to our particles
    m_modelPos.m_z = 0;
    ngl::Transformation trans;
    ngl::Mat4 final;
    // add the translations
    final.m_m[3][0] = m_modelPos.m_x;
    final.m_m[3][1] = m_modelPos.m_y;
    final.m_m[3][2] = m_modelPos.m_z;
    // set this in the TX stack
    trans.setMatrix(final);
    m_transformStack->setGlobal(trans);

    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    prim->createSphere("sphere",1.0,40);
    startTimer(0);
}
//--------------------------------------------------------------------------------------------------------------
void flockingSim::paintGL(){
    OpenGLWidget::paintGL();

    ngl::Transformation trans;
    ngl::Mat4 final;
    // add the translations
    final.m_m[3][0] = m_modelPos.m_x;
    final.m_m[3][1] = m_modelPos.m_y;
    final.m_m[3][2] = m_modelPos.m_z;
    // set this in the TX stack
    trans.setMatrix(final);
    m_transformStack->setGlobal(trans);

    if(!m_particleList.empty()){
        BOOST_FOREACH(particle *p, m_particleList){
            p->draw(m_transformStack,m_cam);
        }
    }
}
//--------------------------------------------------------------------------------------------------------------
void flockingSim::resizeGL(const int _w, const int _h){
    OpenGLWidget::resizeGL(_w,_h);
}
//----------------------------------------------------------------------------------------------------------------------
void flockingSim::loadMatriciesToShader(){
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["nglToonShader"]->use();
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat4 M;
    M=m_transformStack->getCurrentTransform().getMatrix();
    MV= m_transformStack->getCurrAndGlobal().getMatrix()*m_cam->getViewMatrix();
    MVP=MV*m_cam->getProjectionMatrix() ;
    shader->setUniform("MVP",MVP);
    shader->setUniform("MV",MV);
}
//----------------------------------------------------------------------------------------------------------------------
void flockingSim::createParticles(){
    if(!m_particleList.empty()){
        for(unsigned int i=0;i<m_particleList.size();i++){
            delete m_particleList[i];
            m_particleList.clear();
        }
    }
    int x=-sqrt(m_numParticles)/2,y=-sqrt(m_numParticles)/2;
    while(m_particleList.size()<m_numParticles){
        m_particleList.push_back(new particle(ngl::Vec3(x,y,-10)));
        x++;
        if(x>sqrt(m_numParticles)/2){
           y++;
           x=-sqrt(m_numParticles)/2;
        }
    }
    std::cout<<"num particles is: "<<m_particleList.size()<<std::endl;
    m_flockHash.createHashTable(m_particleList);
    std::cout<<"hash complete"<<std::endl;
    // start the clock for our updates
    m_flockSolver.startClock();
}
//----------------------------------------------------------------------------------------------------------------------
void flockingSim::timerEvent(QTimerEvent *){
    if(m_particleList.size()>0){
        m_flockHash.createHashTable(m_particleList);
        std::vector<particle*> neighbourParticles;
        BOOST_FOREACH(particle *p, m_particleList){
            neighbourParticles = m_flockHash.getNeighbours(p,30);
            m_flockSolver.calcFlock(p,neighbourParticles);
        }
        m_flockSolver.startClock();
//        ngl::Vec3 pos = m_particleList[0]->getVel();
//        std::cout<<"["<<pos.m_x<<","<<pos.m_y<<","<<pos.m_z<<"]"<<std::endl;
    }
    updateGL();
}
//----------------------------------------------------------------------------------------------------------------------
void flockingSim::mousePressEvent(QMouseEvent *_event){
    if(_event->button() == Qt::LeftButton){
        ngl::Mat4 MV;
        ngl::Mat4 MVP;
        MV= m_transformStack->getCurrAndGlobal().getMatrix()*m_cam->getViewMatrix();
        MVP=MV*m_cam->getProjectionMatrix() ;
        ngl::Mat4 invProjMat = MVP.inverse();
        ngl::Vec4 Pos((2.0*(_event->x()/(float)width()))-1.0,
                      (2.0*((height() - _event->y())/(float)height()))-1.0,0.86,1.0);
        Pos =  Pos * invProjMat;
        Pos.m_x /= Pos.m_w;
        Pos.m_y /= Pos.m_w;
        Pos.m_z /= Pos.m_w;
        m_flockSolver.setGoalPos(ngl::Vec3(Pos.m_x,Pos.m_y,0));
    }
}
//----------------------------------------------------------------------------------------------------------------------
void flockingSim::mouseMoveEvent(QMouseEvent *_event){
    if(_event->buttons() == Qt::LeftButton){
        ngl::Mat4 MV;
        ngl::Mat4 MVP;
        MV= m_transformStack->getCurrAndGlobal().getMatrix()*m_cam->getViewMatrix();
        MVP=MV*m_cam->getProjectionMatrix() ;
        ngl::Mat4 invProjMat = MVP.inverse();
        ngl::Vec4 Pos((2.0*(_event->x()/(float)width()))-1.0,
                      (2.0*((height() - _event->y())/(float)height()))-1.0,0.86,1.0);
        Pos =  Pos * invProjMat;
        Pos.m_x /= Pos.m_w;
        Pos.m_y /= Pos.m_w;
        Pos.m_z /= Pos.m_w;
        m_flockSolver.setGoalPos(ngl::Vec3(Pos.m_x,Pos.m_y,0));
    }
}
//----------------------------------------------------------------------------------------------------------------------
void flockingSim::wheelEvent(QWheelEvent *_event)
{
    // check the diff of the wheel position (0 means no change)
    if(_event->delta() > 0)
    {
        m_modelPos.m_z+=ZOOM;
    }
    else if(_event->delta() <0 )
    {
        m_modelPos.m_z-=ZOOM;
    }
    updateGL();
}

