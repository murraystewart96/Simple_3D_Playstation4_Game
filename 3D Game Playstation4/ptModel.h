#ifndef __PT_MODEL__
#define __PT_MODEL__


#include "../../common/allocator.h"
#include "../../common/danFileParser.h"
#include "../../common/danRandom.h"
#include "../../common/danOBJHelpers.h"
#include <vectormath.h>


#include "ptAssetType.h"
#include "ptHardModels.h"
#include <scebase.h>


using namespace sce;
using namespace sce::Gnmx;
using namespace sce::Vectormath::Scalar::Aos;


class ptModel
{
private:
	size_t m_onionMemorySize = 16 * 1024 * 1024;
public:

	Gnm::Buffer myVertexBuffers[PT_VERTEX_ELEM_COUNT];

	//Vertex data
	ptVertex* m_vertices = nullptr;
	uint16_t m_vertexCount = 0;
	size_t m_verticesSize = 0;
	ptVertex* l_gpuVertexData = nullptr;

	//indices
	uint16_t* m_indices = nullptr;
	uint32_t m_indexCount = 0;
	size_t m_indicesSize = 0;
	uint16_t* l_gpuIndexData = nullptr;

	//
	ptTriangle* m_triangles = nullptr;

	//holds the name of file to load asset from
	const char* m_filename;

	PT_ASSET_TYPE m_assetType;


	bool m_validData = false;
	bool m_verbose = false;
	bool m_oneColour = false;
	bool m_noColour = false;
	bool m_useRandomColour = false;
	Vector3 m_defaultColour = { 0.5f, 0.5f, 0.5f };

	
	bool m_genSequentialTris = false;
	bool m_centralizePositions = false;
	bool m_normalizePositions = false;
	bool m_generateNormals = false;
	bool m_gotTexcoords = false;

	////////////////////////////////////////////////////////////////////////////////////////////////




	






	void centralizePositions();
	



	void normalizePositions();


	void cleanNormals();


	void generateNormals();
	

	void normalizeNormals();


	//*************************************************************************************//

	




	int loadModelOBJ(const char* _filename, LinearAllocator* _garlicAlloc);
	





	void printPositions();


	void printNormals();


	void printColours();



	void printTexcoords();


	void printTriangles();

	
	void convertToPTM();
	///////////////////////////////////////////////////////////////////////////////////////////////////


	//Load Model in from a file
	//Parameter: _fileName is the name of the file to be read from
	//Parameter: _garlicAlloc is the garlic memory allocator
	int loadModelPTM(const char* _fileName, LinearAllocator* _garlicAlloc);



	//***************************************************************//
	void fillColour(Vector3 _colour);




	void fillRandomColour();




	void generateSeqTriangles(LinearAllocator* _onionAllocator);




	////////////////////////////////////////////////////////////////////////////////
	void loadHardModel(PT_HARD_MODEL _model, LinearAllocator* _garlicAlloc);
	



	////////////////////////////////////////////////////////////////////


	int copyDataToGPU(LinearAllocator* _garlicAlloc);


	/////////////////////////////////////////////////////////////////

	void initVertexBuffer();
	

};//ptModel

#endif 