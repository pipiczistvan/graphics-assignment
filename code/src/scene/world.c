#include "scene/world.h"

#include "core/draw.h"
#include "core/entity.h"
#include "core/height_map.h"
#include "core/input.h"
#include "core/light.h"
#include "core/fog.h"
#include "scene/grasshopper.h"

#define GRASS_COUNT 30
#define WALL_COUNT_PER_SIDE 10
#define WALL_SCALE (TERRAIN_SCALE / WALL_COUNT_PER_SIDE)
#define GRASSHOPPER_COUNT 10
#define FOG_DENSITY_LIMIT 0.1

struct Entity skyboxEntity;
struct Entity grassEntities[GRASS_COUNT];
struct Entity wallEntities[WALL_COUNT_PER_SIDE * 4];
struct Grasshopper grasshoppers[GRASSHOPPER_COUNT];
struct Fog fog;

int l_pressed = FALSE;
int f_pressed = FALSE;
double light_ambient = 0.5;
double delta_density = -0.05;

struct Light light;

void create_light()
{
    set_light_position(&light, 0.0, 10.0, 0.0, 0.0);
    set_light_ambient(&light, light_ambient, light_ambient, light_ambient, 1.0);
    set_light_diffuse(&light, 1.0, 1.0, 1.0, 1.0);
    set_light_specular(&light, 1.0, 1.0, 1.0, 1.0);

    load_light(&light, GL_LIGHT0);
}

void create_walls()
{
    set_entity(&wallEntities[0], "res/wall.obj", "res/wall.png", &DEFAULT);

    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < WALL_COUNT_PER_SIDE; j++)
        {
            int index = i * WALL_COUNT_PER_SIDE + j;
            wallEntities[index].model = wallEntities[0].model;
            wallEntities[index].texture = wallEntities[0].texture;
            wallEntities[index].material = wallEntities[0].material;

            int x, z;
            double rot;
            switch (i) {
                case 0:
                    x = -(TERRAIN_SCALE - 1) / 2 + j * WALL_SCALE + WALL_SCALE / 2;
                    z = -(TERRAIN_SCALE - 1) / 2;
                    rot = 0;
                    break;
                case 1:
                    x = -(TERRAIN_SCALE - 1) / 2 + j * WALL_SCALE + WALL_SCALE / 2;
                    z = (TERRAIN_SCALE - 1) / 2;
                    rot = 0;
                    break;
                case 2:
                    z = -(TERRAIN_SCALE - 1) / 2 + j * WALL_SCALE + WALL_SCALE / 2;
                    x = -(TERRAIN_SCALE - 1) / 2;
                    rot = 90;
                    break;
                case 3:
                    z = -(TERRAIN_SCALE - 1) / 2 + j * WALL_SCALE + WALL_SCALE / 2;
                    x = (TERRAIN_SCALE - 1) / 2;
                    rot = 90;
                    break;
            }
            set_entity_position(&wallEntities[index], x, 0.0, z);
            set_entity_scale(&wallEntities[index], WALL_SCALE, WALL_SCALE, WALL_SCALE);
            set_entity_rotation(&wallEntities[index], 0.0, rot, 0.0);
        }
    }
}

void create_grasses()
{
    set_entity(&grassEntities[0], "res/grass.obj", "res/grass.png", &DEFAULT);

    int i;
    for (i = 0; i < GRASS_COUNT; i++)
    {
        grassEntities[i].model = grassEntities[0].model;
        grassEntities[i].texture = grassEntities[0].texture;
        grassEntities[i].material = grassEntities[0].material;

        int x = rand() % TERRAIN_SCALE + -TERRAIN_SCALE / 2;
        int z = rand() % TERRAIN_SCALE + -TERRAIN_SCALE / 2;
        set_entity_position(&grassEntities[i], x, get_terrain_height(&terrain, x, z), z);
        set_entity_scale(&grassEntities[i], 2.0, 2.0, 2.0);
    }
}

void create_fog()
{
    fog.density = 0.0;
    fog.color[0] = 0.3;
    fog.color[1] = 0.3;
    fog.color[2] = 0.3;
    fog.color[3] = 1.0;
}

void init_world()
{
    set_height_map(&terrain, "res/heightmap2.png", "res/soil_ground.png", 6.0 / TERRAIN_SCALE);
    set_height_map_scale(&terrain, TERRAIN_SCALE, 6.0, TERRAIN_SCALE);
    set_height_map_position(&terrain, -TERRAIN_SCALE / 2, 0.0, -TERRAIN_SCALE / 2);

    set_entity(&skyboxEntity, "res/skybox.obj", "res/skybox.png", &DEFAULT);
    set_entity_scale(&skyboxEntity, 500.0, 500.0, 500.0);

    create_walls();
    create_grasses();
    create_light();
    create_fog();

    init_grasshoppers(grasshoppers, GRASSHOPPER_COUNT);
}

void update_world(double delta)
{
    skyboxEntity.rotation.y += 1.0 * delta;
    fog.density += delta_density * delta;
    if (fog.density < 0.0) 
    {
        fog.density = 0.0;
    } else if (fog.density > FOG_DENSITY_LIMIT)
    {
        fog.density = FOG_DENSITY_LIMIT;
    }

    update_grasshoppers(grasshoppers, GRASSHOPPER_COUNT, &terrain, delta);

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
            set_light_ambient(&light, light_ambient, light_ambient, light_ambient, 0.0);
            load_light(&light, GL_LIGHT0);
        }
        l_pressed = TRUE;
    } else {
        l_pressed = FALSE;
    }
}

void draw_world()
{
    glEnable(GL_FOG);
    draw_fog(&fog);

    draw_entity(&skyboxEntity);
    draw_height_map_entity(&terrain);
    
    int i;
    for (i = 0; i < WALL_COUNT_PER_SIDE * 4; i++)
    {
        draw_entity(&wallEntities[i]);
    }
    for (i = 0; i < GRASS_COUNT; i++)
    {
        draw_entity(&grassEntities[i]);
    }

    draw_grasshoppers(grasshoppers, GRASSHOPPER_COUNT);
}
