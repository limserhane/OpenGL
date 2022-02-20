#pragma once

#include <glimac/glm.hpp>

#include <memory>

using namespace glm;

class FreeflyCamera
{
public :
    FreeflyCamera(float pFov, float pAspect, float pNear, float pFar);

    void setLeftMove(float t);
    void setFrontMove(float t);
    void setUpMove(float t);

    void setLeftRotation(float degrees);
    void setUpRotation(float degrees);

    mat4 getViewMatrix() const;
    mat4 getProjectionMatrix() const;

    void update();

private :
    void computeDirectionVectors();

    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;

    glm::vec3 m_PositionVel;
    float m_fPhiVel;
    float m_fThetaVel;

    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

    mat4 projection;
};
using FreeflyCameraPtr = std::shared_ptr<FreeflyCamera>;
