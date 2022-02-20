#pragma once

#include <GL/glew.h>
#include <glimac/Image.hpp>

#include <memory>

class Texture
{
private:
    GLuint to;
public:
    Texture(const glimac::Image* image);
    ~Texture();

    void bind(unsigned slot) const;
};
using TexturePtr = std::shared_ptr<Texture>;

TexturePtr loadTexture(const char* filepath);