#ifndef CUBE_H
#define CUBE_H

#include <libdragon.h>
#include <GL/gl.h>
#include "vertex.h"


/*typedef struct {
    float position[3];
    float texcoord[2];
    float normal[3];

    uint8_t mtx_index;

} vertex_t;*/


vertex_t cube_vertices[] = {
    { .position = {  0,  10, -10}, .texcoord = {0,  1}, .normal = { 0, 0, 0 }, .color = 0x00FFFFFF },   /* mtx_index = 1 },    0 */
    { .position = { 30,  10, -10}, .texcoord = {0,  1}, .normal = { 0, 3, 3 }, .color = 0x00FFFFFF },   /* mtx_index = 1 },    1 */
    { .position = { 30, -10, -10}, .texcoord = {0,  1}, .normal = { 0, 3, 3 }, .color = 0x00FFFFFF },   /* mtx_index = 1 },    2 */
    { .position = {  0, -10, -10}, .texcoord = {0,  1}, .normal = { 0, 0, 0 }, .color = 0x00FFFFFF },   /* mtx_index = 1 },    3 */
    { .position = { 30,  10,  10}, .texcoord = {0,  1}, .normal = { 0, 3, 3 }, .color = 0x00FFFFFF },   /* mtx_index = 2 },    4 */
    { .position = { 30, -10,  10}, .texcoord = {0,  1}, .normal = { 0, 3, 3 }, .color = 0x00FFFFFF },   /* mtx_index = 2 },    5 */
    { .position = {  0,  10,  10}, .texcoord = {0,  1}, .normal = { 0, 0, 0 }, .color = 0x00FFFFFF },   /* mtx_index = 2 },    6 */
    { .position = {  0, -10,  10}, .texcoord = {0,  1}, .normal = { 0, 0, 0 }, .color = 0x00FFFFFF },   /* mtx_index = 2 },    7 */
    { .position = {-30, -10, -10}, .texcoord = {0,  1}, .normal = { 0, 3, 3 }, .color = 0x00FFFFFF },   /* mtx_index = 3 },    8 */
    { .position = {-30,  10, -10}, .texcoord = {0,  1}, .normal = { 0, 3, 3 }, .color = 0x00FFFFFF },   /* mtx_index = 3 },    9 */
    { .position = {-30, -10,  10}, .texcoord = {0,  1}, .normal = { 0, 3, 3 }, .color = 0x00FFFFFF },   /* mtx_index = 3 },    10 */
    { .position = {-30,  10,  10}, .texcoord = {0,  1}, .normal = { 0, 3, 3 }, .color = 0x00FFFFFF },   /* mtx_index = 3 },    11 */
};

static const uint16_t cube_indices[] = {

     0,  1,  2,  0,  2,  3,
     1,  4,  5,  1,  5,  2,
     0,  6,  4,  0,  4,  1,
     4,  6,  7,  4,  7,  5,
     2,  5,  7,  2,  7,  3,
     0,  3,  8,  0,  8,  9,
     9,  8, 10,  9, 10, 11,
     0,  9, 11,  0, 11,  6,
    11, 10,  7, 11,  7,  6,
     8,  3,  7,  8,  7, 10,

};



void setup_cube()
{
}


void draw_cube()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(vertex_t), cube_vertices);
    glTexCoordPointer(2, GL_FLOAT, sizeof(vertex_t), cube_vertices);
    glNormalPointer(GL_FLOAT, sizeof(vertex_t), cube_vertices);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(vertex_t), cube_vertices);

    glDrawElements(GL_TRIANGLES, sizeof(cube_indices) / sizeof(uint16_t), GL_UNSIGNED_SHORT, cube_indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}



/*
void draw_cube()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(            3, GL_FLOAT,            sizeof(vertex_t),    cube_vertices[0].position);
    glTexCoordPointer(          2, GL_FLOAT,            sizeof(vertex_t),    cube_vertices[0].texcoord);
    glNormalPointer(               GL_FLOAT,            sizeof(vertex_t),    cube_vertices[0].normal);

    //glMatrixIndexPointerARB(    1, GL_UNSIGNED_BYTE,    sizeof(vertex_t),    &cube_vertices[0].mtx_index);

    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(vertex_t), (void*)(8*sizeof(float) + cube_vertices));

    glDrawElements(GL_TRIANGLES, sizeof(cube_vertices) / sizeof(uint16_t), GL_UNSIGNED_SHORT, cube_vertices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}*/

