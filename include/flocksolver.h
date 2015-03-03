#ifndef FLOCKSOLVER_H
#define FLOCKSOLVER_H

#include "particle.h"

class flockSolver
{
public:
    //---------------------------------------------------------------------------------
    flockSolver();
    //---------------------------------------------------------------------------------
    /// @brief calculate and update the particles with the rules of flocking systems
    /// @param _subject - the particle we are doing our calculations for
    /// @param _particleList - the particles we are testing our subject against
    //---------------------------------------------------------------------------------
    void calcFlock(particle* _subject, std::vector<particle*> _particleList);
    //---------------------------------------------------------------------------------
    /// @brief a mutator for our goal postion
    /// @param _pos - the position we wish to set our goal
    //----------------------------------------------------------------------------------------------------------------------
    inline void setGoalPos(ngl::Vec3 _pos){m_goalPos = _pos;}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a mutator to set our weight
    /// @param _weight - the weight we wish to change our member to
    //----------------------------------------------------------------------------------------------------------------------
    inline void setSeperationWeight(float _weight){m_seperationWeight = _weight;}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a mutator to set our weight
    /// @param _weight - the weight we wish to change our member to
    //----------------------------------------------------------------------------------------------------------------------
    inline void setAlignmentWeight(float _weight){m_alignWeight = _weight;}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a mutator to set our weight
    /// @param _weight - the weight we wish to change our member to
    //----------------------------------------------------------------------------------------------------------------------
    inline void setCohesionWeight(float _weight){m_cohesionWeight = _weight;}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a mutator to set our weight
    /// @param _weight - the weight we wish to change our member to
    //----------------------------------------------------------------------------------------------------------------------
    inline void setGoalWeight(float _weight){m_goalWeight = _weight;}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a function to start our update clock
    //----------------------------------------------------------------------------------------------------------------------
    inline void startClock(){m_startTime = clock();}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a mutator to set our velocity scaler
    //----------------------------------------------------------------------------------------------------------------------
    inline void setVelocityScaler(float _vel){m_velocity = _vel;}
    //----------------------------------------------------------------------------------------------------------------------
private:
    //---------------------------------------------------------------------------------
    /// @brief the weight of the overall effect the seperation calculation has
    //---------------------------------------------------------------------------------
    float m_seperationWeight;
    //---------------------------------------------------------------------------------
    /// @brief the weight of the overall effect the alignment calculation has
    //---------------------------------------------------------------------------------
    float m_alignWeight;
    //---------------------------------------------------------------------------------
    /// @brief the weight of the overall effect the cohesion calculation has
    //---------------------------------------------------------------------------------
    float m_cohesionWeight;
    //---------------------------------------------------------------------------------
    /// @brief a member to hold the location of our goal
    //---------------------------------------------------------------------------------
    ngl::Vec3 m_goalPos;
    //---------------------------------------------------------------------------------
    /// @brief a member to hold the weight of influence our goal has
    //---------------------------------------------------------------------------------
    float m_goalWeight;
    //---------------------------------------------------------------------------------
    /// @brief An int to hold our update time
    //---------------------------------------------------------------------------------
    float m_startTime;
    //---------------------------------------------------------------------------------
    /// @brief a float to hold our velocity scaler
    //---------------------------------------------------------------------------------
    float m_velocity;
};

#endif // FLOCKSOLVER_H
