#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "sausage64.h"
#include "time.h"
#include "projection_matrix.h"
#include "render.h"
#include "environment.h"
#include "materials.h"
#include "entity.h"
#include "nick.h"
#include "state.h"
#include "camera.h"
#include "controls.h"

// Set this to 1 to enable rdpq debug output.
// The demo will only run for a single frame and stop.
#define DEBUG_RDP 0

#define TEXTURE_NUMBER 3

#define MODEL_NUMBER 1

static surface_t zbuffer;

static GLenum shade_model = GL_SMOOTH;

static GLuint textures[TEXTURE_NUMBER];

static sprite_t *sprites[TEXTURE_NUMBER];

static const char *texture_path[TEXTURE_NUMBER] = {
    "rom:/grass0.sprite",
    "rom:/skin0.sprite",
    "rom:/sky0.sprite",
};

static time_data_t time_data;

static light_t light = {
    
    color: { 0.5f, 0.5f, 0.5f, 0.5f},
    diffuse: {1.0f, 1.0f, 1.0f, 1.0f},
    direction: {0.0f, -60.0f, 0.0f},
    position: {1.0f, 0.0f, 0.0f, 0.0f},
    radius: 10.0f,
};

static camera_t camera = {
    distance_from_target: 10,
    pitch: 30,
};

static model64_t *assets;


void setup(){

    setup_projection_matrix(&zbuffer);

    setup_textures(textures, sprites, texture_path, TEXTURE_NUMBER);

    setup_nick();

    setup_light(light);

    //setup_fog(light);

    void animcallback(u16 anim){

        
        /*switch(anim)
        {   
            case ANIMATION_nick_walk_left:
            case ANIMATION_nick_run_left:
            case ANIMATION_nick_stand_to_roll_left:
            case ANIMATION_nick_run_to_roll_left :
                sausage64_set_anim(&nick.model, ANIMATION_nick_look_around_left);
                break;
        
        }*/
        entity_animcallback(&nick);
    }

    sausage64_set_animcallback(&nick.model, animcallback);

    assets = model64_load("rom:/assets.model64");
    
}

void render(){

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    glPushMatrix();
	glTranslatef(nick.position[0], nick.position[1], nick.position[2]);
    glColor3f(0.400, 0.950, 1.000);
    model64_draw_mesh(model64_get_mesh(assets, 0));
    glPopMatrix();

    render_init(shade_model, zbuffer, light);

    set_light(light);

    set_camera(camera, nick);
    
    //set_fog();

    glPushMatrix();
	glTranslatef(nick.position[0], nick.position[1], nick.position[2]);
    glRotatef(nick.yaw, 0, 0, 1);
	glScalef(0.05f, 0.05f, 0.05f);
    sausage64_drawmodel(&nick.model); 
    glPopMatrix();

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    glPushMatrix();
	glTranslatef(nick.position[0], nick.position[1], nick.position[2]);
    glColor3f(0.400, 0.950, 1.000);
    model64_draw_mesh(model64_get_mesh(assets, 0));
    glPopMatrix();

    glPushMatrix();
	//glTranslatef(nick.position[0], nick.position[1], nick.position[2]);
	//glScalef(0.1f, 0.1f, 0.1f);
    glColor3f(0.123, 0.823, 0.123);
    model64_draw_mesh(model64_get_mesh(assets, 1));
    glPopMatrix();
  
    render_end();
}


int main(){

	debug_init_isviewer();
	debug_init_usblog();

    console_init();
    console_set_render_mode(RENDER_MANUAL);

    timer_init();
    
    dfs_init(DFS_DEFAULT_LOCATION);

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_RESAMPLE_FETCH_ALWAYS);

    rdpq_init();

    gl_init();

#if DEBUG_RDP
    rdpq_debug_start();
    rdpq_debug_log(true);
#endif

    setup();

    controller_init();

    while (1){

        time_management(&time_data);

        controller_scan();
        struct controller_data hold = get_keys_pressed();
        //struct controller_data press = get_keys_down();
    
        move_entity_stick(hold, &nick, camera);
        set_entity_position(&nick, time_data);

        move_camera_p2_stick(hold, &camera);

        //state_handler(&nick);

        if (fabs(nick.horizontal_speed) > 0){
            if (nick.state != WALK){
                nick.state = WALK;
                sausage64_set_anim(&nick.model, ANIMATION_nick_walk_left);   
            }
        }

        sausage64_advance_anim(&nick.model, 3.0f);

        move_camera_zoom(hold, &camera);
        set_camera_position(&camera, nick);

        render();

        if (DEBUG_RDP) rspq_wait();
    }

}
