#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "camera.h"
#include "dummy_low.h"
#include "plane.h"
#include "lights.h"
#include "player_controls.h"
#include "entity.h"

// Set this to 1 to enable rdpq debug output.
// The demo will only run for a single frame and stop.
#define DEBUG_RDP 0

static uint32_t texture_index = 0;
static camera_t camera;
static surface_t zbuffer;

static GLuint textures[5];

static GLenum shade_model = GL_SMOOTH;
static bool fog_enabled = false;

struct Entity player;

static const char *texture_path[5] = {
    "rom:/circle0.sprite",
    "rom:/diamond0.sprite",
    "rom:/pentagon0.sprite",
    "rom:/skin0.sprite",
    "rom:/triangle0.sprite",
};

static sprite_t *sprites[5];






void setup()
{
    camera.distance = -10.0f;
    camera.rotation = 0.0f;

    zbuffer = surface_alloc(FMT_RGBA16, display_get_width(), display_get_height());





    for (uint32_t i = 0; i < 5; i++)
    {
        sprites[i] = sprite_load(texture_path[i]);
    }

    setup_cube();

    setup_plane();
    make_plane_mesh();






    float aspect_ratio = (float)display_get_width() / (float)display_get_height();
    float near_plane = 1.0f;
    float far_plane = 5000.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-near_plane*aspect_ratio, near_plane*aspect_ratio, -near_plane, near_plane, near_plane, far_plane);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    setup_lights();

    glGenTextures(5, textures);

    #if 0
    GLenum min_filter = GL_LINEAR_MIPMAP_LINEAR;
    #else
    GLenum min_filter = GL_LINEAR;
    #endif


    for (uint32_t i = 0; i < 5; i++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

        glSpriteTextureN64(GL_TEXTURE_2D, sprites[i], &(rdpq_texparms_t){.s.repeats = REPEAT_INFINITE, .t.repeats = REPEAT_INFINITE});
    }
}


void render()
{

    if (fog_enabled) {
        glEnable(GL_FOG);
    } else {
        glDisable(GL_FOG);
    }
    glShadeModel(shade_model);

    surface_t *disp = display_get();

    rdpq_attach(disp, &zbuffer);

    gl_context_begin();

    glClearColor(environment_color[0], environment_color[1], environment_color[2], environment_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    camera_transform(&camera);

    set_light_positions(1.0f);

    // Set some global render modes that we want to apply to all models
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[3]);

    glPushMatrix();
	glScalef(3.f, 3.f, 3.f);
	glTranslatef(player.pos[0], player.pos[1], 0.f);

    render_cube(); 

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, textures[(texture_index + 1)%4]);
    render_plane();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    gl_context_end();

    rdpq_detach_show();
}












int main()
{
	debug_init_isviewer();
	debug_init_usblog();
    
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

    while (1)
    {

        controller_scan();
        struct controller_data pressed = get_keys_pressed();
        struct controller_data down = get_keys_down();
    
        handle_controller_input_player(pressed, down, &player);

        render();
        if (DEBUG_RDP)
            rspq_wait();
    }

}
