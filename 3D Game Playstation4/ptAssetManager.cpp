
#include "ptAssetManager.h"

ptAssetManager::ptAssetManager()
{

}

ptAssetManager::ptAssetManager(LinearAllocator* _garlicAllocator, sce::Gnmx::Toolkit::Allocators* _toolkitAllocator)
{
	m_myGarlicAllocator = _garlicAllocator;
	m_myToolkitAllocator = _toolkitAllocator;
}

void ptAssetManager::Initialise()
{



	// Initialize the texture sampler
	Gnm::Sampler myTexSampler;
	myTexSampler.init();
	myTexSampler.setMipFilterMode(Gnm::kMipFilterModeNone);
	myTexSampler.setXyFilterMode(Gnm::kFilterModeBilinear, Gnm::kFilterModeBilinear);



	m_sampler = myTexSampler;

	m_myModels[AIRBOAT_OBJ].m_filename = "/app0/assets/models/OBJ/airboat.obj";
	m_myModels[AIRBOAT_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[AL_OBJ].m_filename = "/app0/assets/models/OBJ/al.obj";
	m_myModels[AL_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[AL_NORMALS_OBJ].m_filename = "/app0/assets/models/OBJ/al-normals.obj";
	m_myModels[AL_NORMALS_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[CESSNA_OBJ].m_filename = "/app0/assets/models/OBJ/cessna.obj";
	m_myModels[CESSNA_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[COW_NO_NORMALS_OBJ].m_filename = "/app0/assets/models/OBJ/cow-nonormals.obj";
	m_myModels[COW_NO_NORMALS_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[CUBE_OBJ].m_filename = "/app0/assets/models/OBJ/cube.obj";
	m_myModels[CUBE_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[SPACESHIP_OBJ].m_filename = "/app0/assets/models/OBJ/spaceship.obj";
	m_myModels[SPACESHIP_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[DODECAHEDRON_OBJ].m_filename = "/app0/assets/models/OBJ/dodecahedron.obj";
	m_myModels[DODECAHEDRON_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[GOURD_OBJ].m_filename = "/app0/assets/models/OBJ/gourd.obj";
	m_myModels[GOURD_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[SPACE_STATION_OBJ].m_filename = "/app0/assets/models/OBJ/Hexa.obj";
	m_myModels[SPACE_STATION_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[HUMANOID_QUAD_OBJ].m_filename = "/app0/assets/models/OBJ/humanoid_quad.obj";
	m_myModels[HUMANOID_QUAD_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[HUMANOID_TRI_OBJ].m_filename = "/app0/assets/models/OBJ/humanoid_tri.obj";
	m_myModels[HUMANOID_TRI_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[ICOSAHEDRON_OBJ].m_filename = "/app0/assets/models/OBJ/icosahedron.obj";
	m_myModels[ICOSAHEDRON_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[ENEMY_SHIP_OBJ].m_filename = "/app0/assets/models/OBJ/Beholder.obj";
	m_myModels[ENEMY_SHIP_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[LAMP_OBJ].m_filename = "/app0/assets/models/OBJ/lamp.obj";
	m_myModels[LAMP_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[MAGNOLIA_OBJ].m_filename = "/app0/assets/models/OBJ/magnolia.obj";
	m_myModels[MAGNOLIA_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[OCTAHEDRON_OBJ].m_filename = "/app0/assets/models/OBJ/octahedron.obj";
	m_myModels[OCTAHEDRON_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[SANDAL_OBJ].m_filename = "/app0/assets/models/OBJ/sandal.obj";
	m_myModels[SANDAL_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[SHUTTLE_OBJ].m_filename = "/app0/assets/models/OBJ/shuttle.obj";
	m_myModels[SHUTTLE_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[SKYSCRAPER_OBJ].m_filename = "/app0/assets/models/OBJ/skyscraper.obj";
	m_myModels[SKYSCRAPER_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[SLOT_MACHINE_OBJ].m_filename = "/app0/assets/models/OBJ/slot_machine.obj";
	m_myModels[SLOT_MACHINE_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[TEAPOT_OBJ].m_filename = "/app0/assets/models/OBJ/teapot.obj";
	m_myModels[TEAPOT_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[TEDDY_OBJ].m_filename = "/app0/assets/models/OBJ/teddy.obj";
	m_myModels[TEDDY_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[TETRAHEDRON].m_filename = "/app0/assets/models/OBJ/tetrahedron.obj";
	m_myModels[TETRAHEDRON].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[TRUMPET_OBJ].m_filename = "/app0/assets/models/OBJ/trumpet.obj";
	m_myModels[TRUMPET_OBJ].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[VIOLIN_CASE].m_filename = "/app0/assets/models/OBJ/violin_case.obj";
	m_myModels[VIOLIN_CASE].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

	m_myModels[ALIS_CAR_PTM].m_filename = "/app0/assets/models/PTM/newCar.ptm";
	m_myModels[ALIS_CAR_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;


	m_myModels[CUBE_SPLIT_FACE_PTM].m_filename = "/app0/assets/models/PTM/CubeSplitFace.ptm";
	m_myModels[CUBE_SPLIT_FACE_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[CUBE_SPLIT_FACE_PTM].m_verbose = true;


	m_myModels[SPHERE_PTM].m_filename = "/app0/assets/models/PTM/Sphere.ptm";
	m_myModels[SPHERE_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[TEAPOT_PTM].m_filename = "/app0/assets/models/PTM/Teapot.ptm";
	m_myModels[TEAPOT_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[TEDDY_PTM].m_filename = "/app0/assets/models/PTM/Teddy.ptm";
	m_myModels[TEDDY_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[SPACESHIP_PTM].m_filename = "/app0/assets/models/PTM/spaceship.ptm";
	m_myModels[SPACESHIP_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[AIRBOAT_PTM].m_filename = "/app0/assets/models/PTM/airboat.ptm";
	m_myModels[AIRBOAT_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[ICOSAHEDRON_PVC_PTM].m_filename = "/app0/assets/models/PTM/icosahedron_pvc.ptm";
	m_myModels[ICOSAHEDRON_PVC_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[OCTAHEDRON_PVC_PTM].m_filename = "/app0/assets/models/PTM/octahedron_pvc.ptm";
	m_myModels[OCTAHEDRON_PVC_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[ICOSAHEDRON_PTM].m_filename = "/app0/assets/models/PTM/icosahedron.ptm";
	m_myModels[ICOSAHEDRON_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[FLOOR_PTM].m_filename = "/app0/assets/models/PTM/Floor.ptm";
	m_myModels[FLOOR_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[SPACE_STATION_PTM].m_filename = "/app0/assets/models/PTM/SpaceStation.ptm";
	m_myModels[SPACE_STATION_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	m_myModels[ENEMY_SHIP_PTM].m_filename = "/app0/assets/models/PTM/enemy.ptm";
	m_myModels[ENEMY_SHIP_PTM].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

	/*
	m_myModels[PT_PTM_MODEL_CUBEPVC].m_filename = "/app0/assets/models/PTM/CubePVC.ptm";
	m_myModels[PT_PTM_MODEL_CUBEPVC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[PT_PTM_MODEL_CUBESPLITFACE].m_filename = "/app0/assets/models/PTM/CubeSplitFace.ptm";
	m_myModels[PT_PTM_MODEL_CUBESPLITFACE].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[PT_PTM_MODEL_ICOSPVC].m_filename = "/app0/assets/models/PTM/IcosPVC.ptm";
	m_myModels[PT_PTM_MODEL_ICOSPVC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[PT_PTM_MODEL_ICOSSPLITFACE].m_filename = "/app0/assets/models/PTM/PT_PTM_MODEL_ICOSSPLITFACE.ptm";
	m_myModels[PT_PTM_MODEL_ICOSSPLITFACE].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[PT_PTM_MODEL_OCTAPVC].m_filename = "/app0/assets/models/PTM/OctaPVC.ptm";
	m_myModels[PT_PTM_MODEL_OCTAPVC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[PT_PTM_MODEL_OCTASPLITFACE].m_filename = "/app0/assets/models/PTM/OctaSplitFace.ptm";
	m_myModels[PT_PTM_MODEL_OCTASPLITFACE].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[PT_PTM_MODEL_SPHERE].m_filename = "/app0/assets/models/PTM/Sphere.ptm";
	m_myModels[PT_PTM_MODEL_SPHERE].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[PT_PTM_MODEL_TEAPOT].m_filename = "/app0/assets/models/PTM/Teapot.ptm";
	m_myModels[PT_PTM_MODEL_TEAPOT].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[PT_PTM_MODEL_TEDDY].m_filename = "/app0/assets/models/PTM/Teddy.ptm";
	m_myModels[PT_PTM_MODEL_TEDDY].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[PT_PTM_MODEL_TETRAPVC].m_filename = "/app0/assets/models/PTM/TetraPVC.ptm";
	m_myModels[PT_PTM_MODEL_TETRAPVC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	m_myModels[PT_PTM_MODEL_TETRASPLITFACE].m_filename = "/app0/assets/models/PTM/TetraSplitFace.ptm";
	m_myModels[PT_PTM_MODEL_TETRASPLITFACE].m_assetType = PT_ASSET_TYPE::MODEL_PTM;
	*/




	m_myTextures[BRICK_GNF].m_filename = "/app0/assets/textures/brick.gnf";
	m_myTextures[COW_GNF].m_filename = "/app0/assets/textures/cow.gnf";
	m_myTextures[COW_TEAPOT_GNF].m_filename = "/app0/assets/textures/cowTeapot.gnf";
	m_myTextures[DAN_GNF].m_filename = "/app0/assets/textures/dan.gnf";
	m_myTextures[EARTH_GNF].m_filename = "/app0/assets/textures/earth.gnf";
	m_myTextures[GRASS_GNF].m_filename = "/app0/assets/textures/grass.gnf";
	m_myTextures[OIL_GNF].m_filename = "/app0/assets/textures/oil.gnf";
	m_myTextures[TEDDY_TEXTURE_GNF].m_filename = "/app0/assets/textures/TeddyTexture.gnf";
	m_myTextures[PRIDE_ROCK_GNF].m_filename = "/app0/assets/textures/pride_rock.gnf";
	m_myTextures[MARBLE_EMERALD_GNF].m_filename = "/app0/assets/textures/marble_emerald.gnf";
	m_myTextures[DARK_WOOD_GNF].m_filename = "/app0/assets/textures/dark_wood.gnf";
	m_myTextures[OOLITE_FONT_GNF].m_filename = "/app0/assets/textures/oolite-font.gnf";
	m_myTextures[RAINBOW_GNF].m_filename = "/app0/assets/textures/rainbow.gnf";
	m_myTextures[SUN_GNF].m_filename = "/app0/assets/textures/sun.gnf";
	m_myTextures[SPACE_GNF].m_filename = "/app0/assets/textures/space_background.gnf";
	m_myTextures[SPACE_STATION_GNF].m_filename = "/app0/assets/textures/SpaceStation.gnf";
	m_myTextures[ENEMY_SHIP_GNF].m_filename = "/app0/assets/textures/enemy.gnf";
	m_myTextures[SPACESHIP_GNF].m_filename = "/app0/assets/textures/shipTexture.gnf";



	m_myPipelines[TDM].m_filename_vv = "/app0/ptTDMShader_vv.sb";
	m_myPipelines[TDM].m_filename_p = "/app0/ptTDMShader_p.sb";
	m_myPipelines[TDM].m_shaderType = PT_SHADER_CONSTANTS::TDM;
	m_myPipelines[TDM].textureCount = 1;

	m_myPipelines[VVM].m_filename_vv = "/app0/ptVVMShader_vv.sb";
	m_myPipelines[VVM].m_filename_p = "/app0/ptVVMShader_p.sb";
	m_myPipelines[VVM].m_shaderType = PT_SHADER_CONSTANTS::VVM;
	m_myPipelines[VVM].textureCount = 0;

	m_myPipelines[MMM].m_filename_vv = "/app0/ptMMMShader_vv.sb";
	m_myPipelines[MMM].m_filename_p = "/app0/ptMMMShader_p.sb";
	m_myPipelines[MMM].m_shaderType = PT_SHADER_CONSTANTS::MMM;
	m_myPipelines[MMM].textureCount = 0;

	m_myPipelines[HUD].m_filename_vv = "/app0/ptHUDShader_vv.sb";
	m_myPipelines[HUD].m_filename_p = "/app0/ptHUDShader_p.sb";
	m_myPipelines[HUD].m_shaderType = PT_SHADER_CONSTANTS::TDM;
	m_myPipelines[HUD].textureCount = 1;

	//

	m_myMaterials[DARK_WOOD_MAT].m_specularStrength = 0.7f;
	m_myMaterials[DARK_WOOD_MAT].m_specularPower = 10.0f;
	m_myMaterials[DARK_WOOD_MAT].SetPipelineType(TDM, m_myPipelines[TDM].textureCount);
	m_myMaterials[DARK_WOOD_MAT].SetTextureName(DARK_WOOD_GNF, 0);


	m_myMaterials[HUD_MAT].SetPipelineType(HUD, m_myPipelines[HUD].textureCount);
	m_myMaterials[HUD_MAT].SetTextureName(OOLITE_FONT_GNF, 0);

	m_myMaterials[BRICK_MAT].SetPipelineType(TDM, m_myPipelines[TDM].textureCount);
	m_myMaterials[BRICK_MAT].SetTextureName(BRICK_GNF, 0);

	m_myMaterials[ENEMY_SHIP_MAT].SetPipelineType(TDM, m_myPipelines[TDM].textureCount);
	m_myMaterials[ENEMY_SHIP_MAT].SetTextureName(ENEMY_SHIP_GNF, 0);


	m_myMaterials[EARTH_MAT].SetPipelineType(TDM, m_myPipelines[TDM].textureCount);
	m_myMaterials[EARTH_MAT].SetTextureName(EARTH_GNF, 0);


	m_myMaterials[RAINBOW_MAT].SetPipelineType(TDM, m_myPipelines[TDM].textureCount);
	m_myMaterials[RAINBOW_MAT].SetTextureName(RAINBOW_GNF, 0);
	m_myMaterials[RAINBOW_MAT].m_transparency = 0.4f;

	m_myMaterials[SUN_MAT].SetPipelineType(TDM, m_myPipelines[TDM].textureCount);
	m_myMaterials[SUN_MAT].SetTextureName(SUN_GNF, 0);

	m_myMaterials[OIL_MAT].SetPipelineType(TDM, m_myPipelines[TDM].textureCount);
	m_myMaterials[OIL_MAT].SetTextureName(OIL_GNF, 0);

	m_myMaterials[SPACE_MAT].SetPipelineType(TDM, m_myPipelines[TDM].textureCount);
	m_myMaterials[SPACE_MAT].SetTextureName(SPACE_GNF, 0);


	m_myMaterials[COW_TEAPOT_MAT].m_specularStrength = 0.7f;
	m_myMaterials[COW_TEAPOT_MAT].m_specularPower = 10.0f;
	m_myMaterials[COW_TEAPOT_MAT].SetPipelineType(TDM, m_myPipelines[TDM].textureCount);
	m_myMaterials[COW_TEAPOT_MAT].SetTextureName(COW_TEAPOT_GNF, 0);


	m_myMaterials[SPACE_STATION_MAT].SetPipelineType(TDM, m_myPipelines[TDM].textureCount);
	m_myMaterials[SPACE_STATION_MAT].SetTextureName(SPACE_STATION_GNF, 0);


	
	m_myMaterials[SPACESHIP_MAT].m_specularStrength = 0.7f;
	m_myMaterials[SPACESHIP_MAT].m_specularPower = 10.0f;
	m_myMaterials[SPACESHIP_MAT].SetPipelineType(VVM, m_myPipelines[VVM].textureCount);


	m_myMaterials[MERCURY_MAT].m_ambientColour = Vector3(0.5, 0, 0.5);  
	m_myMaterials[MERCURY_MAT].m_diffuseColour = Vector3(0.5, 0, 0.5);
	m_myMaterials[MERCURY_MAT].m_specularStrength = 0.7f;
	m_myMaterials[MERCURY_MAT].m_specularPower = 10.0f;
	m_myMaterials[MERCURY_MAT].SetPipelineType(VVM, m_myPipelines[VVM].textureCount);

	
	m_myMaterials[RANDOM_COLOUR_MAT].m_specularStrength = 0.7f;
	m_myMaterials[RANDOM_COLOUR_MAT].m_specularPower = 10.0f;
	m_myMaterials[RANDOM_COLOUR_MAT].SetPipelineType(VVM, m_myPipelines[VVM].textureCount);


	m_myMaterials[USER_DEFINED_COLOUR_MAT].m_specularStrength = 0.7f;
	m_myMaterials[USER_DEFINED_COLOUR_MAT].m_specularPower = 10.0f;
	m_myMaterials[USER_DEFINED_COLOUR_MAT].SetPipelineType(VVM, m_myPipelines[VVM].textureCount);


}


ptMaterial* ptAssetManager::GetMaterial(ptMaterialEnum material)
{

	//Load material if not already loaded
	if (!m_myMaterials[material].m_isLoaded)
	{
		if (!m_myMaterials[material].m_pipeline)    //Get a pipeline for material if needed
		{
			m_myMaterials[material].m_pipeline = getPipeline(m_myMaterials[material].getPipelineType());
		}

		for (int i = 0; i < m_myMaterials[material].m_textureCount; i++)  //Assign texture(s) for material
		{
			m_myMaterials[material].m_myTextures[i] = getTexture(m_myMaterials[material].getTextureName(i));
		}

		m_myMaterials[material].m_isLoaded = true;      //loaded
	}

	if (!m_myMaterials[material].m_mySampler)    //Assign sampler
	{
		m_myMaterials[material].m_mySampler = &m_sampler;
	}


	return &m_myMaterials[material];    
}

ptPipeline* ptAssetManager::getPipeline(ptPipelineEnum pipeline)
{
	//Load pipeline if not initialised
	if (!m_myPipelines[pipeline].m_isInitialised)
	{
		m_myPipelines[pipeline].LoadShaders(m_myToolkitAllocator, m_myGarlicAllocator);
		m_myPipelines[pipeline].m_isInitialised = true;

	}
	return &m_myPipelines[pipeline];   
}



ptModel* ptAssetManager::getModel(ptModelEnum model_name)
{
	//Load model data if current data is not valid
	if (!m_myModels[model_name].m_validData)
	{
		if (m_myModels[model_name].m_assetType == PT_ASSET_TYPE::MODEL_PTM)
		{
			m_myModels[model_name].loadModelPTM(m_myModels[model_name].m_filename, m_myGarlicAllocator);

		}
		else if (m_myModels[model_name].m_assetType == PT_ASSET_TYPE::MODEL_OBJ)
		{
			m_myModels[model_name].loadModelOBJ(m_myModels[model_name].m_filename, m_myGarlicAllocator);
		}

	}

	return &m_myModels[model_name];   
}

Gnm::Texture* ptAssetManager::getTexture(ptTextureEnum texture)
{
	int l_error = SCE_OK;


	//Load texture if current data is not valid
	if (!m_myTextures[texture].m_validData)
	{
		l_error = m_myTexL.loadTextureFromGnf(m_myTextures[texture].m_filename, m_myTextures[texture].m_index,
			m_myToolkitAllocator, m_myTextures[texture].m_texture);

		m_myTextures[texture].m_validData = true;  //After loading set to valid
	}


	return &m_myTextures[texture].m_texture;
}




