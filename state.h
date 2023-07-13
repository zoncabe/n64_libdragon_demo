#ifndef STATE_H
#define STATE_H


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


void set_entity_state(struct entity_t *entity) {
    
    if (entity->state == entity->new_state){
        return;
    }

    if (entity->new_state == WALK && 
              (  entity->state == STAND
              || entity->state == RUN)){

        entity->state = entity->new_state;
        set_animation(entity);
    }

    if (entity->new_state == RUN && 
              (  entity->state == STAND
              || entity->state == WALK)){

        entity->state = entity->new_state;
        set_animation(entity);
    }

    if (entity->new_state == ROLL && 
              (  entity->state == STAND 
              || entity->state == WALK 
              || entity->state == RUN)){

        entity->state = entity->new_state;
        set_animation(entity);
    }

    if (entity->new_state == JUMP && 
              (  entity->state == STAND
              || entity->state == WALK
              || entity->state == RUN)){

        entity->state = entity->new_state;
        set_animation(entity);
    }

	    if (entity->new_state == CROUCH && 
				entity->state == STAND){

        entity->state = entity->new_state;
        set_animation(entity);
    }


    if (entity->new_state == STAND && 
              (  entity->state == WALK
              || entity->state == RUN
              || entity->state == ROLL 
              || entity->state == JUMP)){

        entity->state = entity->new_state;
        set_animation(entity);
    }
}


#endif