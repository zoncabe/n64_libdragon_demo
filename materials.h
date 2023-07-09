#ifndef MATERIALS_H
#define MATERIALS_H

#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>


void setup_textures(GLuint textures[], sprite_t *sprites[], const char *texture_path[], int texture_number) {

    for (uint32_t i = 0; i < texture_number; i++){

        sprites[i] = sprite_load(texture_path[i]);
    }

    glGenTextures(texture_number, textures);

    #if 0
    GLenum min_filter = GL_LINEAR_MIPMAP_LINEAR;
    #else
    GLenum min_filter = GL_LINEAR;
    #endif

    for (uint32_t i = 0; i < texture_number; i++){

        glBindTexture(GL_TEXTURE_2D, textures[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

        glSpriteTextureN64(GL_TEXTURE_2D, sprites[i], &(rdpq_texparms_t){.s.repeats = REPEAT_INFINITE, .t.repeats = REPEAT_INFINITE});
    }

}

void generate_s64_texture(s64Texture* tex, GLuint* store, sprite_t* texture)
{
    // Create the texture buffer 
    glGenTextures(1, store);
    glBindTexture(GL_TEXTURE_2D, *store);

    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tex->wraps);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tex->wrapt);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex->filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex->filter);

    glSpriteTextureN64(GL_TEXTURE_2D, texture, NULL);
}


#endif