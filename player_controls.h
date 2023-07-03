#ifndef PLAYER_CONTROLS_H
#define PLAYER_CONTROLS_H

#include <libdragon.h>
#include <math.h>
#include "entity.h"

void handle_controller_input_player(struct controller_data pressed, 
                                    struct controller_data down,
                                    struct Entity* player) {

  if (pressed.c[0].A) {
  }

  if (pressed.c[0].B) {
  }

  if (down.c[0].start) {
  }

  if (down.c[0].R) {
  }

  if (down.c[0].L) {
      //fog_enabled = !fog_enabled;
  }

  if (down.c[0].C_up) {
  }

  if (down.c[0].C_down) {
  }

  if (down.c[0].C_right) {
      //texture_index = (texture_index + 1) % 4;
  }

  float y = pressed.c[0].y/20;
  float x = pressed.c[0].x/20;
  // calculate magnitude
  float mag = /* todo add back sqrt here */x*x + y*y;

  if (fabsf(mag) > 0.01f) {
      player->pos[0] -= (x / 20.0);
      player->pos[1] -= (y / 20.0);
  }
}
#endif