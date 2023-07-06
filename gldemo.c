#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "time.h"
#include "projection_matrix.h"
#include "render.h"
#include "environment.h"
#include "materials.h"
#include "dummy_low.h"
#include "sphere.h"
#include "plane.h"
#include "controls.h"
#include "entity.h"
#include "camera.h"

// Set this to 1 to enable rdpq debug output.
// The demo will only run for a single frame and stop.
#define DEBUG_RDP 0

#define TEXTURE_NUMBER 3

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
    distance_from_entity: 6,
    pitch: 30,
};

struct entity_t dummy = {
    position: {0, 0, 0,},
};


void setup(){

    setup_projection_matrix(&zbuffer);

    setup_textures(textures, sprites, texture_path, TEXTURE_NUMBER);

    setup_sphere();
    make_sphere_mesh();

    setup_plane();
    make_plane_mesh();

    setup_light(light);

    //setup_fog(light);
    
}

void render(){

    render_init(shade_model, zbuffer, light);

    set_light(light);

    set_camera(camera, dummy);
    
    //set_fog();

    glPushMatrix();
	glTranslatef(dummy.position[0], dummy.position[1], dummy.position[2]);
    glRotatef(dummy.yaw, 0, 0, 1);
	glScalef(1.f, 1.f, 1.f);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    render_dummy(); 
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, textures[0%4]);
    render_plane();

    glBindTexture(GL_TEXTURE_2D, textures[2%4]);
    render_sphere(dummy);

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
    
        move_entity_stick(hold, &dummy, camera);
        set_entity_position(&dummy, time_data);

        move_camera_c_buttons(hold, &camera);
        move_camera_zoom(hold, &camera);
        set_camera_position(&camera, dummy);

        render();

        if (DEBUG_RDP) rspq_wait();
    }

}
