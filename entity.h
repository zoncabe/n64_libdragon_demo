#ifndef ENTITY_H
#define ENTITY_H

#include <libdragon.h>

struct Entity {
	float size[3];
	float pos[3];
	float dir[3];
	float scale;
	float pitch;
	float yaw;
	float speed;
	float vertical_speed;
	float forward_speed;
	float side_speed;
};

#endif