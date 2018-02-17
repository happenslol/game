#include <texture.hpp>

Texture::Texture(const std::string& path) {
    unsigned char* data = stbi_load(
        path.c_str(),
        &this->width, &this->height,
        &this->channels, 0
    );

    if (!data) {
        printf("failed to load image %s\n", path);
        return;
    }

    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB,
        this->width, this->height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, data
    );

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &this->id);
}

