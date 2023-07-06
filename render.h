#ifndef RENDER_H
#define RENDER_H


#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>

#include "environment.h"


void render_init(GLenum shade_model, surface_t zbuffer, light_t light){
    
    glShadeModel(shade_model);

    surface_t *disp = display_get();

    rdpq_attach(disp, &zbuffer);

    gl_context_begin();

    glClearColor(light.color[0], light.color[1], light.color[2], light.color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    // Set some global render modes that we want to apply to all models
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
}

void render_end(){

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    gl_context_end();

    rdpq_detach_show();
}

#endif