void render_cube()
{
    rdpq_debug_log_msg("Cube");
    glPushMatrix();
    glTranslatef(0,-1.f,0);

    // Apply vertex color as material color.
    // Because the cube has colors set per vertex, we can color each face seperately
    glEnable(GL_COLOR_MATERIAL);

    // Apply to ambient and diffuse material properties
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    draw_cube();
    
    glDisable(GL_COLOR_MATERIAL);

    glPopMatrix();
}


#endif



/*

void draw_skinned()
{
    glEnable(GL_MATRIX_PALETTE_ARB);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_MATRIX_INDEX_ARRAY_ARB);

    glVertexPointer(        3,  GL_FLOAT,           sizeof(vertex_t),   cube_vertices[0].position);
    glTexCoordPointer(      2,  GL_FLOAT,           sizeof(vertex_t),   cube_vertices[0].texcoord);
    glNormalPointer(            GL_FLOAT,           sizeof(vertex_t),   cube_vertices[0].normal);
    glMatrixIndexPointerARB(1,  GL_UNSIGNED_BYTE,   sizeof(vertex_t),   &cube_vertices[0].mtx_index);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(cube_vertices)/sizeof(vertex_t));

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_MATRIX_INDEX_ARRAY_ARB);

    glDisable(GL_MATRIX_PALETTE_ARB);
}


*/

/*

void render_skinned(const camera_t *camera, float animation)
{
    rdpq_debug_log_msg("Skinned");

    // Set bone transforms. Note that because there is no matrix stack in palette mode, we need
    // to apply the camera transform and model transform as well for each bone.
    glMatrixMode(GL_MATRIX_PALETTE_ARB);

    // Set transform of first bone
    glCurrentPaletteMatrixARB(0);
    camera_transform(camera);
    skinned_model_transform();
    glRotatef(sinf(animation*0.1f)*45, 0, 0, 1);

    // Set transform of second bone
    glCurrentPaletteMatrixARB(1);
    camera_transform(camera);
    skinned_model_transform();
    glRotatef(-sinf(animation*0.1f)*45, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_CULL_FACE);
    draw_skinned();
    glEnable(GL_CULL_FACE);
}

void skinned_model_transform()
{
    glTranslatef(0, 3, -6);
    glScalef(2, 2, 2);
}

*/






/*


typedef struct {
    f32 pos[3];
    f32 rot[4];
    f32 scale[3];
} FrameData;

static FrameData animation_framedata0[] = {
    
    {{0.0000f, 0.0000f, 0.0000f}, {1.0000f, 0.0000f, 0.0000f, 0.0000f}, {1.0000f, 1.0000f, 1.0000f}},
   
    {{0.0000f, 0.0000f, 0.0000f}, {1.0000f, 0.0000f, 0.0000f, 0.0000f}, {1.0000f, 1.0000f, 1.0000f}},

};

static FrameData animation_framedata4[] = {
    {{0.0000f, 0.0000f, 0.0000f}, {0.9680f, 0.0000f, 0.2509f, 0.0000f}, {1.0000f, 1.0000f, 1.0000f}},
    {{0.0000f, 0.0000f, 0.0000f}, {0.9599f, -0.0000f, -0.2805f, -0.0000f}, {1.0000f, 1.0000f, 1.0000f}},
};
static FrameData animation_framedata8[] = {
    {{0.0000f, 0.0000f, 0.0000f}, {1.0000f, 0.0000f, 0.0000f, 0.0000f}, {1.0000f, 1.0000f, 1.0000f}},
    {{0.0000f, 0.0000f, 0.0000f}, {1.0000f, 0.0000f, 0.0000f, 0.0000f}, {1.0000f, 1.0000f, 1.0000f}},
};
static FrameData animation_framedata12[] = {
    {{0.0000f, 0.0000f, 0.0000f}, {0.9774f, 0.0000f, -0.2115f, -0.0000f}, {1.0000f, 1.0000f, 1.0000f}},
    {{0.0000f, 0.0000f, 0.0000f}, {0.9736f, -0.0000f, 0.2284f, 0.0000f}, {1.0000f, 1.0000f, 1.0000f}},
};
static FrameData animation_framedata16[] = {
    {{0.0000f, 0.0000f, 0.0000f}, {1.0000f, 0.0000f, 0.0000f, 0.0000f}, {1.0000f, 1.0000f, 1.0000f}},
    {{0.0000f, 0.0000f, 0.0000f}, {1.0000f, 0.0000f, 0.0000f, 0.0000f}, {1.0000f, 1.0000f, 1.0000f}},
};


typedef struct {
    u32 framenumber;
    FrameData* framedata;
} KeyFrame;


static KeyFrame animation_keyframes[] = {
    {0, animation_framedata0},
    {4, animation_framedata4},
    {8, animation_framedata8},
    {12, animation_framedata12},
    {16, animation_framedata16},
};



*/
