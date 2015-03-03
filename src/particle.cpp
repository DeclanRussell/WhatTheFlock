#include "include/particle.h"
#include <ngl/VAOPrimitives.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>

particle::particle()
{
    m_pos.set(ngl::Vec3(0.0));
    m_vel.set(ngl::Vec3(0.0));
    m_acc.set(ngl::Vec3(0.0));
}
//---------------------------------------------------------------------------------
particle::particle(ngl::Vec3 _pos){
    m_pos.set(_pos);
    m_vel.set(ngl::Vec3(0));
    m_acc.set(ngl::Vec3(0.0));
}
//---------------------------------------------------------------------------------
void particle::draw(ngl::TransformStack* _tranStack, ngl::Camera* _cam){
    _tranStack->pushTransform();
    {
        _tranStack->setPosition(m_pos.m_x,m_pos.m_y,m_pos.m_z);
        _tranStack->setScale(0.1,0.1,0.1);
        loadMatriciesToShader(_tranStack,_cam);
        ngl::VAOPrimitives::instance()->draw("sphere");
    }
    _tranStack->popTransform();

}
//---------------------------------------------------------------------------------
void particle::loadMatriciesToShader(ngl::TransformStack *_tranStack, ngl::Camera* _cam){
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["nglToonShader"]->use();
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;
    M=_tranStack->getCurrAndGlobal().getMatrix();
    MV=  M*_cam->getViewMatrix();
    MVP= M*_cam->getVPMatrix();
    normalMatrix=MV;
    normalMatrix.inverse();
    shader->setShaderParamFromMat4("MVP",MVP);
    shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
}
//---------------------------------------------------------------------------------

