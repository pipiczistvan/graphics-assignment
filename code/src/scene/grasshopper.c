#include "scene/grasshopper.h"

#include "scene/world.h"
#include "core/camera.h"
#include "core/draw.h"

#define JUMP_CHANCE 250
#define GRAVITY -2.0
#define JUMP_POWER 0.5
#define SPEED 15.0

void init_grasshoppers(struct Grasshopper grasshoppers[], int count)
{
    struct Entity grasshopperEntity;
    set_entity(&grasshopperEntity, "res/grasshopper.obj", "res/grasshopper.png", &DEFAULT);

    int i;

    for (i = 0; i < count; i++)
    {
        grasshoppers[i].entity.model = grasshopperEntity.model;
        grasshoppers[i].entity.texture = grasshopperEntity.texture;

        set_entity_position(&(grasshoppers[i].entity), 0.0, 0.0, 0.0);
        set_entity_rotation(&(grasshoppers[i].entity), 0.0, 0.0, 0.0);
        set_entity_scale(&(grasshoppers[i].entity), 1.5, 1.5, 1.5);
        switch (rand() % 3) 
        {
            case 0:
                grasshoppers[i].entity.material = JADE;
                break;
            case 1:
                grasshoppers[i].entity.material = GOLD;
                break;
            case 2:
                grasshoppers[i].entity.material = OBSIDIAN;
                break;
        }
    }
}

void update_grasshoppers(struct Grasshopper grasshoppers[], int count, struct HeightMap *terrain, double delta)
{
    int i;

    for (i = 0; i < count; i++)
    {
        struct Vector3d *position = &(grasshoppers[i].entity.position);
        struct Vector3d *rotation = &(grasshoppers[i].entity.rotation);

        if (grasshoppers[i].in_air == FALSE)
        {
            if (is_in_camera_range(position) == TRUE)
            {
                grasshoppers[i].in_air = TRUE;
                grasshoppers[i].upward_speed = JUMP_POWER;
                grasshoppers[i].direction = position_relative_to_camera(position);
            } else if (rand() % JUMP_CHANCE == 0)
            {
                grasshoppers[i].in_air = TRUE;
                grasshoppers[i].upward_speed = JUMP_POWER;
                grasshoppers[i].direction = rand() % 4;
            }
        } else 
        {
            grasshoppers[i].upward_speed += GRAVITY * delta;
            position->y += grasshoppers[i].upward_speed;
            
            switch (grasshoppers[i].direction) {
                case 3:
                    rotation->y = 180;
                    position->x -= SPEED * delta;
                    break;
                case 2:
                    rotation->y = 0;
                    position->x += SPEED * delta;
                    break;
                case 1:
                    rotation->y = 90;
                    position->z -= SPEED * delta;
                    break;
                case 0:
                    rotation->y = -90;
                    position->z += SPEED * delta;
                    break;
            }

            
            double terrainX = (terrain->scale.x - 1) / 2.0 - 1;
            double terrainZ = (terrain->scale.z - 1) / 2.0 - 1;
            if (position->x < -terrainX)
            {
                position->x = -terrainX;
            }
            if (position->x > terrainX)
            {
                position->x = terrainX;
            }
            if (position->z < -terrainZ)
            {
                position->z = -terrainZ;
            }
            if (position->z > terrainZ)
            {
                position->z = terrainZ;
            }

            double terrain_height = get_terrain_height(terrain, position->x, position->z);

            if (position->y < terrain_height) 
            {
                grasshoppers[i].upward_speed = 0;
                grasshoppers[i].in_air = FALSE;
                position->y = terrain_height;
            }
        }
    }
}

void draw_grasshoppers(struct Grasshopper grasshoppers[], int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        draw_entity(&(grasshoppers[i].entity));
    }
}