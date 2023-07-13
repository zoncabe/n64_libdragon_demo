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

	float target_yaw;
	float yaw;

	float force[3];
	float acceleration[3];

	float target_speed[3];
	float speed[3];
	
	entity_type_t type;
	entity_state_t state;
	entity_state_t new_state;

	s64ModelHelper model;
};


void set_entity_position(struct entity_t* entity, time_data_t time_data){

    entity->position[0] += entity->speed[0] * time_data.frame_duration;
    entity->position[1] += entity->speed[1] * time_data.frame_duration;
    entity->position[2] += entity->speed[2] * time_data.frame_duration;
}


#endif