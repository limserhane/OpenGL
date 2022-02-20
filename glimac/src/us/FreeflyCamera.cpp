#include <us/FreeflyCamera.hpp>

FreeflyCamera::FreeflyCamera(float pFov, float pAspect, float pNear, float pFar):
    m_Position(0, 1.7f, 5),
    m_fPhi(glm::pi<float>()),
    m_fTheta(0),
    projection(perspective(pFov, pAspect, pNear, pFar))
{
    computeDirectionVectors();
}

void FreeflyCamera::setLeftMove(float t)
{
    m_PositionVel.x = t;
}

void FreeflyCamera::setFrontMove(float t)
{
    m_PositionVel.z = t;
}

void FreeflyCamera::setUpMove(float t)
{
    m_PositionVel.y = t;
}

void FreeflyCamera::setLeftRotation(float degrees)
{
    m_fPhiVel = glm::radians(degrees);
}

void FreeflyCamera::setUpRotation(float degrees)
{
    m_fThetaVel = glm::radians(degrees);
}

void FreeflyCamera::update()
{
    m_Position += m_PositionVel.x * m_LeftVector;
    m_Position += m_PositionVel.y * m_UpVector;
    m_Position += m_PositionVel.z * m_FrontVector;
    m_fPhi += m_fPhiVel;
    m_fTheta += m_fThetaVel;
    computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const
{
    return glm::lookAt(
        m_Position,
        m_Position + m_FrontVector,
        m_UpVector
    );
}

void FreeflyCamera::computeDirectionVectors()
{
    m_FrontVector = glm::vec3(
        glm::cos(m_fTheta) * glm::sin(m_fPhi),
        glm::sin(m_fTheta),
        glm::cos(m_fTheta) * glm::cos(m_fPhi)
    );

    m_LeftVector = glm::vec3(
        glm::sin(m_fPhi + glm::half_pi<float>()),
        0,
        glm::cos(m_fPhi + glm::half_pi<float>())
    );

    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

mat4 FreeflyCamera::getProjectionMatrix() const
{
    return projection;
}