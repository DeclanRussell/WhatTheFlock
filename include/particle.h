#ifndef PARTICLE_H
#define PARTICLE_H

#include <ngl/Vec3.h>
#include <ngl/TransformStack.h>
#include <ngl/Camera.h>

class particle
{
public:
    //---------------------------------------------------------------------------------
    /// @brief default constructor sets all the members to 0
    //---------------------------------------------------------------------------------
    particle();
    //---------------------------------------------------------------------------------
    /// @brief contructor for setting position of the particle
    /// @param _pos the position of the particle you are creating
    //---------------------------------------------------------------------------------
    particle(ngl::Vec3 _pos);
    //---------------------------------------------------------------------------------
    /// @brief A accessor to return the position of the particle
    /// @return The position of the particle
    inline ngl::Vec3 getPos(){return m_pos;}
    //---------------------------------------------------------------------------------
    /// @brief A accessor to return the velocity of the particle
    /// @return The velocity of the particle
    inline ngl::Vec3 getVel(){return m_vel;}
    //---------------------------------------------------------------------------------
    /// @brief A accessor to return the acceleration of the particle
    /// @return The acceleration of the particle
    inline ngl::Vec3 getAcc(){return m_acc;}
    //---------------------------------------------------------------------------------
    /// @brief a mutator to set the postion of the particle
    /// @param _x the x pos of the particle
    /// @param _y the y pos of the particle
    /// @param _z the z pos of the particle
    inline void setPos(float _x, float _y, float _z){m_pos.set(_x,_y,_z);}
    //---------------------------------------------------------------------------------
    /// @brief a mutator to set the velocity of the particle
    /// @param _x the x coordinate of the velocity
    /// @param _y the y coordinate of the velocity
    /// @param _z the z coordinate of the velocity
    inline void setVel(float _x, float _y, float _z){m_vel.set(_x,_y,_z);}
    //---------------------------------------------------------------------------------
    /// @brief a mutator to set the acceleration of the particle
    /// @param _x the x coordinate of the acceleration
    /// @param _y the y coordinate of the acceleration
    /// @param _z the z coordinate of the acceleration
    inline void setAcc(float _x, float _y, float _z){m_acc.set(_x,_y,_z);}
    //---------------------------------------------------------------------------------
    /// @brief a function to draw our particle on the screen
    //---------------------------------------------------------------------------------
    void draw(ngl::TransformStack *_tranStack, ngl::Camera *_cam);
    //---------------------------------------------------------------------------------

private:
    //---------------------------------------------------------------------------------
    /// @brief A function to load our transforms to our shader, called when drawing the particle
    //---------------------------------------------------------------------------------
    void loadMatriciesToShader(ngl::TransformStack* _tranStack, ngl::Camera *_cam);
    //---------------------------------------------------------------------------------
    /// @brief A vec 3 to hold the position of the particle
    ngl::Vec3 m_pos;
    //---------------------------------------------------------------------------------
    /// @brief A vec 3 to hold the velocity of the particle
    ngl::Vec3 m_vel;
    //---------------------------------------------------------------------------------
    /// @brief A vec 3 to hold the acceleration of the particle
    ngl::Vec3 m_acc;
    //---------------------------------------------------------------------------------


};

#endif // PARTICLE_H
