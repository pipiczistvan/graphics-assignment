#include "scene/bee.h"

#include "core/draw.h"
#include "core/utils.h"
#include "scene/world.h"
#include <math.h>

#define WING_SPEED 2000
#define FLOATING_SPEED 50
#define FLYING_SPEED 5
#define TERRAIN_OFFSET 2
#define FLOWER_RANGE 5
#define LANDING_SPEED 5
#define EATING_LIMIT 5

// PRIVATE

void apply_changes_to_wings(struct Bee *bee)
{
    set_entity_position(&(bee->left_wing), bee->body.position.x, bee->body.position.y, bee->body.position.z);
    set_entity_position(&(bee->right_wing), bee->body.position.x, bee->body.position.y, bee->body.position.z);
    bee->left_wing.rotation.y = bee->body.rotation.y;
    bee->right_wing.rotation.y = bee->body.rotation.y;
}

void flap_wings(struct Bee *bee, double delta, double speed)
{
    bee->wing_progression += delta * speed;
    bee->left_wing.rotation.z = 45.0 + cos(degree_to_radian(bee->wing_progression)) * 22.5;
    bee->right_wing.rotation.z = -bee->left_wing.rotation.z;
}

int fly_to_target_position(struct Bee *bee, struct HeightMap *terrain, double delta)
{
    struct Vector3d *bee_position = &(bee->body.position);
    struct Vector3d *bee_rotation = &(bee->body.rotation);

    double d_x = bee->target_position.x - bee_position->x;
    double d_z = bee->target_position.z - bee_position->z;

    // is near target position
    if (abs(d_x) < 0.5 && abs(d_z) < 0.5)
    {
        return TRUE;
    } else 
    {
        // rotate to target
        bee_rotation->y = radian_to_degree(atan2(d_x, d_z));

        // move to target
        bee_position->x += sin(degree_to_radian(bee_rotation->y)) * FLYING_SPEED * delta;
        bee_position->z += cos(degree_to_radian(bee_rotation->y)) * FLYING_SPEED * delta;

        // floating
        bee->floating_progression += delta * FLOATING_SPEED;
        double terrain_height = get_terrain_height_on_pos(terrain, bee->body.position.x, bee->body.position.z);
        bee_position->y = terrain_height + cos(degree_to_radian(bee->floating_progression)) + 1 + TERRAIN_OFFSET;

        apply_changes_to_wings(bee);

        return FALSE;
    }
}

struct Entity *get_flower_in_range(struct Bee *bee, struct Entity flowers[], int flower_count)
{
    int i;

    for (i = 0; i < flower_count; i++)
    {
        if (bee->body.position.x - FLOWER_RANGE <= flowers[i].position.x &&
            bee->body.position.x + FLOWER_RANGE >= flowers[i].position.x &&
            bee->body.position.z - FLOWER_RANGE <= flowers[i].position.z &&
            bee->body.position.z + FLOWER_RANGE >= flowers[i].position.z)
        {
            return &(flowers[i]);
        }
    }

    return NULL;
}

// PUBLIC

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

        double scale = random_double(0.75, 1.25);
        bees[i].floating_progression = 0;
        bees[i].wing_progression = 0;
        bees[i].eating_progression = 0;

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

        // target
        bees[i].target_position.x = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
        bees[i].target_position.z = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
        bees[i].target_flower = NULL;
    }
}

void update_bees(struct Bee bees[], int bee_count, struct Entity flowers[], int flower_count, struct HeightMap *terrain, double delta)
{
    int i;

    for (i = 0; i < bee_count; i++)
    {
        int reached_target = fly_to_target_position(&(bees[i]), terrain, delta);

        struct Entity *closest_flower = get_flower_in_range(&(bees[i]), flowers, flower_count);
        // find a different target flower
        if (closest_flower != NULL && bees[i].target_flower != closest_flower)
        {
            bees[i].target_flower = closest_flower;
            bees[i].target_position = bees[i].target_flower->position;
            bees[i].eating_progression = 0;
        }

        if (reached_target == TRUE)
        {
            if (bees[i].target_flower == NULL)
            {
                // find new random target
                bees[i].target_position.x = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
                bees[i].target_position.z = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
                flap_wings(&(bees[i]), delta, WING_SPEED);
            } else
            {
                double terrain_height = get_terrain_height_on_pos(terrain, bees[i].body.position.x, bees[i].body.position.z);
                // bee is in target flower position
                if (bees[i].eating_progression == 0)
                {
                    // begin landing sequence
                    if (bees[i].body.position.y > terrain_height + 0.5)
                    {
                        bees[i].body.position.y -= delta * LANDING_SPEED;
                    } else
                    {
                        bees[i].body.position.y = terrain_height + 0.5;
                        bees[i].eating_progression += delta;
                    }
                    flap_wings(&(bees[i]), delta, WING_SPEED);
                } else
                {
                    if (bees[i].eating_progression >= EATING_LIMIT)
                    {
                        // begin ascending sequence
                        if (bees[i].body.position.y < terrain_height + cos(degree_to_radian(bees[i].floating_progression)) + 1 + TERRAIN_OFFSET)
                        {
                            bees[i].body.position.y += delta * LANDING_SPEED;
                        } else
                        {
                            // find new random target
                            bees[i].target_position.x = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
                            bees[i].target_position.z = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
                        }
                        flap_wings(&(bees[i]), delta, WING_SPEED);
                    } else
                    {
                        bees[i].eating_progression += delta;
                        flap_wings(&(bees[i]), delta, WING_SPEED / 100);
                    }
                }
                
                apply_changes_to_wings(&(bees[i]));
            }
        } else 
        {
            flap_wings(&(bees[i]), delta, WING_SPEED);
        }
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
