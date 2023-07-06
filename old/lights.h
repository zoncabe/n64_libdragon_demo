#ifndef LIGHTS_H
#define LIGHTS_H

#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>

static const GLfloat environment_color[] = { 0.6f, 0.7f, 0.6f, 1.f };

#define LIGHT_COUNT 1
static const GLfloat light_pos[LIGHT_COUNT][4] = {
    { 1, 0, 0, 0 }
};

static const GLfloat light_diffuse[LIGHT_COUNT][4] = {
    { 1.0f, 0.0f, 0.0f, 1.0f }
};

void setup_lights() {
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, environment_color);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  float light_radius = 10.0f;

  for (uint32_t i = 0; i < LIGHT_COUNT; i++)
  {
      glEnable(GL_LIGHT0 + i);
      glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, light_diffuse[i]);
      glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, 2.0f/light_radius);
      glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, 1.0f/(light_radius*light_radius));
  }

  GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);

  glFogf(GL_FOG_START, 5);
  glFogf(GL_FOG_END, 20);
  glFogfv(GL_FOG_COLOR, environment_color);
}

void set_light_positions(float rotation)
{
    glPushMatrix();
    glRotatef(rotation*5.43f, 0, 1, 0);

    for (uint32_t i = 0; i < LIGHT_COUNT; i++)
    {
        glLightfv(GL_LIGHT0 + i, GL_POSITION, light_pos[i]);
    }
    glPopMatrix();
}


#endif