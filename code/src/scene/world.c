#include "scene/world.h"

#include "core/draw.h"
#include "core/input.h"

#define WALL_SCALE (TERRAIN_SCALE_X / WALL_COUNT_PER_SIDE)
#define FOG_DENSITY_LIMIT 0.1

int l_pressed = FALSE;
int f_pressed = FALSE;
double light_ambient = 1.0;
double delta_density = -0.05;

// PRIVATE

void create_light(struct Light *light)
{
    set_light_position(light, 10.0, 10.0, 10.0, 0.0);
    set_light_ambient(light, light_ambient, light_ambient, light_ambient, 1.0);
    set_light_diffuse(light, 1.0, 1.0, 1.0, 1.0);
    set_light_specular(light, 1.0, 1.0, 1.0, 1.0);

    load_light(light, GL_LIGHT0);
}

void create_walls(struct Entity *walls)
{
    set_entity(&walls[0], "resources/models/wall.obj", "resources/textures/wall.png", &DEFAULT);

    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < WALL_COUNT_PER_SIDE; j++)
        {
            int index = i * WALL_COUNT_PER_SIDE + j;
            walls[index].model = walls[0].model;
            walls[index].texture = walls[0].texture;
            walls[index].material = walls[0].material;

            int x, z;
            double rot;
            switch (i) {
                case 0:
                    x = -(TERRAIN_SCALE_X - 1) / 2 + j * WALL_SCALE + WALL_SCALE / 2;
                    z = -(TERRAIN_SCALE_X - 1) / 2;
                    rot = 0;
                    break;
                case 1:
                    x = -(TERRAIN_SCALE_X - 1) / 2 + j * WALL_SCALE + WALL_SCALE / 2;
                    z = (TERRAIN_SCALE_X - 1) / 2;
                    rot = 0;
                    break;
                case 2:
                    z = -(TERRAIN_SCALE_X - 1) / 2 + j * WALL_SCALE + WALL_SCALE / 2;
                    x = -(TERRAIN_SCALE_X - 1) / 2;
                    rot = 90;
                    break;
                case 3:
                    z = -(TERRAIN_SCALE_X - 1) / 2 + j * WALL_SCALE + WALL_SCALE / 2;
                    x = (TERRAIN_SCALE_X - 1) / 2;
                    rot = 90;
                    break;
            }
            move_entity(&walls[index], x, 0.0, z);
            scale_entity(&walls[index], WALL_SCALE, WALL_SCALE, WALL_SCALE);
            rotate_entity(&walls[index], 0.0, rot, 0.0);
        }
    }
}

void create_grasses(struct HeightMap *terrain, struct Entity *grasses)
{
    set_entity(&grasses[0], "resources/models/grass.obj", "resources/textures/grass.png", &GREEN_RUBBER);

    int i;
    for (i = 0; i < GRASS_COUNT; i++)
    {
        grasses[i].model = grasses[0].model;
        grasses[i].texture = grasses[0].texture;
        grasses[i].material = grasses[0].material;

        int x = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
        int z = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
        move_entity(&grasses[i], x, get_terrain_height_on_pos(terrain, x, z), z);
        scale_entity(&grasses[i], 2.0, 2.0, 2.0);
    }
}

void create_flowers(const struct HeightMap *terrain, struct Entity *flowers)
{
    set_entity(&flowers[0], "resources/models/flower.obj", "resources/textures/flower.png", &DEFAULT);

    int i;
    for (i = 0; i < FLOWER_COUNT; i++)
    {
        flowers[i].model = flowers[0].model;
        flowers[i].texture = flowers[0].texture;
        flowers[i].material = flowers[0].material;

        int x = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
        int z = rand() % TERRAIN_SCALE_X + -TERRAIN_SCALE_X / 2;
        move_entity(&flowers[i], x, get_terrain_height_on_pos(terrain, x, z), z);
        scale_entity(&flowers[i], 1.0, 1.0, 1.0);
    }
}

void create_fog(struct Fog *fog)
{
    fog->density = 0.0;
    fog->color[0] = 0.3;
    fog->color[1] = 0.3;
    fog->color[2] = 0.3;
    fog->color[3] = 1.0;
}

// PUBLIC

void init_world(struct World *world)
{
    set_height_map(&(world->terrain), "resources/textures/heightmap2.png", "resources/textures/soil_ground.png", TERRAIN_SCALE_Y / TERRAIN_SCALE_X, &DEFAULT);
    scale_height_map(&(world->terrain), TERRAIN_SCALE_X, TERRAIN_SCALE_Y, TERRAIN_SCALE_X);
    move_height_map(&(world->terrain), -TERRAIN_SCALE_X / 2, 0.0, -TERRAIN_SCALE_X / 2);

    set_entity(&(world->skybox), "resources/models/skybox.obj", "resources/textures/skybox.png", &DEFAULT);
    scale_entity(&(world->skybox), 500.0, 500.0, 500.0);

    create_walls(world->walls);
    create_grasses(&(world->terrain), world->grasses);
    create_flowers(&(world->terrain), world->flowers);
    create_light(&(world->light));
    create_fog(&(world->fog));

    create_grasshoppers(world->grasshoppers, GRASSHOPPER_COUNT, world->grasses, GRASS_COUNT);
    create_bees(world->bees, BEE_COUNT);
}

void update_world(struct World *world, double delta)
{
    // skybox
    world->skybox.rotation.y += 1.0 * delta;

    // fog
    world->fog.density += delta_density * delta;
    if (world->fog.density < 0.0) 
    {
        world->fog.density = 0.0;
    } else if (world->fog.density > FOG_DENSITY_LIMIT)
    {
        world->fog.density = FOG_DENSITY_LIMIT;
    }

    // grasshoppers
    update_grasshoppers(world->grasshoppers, GRASSHOPPER_COUNT, &(world->terrain), delta);

    // bees
    update_bees(world->bees, BEE_COUNT, world->flowers, FLOWER_COUNT, &(world->terrain), delta);

    // input
    if (keyboard.F == PRESSED)
    {
        if (f_pressed == FALSE)
        {
           delta_density *= -1; 
        }
        f_pressed = TRUE;
    } else {
        f_pressed = FALSE;
    }

    if (keyboard.L == PRESSED)
    {
        if (l_pressed == FALSE)
        {
            light_ambient += 0.1;
            if (light_ambient >= 0.8)
            {
                light_ambient = 0.2;
            }
            set_light_ambient(&(world->light), light_ambient, light_ambient, light_ambient, 0.0);
            load_light(&(world->light), GL_LIGHT0);
        }
        l_pressed = TRUE;
    } else {
        l_pressed = FALSE;
    }
}

void draw_world(const struct World *world)
{
    glEnable(GL_FOG);
    draw_fog(&(world->fog));

    draw_entity(&(world->skybox));
    draw_height_map_entity(&(world->terrain));
    draw_entities(world->walls, WALL_COUNT_PER_SIDE * 4);
    draw_entities(world->grasses, GRASS_COUNT);
    draw_grasshoppers(world->grasshoppers, GRASSHOPPER_COUNT);
    draw_bees(world->bees, BEE_COUNT);
    draw_entities(world->flowers, FLOWER_COUNT);
}
