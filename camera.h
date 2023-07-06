#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"


typedef struct {

    float distance;
    float rotation;

    float distance_from_entity;
	float horizontal_distance_from_entity;
	float vertical_distance_from_entity;
    float angle_around_entity;

	float position[3];
	float pitch;
	float yaw;
	float roll;

} camera_t;


void set_camera (camera_t camera, struct entity_t entity){

    glLoadIdentity();
    gluLookAt(
        camera.position[0], camera.position[1], camera.position[2],
        entity.position[0], entity.position[1], entity.position[2],
        0, 0, 1);

}

void set_camera_position(camera_t *camera, struct entity_t entity){

    camera->horizontal_distance_from_entity = camera->distance_from_entity * cos(rad(camera->pitch));
	camera->vertical_distance_from_entity = camera->distance_from_entity * sin(rad(camera->pitch));

    camera->position[0] = entity.position[0] - camera->horizontal_distance_from_entity * sin(rad(camera->angle_around_entity));
    camera->position[1] = entity.position[1] - camera->horizontal_distance_from_entity * cos(rad(camera->angle_around_entity));
    camera->position[2] = camera->vertical_distance_from_entity + entity.position[2];

    //if ((camera->vertical_distance_from_entity + entity.position[2]) < 0){camera->position[2] = 0;}
}


#endif
