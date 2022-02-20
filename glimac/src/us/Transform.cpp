#include <us/Transform.hpp>

Transform::Transform():
    position(vec3(0, 0, 0)),
    scale(vec3(1, 1, 1)),
    rotation(vec3(0, 0, 0))
{}

mat4 Transform::getModelMatrix() const
{
    mat4 model(1.f);

    model = glm::translate(model, position);
    model = glm::rotate(model, radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);

    return model;
}
