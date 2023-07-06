#ifndef ENTITY_H
#define ENTITY_H

#include <libdragon.h>
#include <math.h>

#include "math.h"
#include "time.h"


struct entity_t {

	float position[3];
	float pitch;
	float yaw;

	float horizontal_speed;
	float vertical_speed;
	float forward_speed;
	float side_speed;
};


void set_entity_position(struct entity_t* entity, time_data_t time_data){

    float horizontal_distance = time_data.frame_duration * entity->horizontal_speed;

    entity->position[0] += horizontal_distance * sin(rad(entity->yaw));
    entity->position[1] -= horizontal_distance * cos(rad(entity->yaw));

}


#endif