#include "us/TrackballCamera.hpp"

using namespace glm;

TrackballCamera::TrackballCamera(float pFov, float pAspect, float pNear, float pFar):
    m_fDistance(5),
    m_fAngleX(0),
    m_fAngleY(0),
    projection(perspective(pFov, pAspect, pNear, pFar))
{}
  
void TrackballCamera::moveFront(float delta)
{
    m_fDistance -= delta;
}

void TrackballCamera::rotateLeft(float degrees)
{
    m_fAngleY += degrees;
}

void TrackballCamera::rotateUp(float degrees)
{
    m_fAngleX += degrees;
}

mat4 TrackballCamera::getViewMatrix() const
{
    mat4 viewMatrix = mat4(1.f);

    viewMatrix = translate(viewMatrix, vec3(0.f, 0.f, - m_fDistance));

    viewMatrix = rotate(viewMatrix, - radians(m_fAngleX), vec3(1.f, 0.f, 0.f));
    viewMatrix = rotate(viewMatrix, - radians(m_fAngleY), vec3(0.f, 1.f, 0.f));

    return viewMatrix;
}

mat4 TrackballCamera::getProjectionMatrix() const
{
    return projection;
}