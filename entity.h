#ifndef ENTITY_H
#define ENTITY_H

#include <libdragon.h>
#include <math.h>

#include "math.h"
#include "time.h"


typedef enum {

	NICK
} entity_type_t;


typedef enum { 

	WALK,
	RUN,
	ROLL,
	JUMP,
	FALL,
	CROUCH,
	STAND
} entity_state_t;


struct entity_t {

	float position[3];
	float pitch;
	float yaw;

	float horizontal_speed;
	float vertical_speed;
	
	entity_type_t type;
	entity_state_t state;

	s64ModelHelper model;
};


void set_entity_position(struct entity_t* entity, time_data_t time_data){

    float horizontal_distance = time_data.frame_duration * entity->horizontal_speed;

    entity->position[0] += horizontal_distance * sin(rad(entity->yaw));
    entity->position[1] -= horizontal_distance * cos(rad(entity->yaw));
}


#endif