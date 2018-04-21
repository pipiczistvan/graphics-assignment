#include "scene/bee.h"

#include "core/draw.h"
#include "core/utils.h"
#include "scene/world.h"
#include <math.h>

#define WING_SPEED 2000
#define FLOATING_SPEED 50
#define FLYING_SPEED 5
#define TERRAIN_OFFSET 2

void create_bees(struct Bee bees[], int count)
{
    struct Entity bee_body, bee_wing;
    set_entity(&bee_body, "res/bee_body.obj", "res/bee.png", &DEFAULT);
    set_entity(&bee_wing, "res/bee_wing.obj", "res/bee.png", &DEFAULT);

    int i;

    for (i = 0; i < count; i++)
    {
        int x = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
        int z = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;

        double scale = random_double(1.0, 1.5);
        bees[i].flying_progression = 0;
        bees[i].wing_progression = 0;

        // body
        bees[i].body.model = bee_body.model;
        bees[i].body.texture = bee_body.texture;
        set_entity_position(&(bees[i].body), x, 5, z);
        set_entity_rotation(&(bees[i].body), 0.0, 0.0, 0.0);
        set_entity_scale(&(bees[i].body), scale, scale, scale);
        bees[i].body.material = GOLD;

        // left wing
        bees[i].left_wing.model = bee_wing.model;
        bees[i].left_wing.texture = bee_wing.texture;
        set_entity_position(&(bees[i].left_wing), x, 5, z);
        set_entity_rotation(&(bees[i].left_wing), 0.0, 0.0, 0.0);
        set_entity_scale(&(bees[i].left_wing), scale, scale, scale);
        bees[i].left_wing.material = SILVER;

        // right wing
        bees[i].right_wing.model = bee_wing.model;
        bees[i].right_wing.texture = bee_wing.texture;
        set_entity_position(&(bees[i].right_wing), x, 5, z);
        set_entity_rotation(&(bees[i].right_wing), 0.0, 0.0, 0.0);
        set_entity_scale(&(bees[i].right_wing), scale, scale, scale);
        bees[i].right_wing.material = SILVER;
    }
}

void update_bees(struct Bee bees[], int count, struct HeightMap *terrain, double delta)
{
    int i;
    double terrainX = (terrain->scale.x - 1) / 2.0 - 1;
    double terrainZ = (terrain->scale.z - 1) / 2.0 - 1;

    for (i = 0; i < count; i++)
    {
        struct Vector3d *position = &(bees[i].body.position);
        struct Vector3d *rotation = &(bees[i].body.rotation);

        // wings
        bees[i].wing_progression += delta * WING_SPEED;
        bees[i].left_wing.rotation.z = 45.0 + cos(degree_to_radian(bees[i].wing_progression)) * 22.5;
        bees[i].right_wing.rotation.z = -bees[i].left_wing.rotation.z;

        // rotation
        rotation->y += random_double(-180.0, 180.0) * delta;

        // movement
        if (position->x < -terrainX)
        {
            position->x = -terrainX;
            rotation->y += 90;
        }
        if (position->x > terrainX)
        {
            position->x = terrainX;
            rotation->y += 90;
        }
        if (position->z < -terrainZ)
        {
            position->z = -terrainZ;
            rotation->y += 90;
        }
        if (position->z > terrainZ)
        {
            position->z = terrainZ;
            rotation->y += 90;
        }
        position->x += sin(degree_to_radian(rotation->y)) * FLYING_SPEED * delta;
        position->z += cos(degree_to_radian(rotation->y)) * FLYING_SPEED * delta;
        
        // floating
        bees[i].flying_progression += delta * FLOATING_SPEED;
        double terrain_height = get_terrain_height_on_pos(terrain, bees[i].body.position.x, bees[i].body.position.z);
        position->y = terrain_height + cos(degree_to_radian(bees[i].flying_progression)) + 1 + TERRAIN_OFFSET;

        // apply changes to wings
        set_entity_position(&(bees[i].left_wing), position->x, position->y, position->z);
        set_entity_position(&(bees[i].right_wing), position->x, position->y, position->z);
        bees[i].left_wing.rotation.y = rotation->y;
        bees[i].right_wing.rotation.y = rotation->y;
    }
}

void draw_bees(struct Bee bees[], int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        draw_entity(&(bees[i].body));
        draw_entity(&(bees[i].left_wing));
        draw_entity(&(bees[i].right_wing));
    }
}
