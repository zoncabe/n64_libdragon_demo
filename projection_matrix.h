#ifndef PROJECTION_MATRIX_H
#define PROJECTION_MATRIX_H

#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>


void setup_projection_matrix(surface_t zbuffer){

    zbuffer = surface_alloc(FMT_RGBA16, display_get_width(), display_get_height());

    float aspect_ratio = (float)display_get_width() / (float)display_get_height();
    float near_plane = 1.0f;
    float far_plane = 2000.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-near_plane*aspect_ratio, near_plane*aspect_ratio, -near_plane, near_plane, near_plane, far_plane);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


#endif