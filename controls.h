#ifndef entity_CONTROLS_H
#define entity_CONTROLS_H

#include <libdragon.h>
#include <math.h>

#include "entity.h"
#include "camera.h"


void acceleration_to_speed(struct entity_t *entity, time_data_t time_data){

    entity->speed[0] += (entity->acceleration[0] * time_data.frame_duration);
    entity->speed[1] += (entity->acceleration[1] * time_data.frame_duration);
    entity->speed[2] += (entity->acceleration[2] * time_data.frame_duration);

}


void move_entity_stick(struct controller_data hold, struct entity_t* entity, camera_t camera, time_data_t time_data) {

	if (fabs(hold.c[0].y) < 7){hold.c[0].y = 0;}
	if (fabs(hold.c[0].x) < 7){hold.c[0].x = 0;}

	float ly = hold.c[0].y ;
	float lx = hold.c[0].x ;

    float input_amount = fabs(sqrt(lx * lx + ly * ly));

    entity->target_yaw = deg(atan2(lx, -ly) - rad(camera.angle_around_target));

    if (input_amount == 0) {

        if  (fabs(entity->speed[0]) < 0.1f && fabs(entity->speed[1]) < 0.1f){
            entity->speed[0] = 0;
            entity->speed[1] = 0;
            entity->new_state = STAND;
        }

        entity->target_speed[0] = 0;
        entity->target_speed[1] = 0;

        entity->acceleration[0] = 8 * (entity->target_speed[0] - entity->speed[0]);
        entity->acceleration[1] = 8 * (entity->target_speed[1] - entity->speed[1]);
    }
    else
	if (input_amount > 0 && input_amount < 80) {

        entity->target_speed[0] = 10 * sin(rad(entity->target_yaw));
        entity->target_speed[1] = 10 * -cos(rad(entity->target_yaw));

        entity->acceleration[0] = 8 * (entity->target_speed[0] - entity->speed[0]);
        entity->acceleration[1] = 8 * (entity->target_speed[1] - entity->speed[1]);

        entity->new_state = WALK;
    }
    else
    if (input_amount >= 80){

        entity->target_speed[0] = 25 * sin(rad(entity->target_yaw));
        entity->target_speed[1] = 25 * -cos(rad(entity->target_yaw));

        entity->acceleration[0] = 8 * (entity->target_speed[0] - entity->speed[0]);
        entity->acceleration[1] = 8 * (entity->target_speed[1] - entity->speed[1]);

        entity->new_state = RUN;
    }

    acceleration_to_speed(entity, time_data);

    if (entity->speed[0] != 0 || entity->speed[1] != 0) entity->yaw = deg(atan2(entity->speed[0], -entity->speed[1]));
        
}


void move_camera_p2_stick(struct controller_data hold, camera_t *camera){

    if (fabs(hold.c[1].y) < 7){hold.c[0].y = 0;}
	if (fabs(hold.c[1].x) < 7){hold.c[0].x = 0;}

    float ry = hold.c[1].y ;
	float rx = hold.c[1].x ;

    camera->angle_around_target += rx / 10.0f;
    camera->pitch += ry / 10.0f;

    if (camera->angle_around_target > 360) {camera->angle_around_target  = camera->angle_around_target - 360;}
    if (camera->angle_around_target < 0) {camera->angle_around_target  = camera->angle_around_target + 360;}

    if (camera->pitch > 85) {camera->pitch = 85;}
    if (camera->pitch < -85) {camera->pitch = -85;}
}


void move_camera_c_buttons(struct controller_data hold, camera_t *camera){

    if (hold.c[0].C_left) {camera->angle_around_target -= 5.0f;}
    if (hold.c[0].C_right) {camera->angle_around_target += 5.0f;}

    if (camera->angle_around_target > 360) {camera->angle_around_target  = camera->angle_around_target - 360;}
    if (camera->angle_around_target < 0) {camera->angle_around_target  = camera->angle_around_target + 360;}

     if (hold.c[0].C_down) {camera->pitch -= 5.0f;}
    if (hold.c[0].C_up) {camera->pitch += 5.0f;}

    if (camera->pitch > 85) {camera->pitch = 85;}
    if (camera->pitch < -85) {camera->pitch = -85;}
}


void move_camera_zoom(struct controller_data hold, camera_t *camera){

    if (hold.c[0].Z && camera->distance_from_target > 5) {camera->distance_from_target -= 1;}
    if (hold.c[0].R) {camera->distance_from_target += 1;}
}


/*==============================
    move_entity_c_buttons
    Moves entity with c buttons

void move_entity_c_buttons(Entity *entity, Camera camera, NUContData cont[1]){

    float forward_input = lim(cont[0].button & D_CBUTTONS) - lim(contdata[0].button & U_CBUTTONS);
    float side_input = lim(cont[0].button & R_CBUTTONS) - lim(contdata[0].button & L_CBUTTONS);

	if (forward_input != 0 || side_input != 0) {
    	entity->yaw = deg(atan2(side_input, forward_input) - rad(camera->angle_around_target));
        entity->horizontal_speed = 500;
    }
    
    if (forward_input == 0 && side_input == 0) {
        entity->horizontal_speed = 0;
    }
}

  if (hold.c[0].A) {}

  if (hold.c[0].B) {}

  if (hold.c[0].start) {}

  if (hold.c[0].R) {}

  if (hold.c[0].L) {}

  if (hold.c[0].C_up) {}

  if (hold.c[0].C_down) {}

  if (hold.c[0].C_right) {}

  float ly = hold.c[0].y;
  float lx = hold.c[0].x;

  float ry = hold.c[1].y;
  float rx = hold.c[1].x;0  

==============================*/


#endif