#include "include/flocksolver.h"
#include <boost/foreach.hpp>

flockSolver::flockSolver()
{
    m_seperationWeight = 0.1;
    m_alignWeight = 0.1;
    m_cohesionWeight = 0.1;
    m_goalPos = ngl::Vec3(0);
    m_goalWeight = 1.0;
    m_velocity = 3.0;
}
//----------------------------------------------------------------------------------------------------------------------
void flockSolver::calcFlock(particle *_subject, std::vector<particle *> _particleList){
    ngl::Vec3 seperation = ngl::Vec3(0);
    ngl::Vec3 alignment = ngl::Vec3(0);
    ngl::Vec3 cohesion = ngl::Vec3(0);
    ngl::Vec3 dist(0);
    int numSamples = 0;
    BOOST_FOREACH(particle *p, _particleList){
        if(p!=_subject){
            if(_subject->getPos()!=p->getPos()){
                dist = _subject->getPos() - p->getPos();

                seperation += dist/(dist.length()*dist.length());
                alignment += p->getVel()-_subject->getVel();
                cohesion += p->getPos();
                numSamples++;

            }
        }
    }
    if(numSamples!=0){
        cohesion/=numSamples;
        cohesion-= _subject->getPos();
    }
//    std::cout<<"cohesion direction: "<<cohesion.m_x<<","<<cohesion.m_y<<","<<cohesion.m_z<<std::endl;
    ngl::Vec3 goalDir = m_goalPos - _subject->getPos();
    if (goalDir.length()!=0)
        goalDir.normalize();
    ngl::Vec3 newVel = (seperation * m_seperationWeight) + (alignment * m_alignWeight) + (cohesion * m_cohesionWeight) + (goalDir * m_goalWeight);
    if(newVel.length()!=0){
        newVel.normalize();
        newVel*=m_velocity;
        float timeStep = (clock() - m_startTime) / (float)CLOCKS_PER_SEC;
        newVel *= timeStep;
        _subject->setVel(newVel.m_x,newVel.m_y,newVel.m_z);
    }
//    std::cout<<m_seperationWeight<<std::endl;
//    std::cout<<m_alignWeight<<std::endl;
//    std::cout<<m_cohesionWeight<<std::endl;
//    std::cout<<m_goalWeight<<std::endl;
//    std::cout<<std::endl;
//    std::cout<<"["<<newVel.m_x<<","<<newVel.m_y<<","<<newVel.m_z<<"]"<<std::endl;
    ngl::Vec3 newPos = _subject->getPos() + _subject->getVel();
    _subject->setPos(newPos.m_x,newPos.m_y,newPos.m_z);
}


