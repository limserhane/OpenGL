#pragma once

#include <glimac/glm.hpp>
#include <memory>

using namespace glm;

class TrackballCamera
{
public:
    TrackballCamera(float pFov, float pAspect, float pNear, float pFar);
  
    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

    mat4 getViewMatrix() const;
    mat4 getProjectionMatrix() const;
    

private :
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

    mat4 projection;
};
using TrackballCameraPtr = std::shared_ptr<TrackballCamera>;