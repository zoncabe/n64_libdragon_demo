#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>


typedef struct{

    const GLfloat color[4];
    const GLfloat diffuse[4];

    const GLfloat position[4];
    const GLfloat direction[3];

    const float radius;

} light_t;


void setup_light(light_t light) {

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light.color);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 2.0f/light.radius);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0f/(light.radius*light.radius));

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, light.diffuse);

}

void set_light(light_t light)
{
    glPushMatrix();
    glRotatef(light.direction[0], 1, 0, 0);
    glRotatef(light.direction[1], 0, 1, 0);
    glRotatef(light.direction[2], 0, 0, 1);
    glLightfv(GL_LIGHT0, GL_POSITION, light.position);
    glPopMatrix();

}

void setup_fog(light_t light) {
    
    glFogf(GL_FOG_START, 2);
    glFogf(GL_FOG_END, 50);
    glFogfv(GL_FOG_COLOR, light.color);

}

void set_fog() {
    
    glEnable(GL_FOG);

}


#endif