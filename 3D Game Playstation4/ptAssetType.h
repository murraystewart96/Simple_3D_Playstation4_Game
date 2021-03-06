#pragma once

enum class PT_ASSET_TYPE
{
	MODEL_PTM,
	MODEL_OBJ,
	TEXTURE_GNF,
	PIPELINE,
	COUNT
};//enum class

enum ptModelEnum {
	CUBE_SPLIT_FACE_PTM, SPHERE_PTM, TEAPOT_PTM, TEDDY_PTM, AIRBOAT_PTM, SPACESHIP_OBJ, SPACESHIP_PTM, ALIS_CAR_PTM, ALIS_CAR_OBJ, ENEMY_SHIP_OBJ, ENEMY_SHIP_PTM, SPACE_STATION_OBJ, SPACE_STATION_PTM, FLOOR_PTM, ICOSAHEDRON_PTM, ICOSAHEDRON_PVC_PTM, OCTAHEDRON_PVC_PTM, AIRBOAT_OBJ, AL_OBJ,
	AL_NORMALS_OBJ, CESSNA_OBJ, COW_NO_NORMALS_OBJ, CUBE_OBJ, DODECAHEDRON_OBJ, GOURD_OBJ,
	HUMANOID_QUAD_OBJ, HUMANOID_TRI_OBJ, ICOSAHEDRON_OBJ, LAMP_OBJ, MAGNOLIA_OBJ, OCTAHEDRON_OBJ,
	SANDAL_OBJ, SHUTTLE_OBJ, SKYSCRAPER_OBJ, SLOT_MACHINE_OBJ, TEAPOT_OBJ, TEDDY_OBJ, TETRAHEDRON,
	TRUMPET_OBJ, VIOLIN_CASE, PT_MODEL_COUNT
};

enum ptTextureEnum {
	BRICK_GNF, COW_GNF, COW_TEAPOT_GNF, DARK_WOOD_GNF, RAINBOW_GNF, SPACESHIP_GNF, SUN_GNF, SPACE_STATION_GNF, SPACE_GNF, ENEMY_SHIP_GNF, MARBLE_EMERALD_GNF, OOLITE_FONT_GNF, DAN_GNF, EARTH_GNF, GRASS_GNF,
	OIL_GNF, TEDDY_TEXTURE_GNF, PRIDE_ROCK_GNF, PT_TEXTURE_COUNT
};

enum ptPipelineEnum { TDM, VVM, MMM, HUD, PT_PIPELINE_COUNT};

enum ptMaterialEnum {DARK_WOOD_MAT, AL_MAT, COW_TEAPOT_MAT, BRICK_MAT, SPACE_STATION_MAT, RANDOM_COLOUR_MAT, USER_DEFINED_COLOUR_MAT, ENEMY_SHIP_MAT, RAINBOW_MAT, SPACE_MAT, SUN_MAT, SPACESHIP_MAT, OIL_MAT, EARTH_MAT, MERCURY_MAT, HUD_MAT, PT_MATERIAL_COUNT};

enum ptObjectEnum { FLOOR, TEAPOT, WALL, AL, ICOS, ROAD, ENEMY_SHIP, ROCKET, ENEMY_ROCKET, SPACESHIP, SPACE_STATION, SUN, MERCURY, EARTH, MOON, COMET, PLUTO, OBJECT_COUNT};

enum ptTestEnvironmentObjects { TEST_FLOOR, TEST_PTM, TEST_HARD_MODEL, TEST_WALL, TEST_VVM, TEST_OBJ_NORMALS, TEST_SPACE_STATION, TEST_OBJECT_COUNT };