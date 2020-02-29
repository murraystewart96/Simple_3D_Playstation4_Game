#ifndef __PT_ASSET_MANAGER__
#define __PT_ASSET_MANAGER__
#include "../../common/danTextureLoader.h"
#include "ptModel.h"
#include "ptMaterials.h"


class ptAssetManager
{
public:
	ptModel m_myModels[PT_MODEL_COUNT];
	ptTexture m_myTextures[PT_TEXTURE_COUNT];
	ptPipeline m_myPipelines[PT_PIPELINE_COUNT];
	ptMaterial m_myMaterials[PT_MATERIAL_COUNT];

	LinearAllocator* m_myGarlicAllocator;
	sce::Gnmx::Toolkit::Allocators* m_myToolkitAllocator;
	danTextureLoader m_myTexL;
	Gnm::Sampler m_sampler;


	ptAssetManager();


	ptAssetManager(LinearAllocator* _garlicAllocator, sce::Gnmx::Toolkit::Allocators* _toolkitAllocator);
	
	void Initialise();
	

	
	ptMaterial* GetMaterial(ptMaterialEnum material);
	

	ptPipeline* getPipeline(ptPipelineEnum pipeline);
	


	ptModel* getModel(ptModelEnum model_name);
	

	Gnm::Texture* getTexture(ptTextureEnum texture);
	
};

#endif