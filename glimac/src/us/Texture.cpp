#include <us/Texture.hpp>

#include <iostream>
#include <sstream>

Texture::Texture(const glimac::Image* image):
    to(0)
{
	glGenTextures(1, &to);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, to);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
Texture::~Texture()
{
    glDeleteTextures(1, &to);
}

void Texture::bind(unsigned slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, to);
}

TexturePtr loadTexture(const char* filepath)
{
	auto image = glimac::loadImage(filepath);

	if(!image)
	{
		std::stringstream error;
		error << "Texture could not be loaded at " << filepath;
        std::cerr << error.str() << std::endl;
		throw new std::invalid_argument(error.str());
	}

	return std::make_shared<Texture>(image.get());
}