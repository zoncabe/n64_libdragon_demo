#ifndef STATES_H
#define STATES_H


void set_animation(struct entity_t *entity) {

	if (entity->type == NICK) {

		if (entity->state  == WALK) sausage64_set_anim(&entity->model, ANIMATION_nick_walk_left);
		if (entity->state  == RUN) sausage64_set_anim(&entity->model, ANIMATION_nick_run_left);
		if (entity->state  == ROLL) sausage64_set_anim(&entity->model, ANIMATION_nick_run_to_roll_left);
		if (entity->state  == JUMP) sausage64_set_anim(&entity->model, ANIMATION_nick_jump_left);
		if (entity->state  == FALL) sausage64_set_anim(&entity->model, ANIMATION_nick_fall_idle_left) ;
		if (entity->state  == CROUCH) sausage64_set_anim(&entity->model, ANIMATION_nick_tap_shoe_left);
		if (entity->state  == STAND) sausage64_set_anim(&entity->model, ANIMATION_nick_tap_shoe_left);

    }
}


void set_entity_state(struct entity_t *entity, entity_state_t new_state) {
    
    if (entity->state == new_state){
        return;
    }

    if (new_state == WALK && 
              (  entity->state == STAND
              || entity->state == RUN)){

        set_animation(entity);
        entity->state = new_state;
    }

    if (new_state == RUN && 
              (  entity->state == STAND
              || entity->state == WALK)){

        set_animation(entity);
        entity->state = new_state;
    }

    if (new_state == ROLL && 
              (  entity->state == STAND 
              || entity->state == WALK 
              || entity->state == RUN)){

        set_animation(entity);
        entity->state = new_state;
    }

    if (new_state == JUMP && 
              (  entity->state == STAND
              || entity->state == WALK
              || entity->state == RUN)){

        set_animation(entity);
        entity->state = new_state;
    }

	    if (new_state == CROUCH && 
				entity->state == STAND){

        set_animation(entity);
        entity->state = new_state;
    }


    if (new_state == STAND && 
              (  entity->state == WALK
              || entity->state == RUN
              || entity->state == ROLL 
              || entity->state == JUMP)){

        set_animation(entity);
        entity->state = new_state;
    }
}


void entity_animcallback(struct entity_t *entity){

    // Go to idle animation when we finished attacking
    switch(entity->state)
    {

		case STAND: set_entity_state(entity, STAND); break;

		case CROUCH: set_entity_state(entity, CROUCH); break;

		case WALK: set_entity_state(entity, STAND); break;

		case RUN: set_entity_state(entity, STAND); break;

        case ROLL: set_entity_state(entity, STAND); break;

        case JUMP: set_entity_state(entity, FALL); break;

        case FALL: set_entity_state(entity, STAND); break;
    }
}


void state_handler(struct entity_t *entity){

    if (fabs(entity->horizontal_speed) > 0){

        sausage64_set_anim(&entity->model, ANIMATION_nick_walk_left);
        //set_entity_state(entity, WALK);   
    }

    else if (fabs(entity->horizontal_speed) > 20){

        sausage64_set_anim(&entity->model, ANIMATION_nick_run_left);
        //set_entity_state(entity, RUN);   
    }
}


#endif