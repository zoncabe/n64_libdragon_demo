#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
    float distance;
    float rotation;
} camera_t;

void camera_transform(const camera_t *camera)
{
    // Set the camera transform
    glLoadIdentity();
    gluLookAt(
        0, -camera->distance, -camera->distance,
        0, 0, 0,
        0, 0, 1);
    glRotatef(camera->rotation, 0, 0, 1);
}

#endif
