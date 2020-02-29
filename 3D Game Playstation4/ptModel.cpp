
#include "ptModel.h"



void ptModel::centralizePositions()
{
	float l_totalX = 0, l_averageX = 0;
	float l_totalY = 0, l_averageY = 0;
	float l_totalZ = 0, l_averageZ = 0;

	//add all up
	for (int i = 0; i < m_vertexCount; i++)
	{
		l_totalX += m_vertices[i].x;
		l_totalY += m_vertices[i].y;
		l_totalZ += m_vertices[i].z;
	}//for

	 //find centre
	l_averageX = l_totalX / m_vertexCount;
	l_averageY = l_totalY / m_vertexCount;
	l_averageZ = l_totalZ / m_vertexCount;

	//ofset from local origin
	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertices[i].x -= l_averageX;
		m_vertices[i].y -= l_averageY;
		m_vertices[i].z -= l_averageZ;
	}//for
}//centralizePositions()


void ptModel::normalizePositions()
{
	float l_largest = 0.0f;
	for (int i = 0; i < m_vertexCount; i++)
	{
		float t_length = sqrt((m_vertices[i].x * m_vertices[i].x) + (m_vertices[i].y * m_vertices[i].y) + (m_vertices[i].z * m_vertices[i].z));
		if (t_length > l_largest) l_largest = t_length;
	}//for
	printf("Normalizing model size by factor %f\n", l_largest);
	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertices[i].x = m_vertices[i].x / l_largest;
		m_vertices[i].y = m_vertices[i].y / l_largest;
		m_vertices[i].z = m_vertices[i].z / l_largest;
	}//for
}//normalizePositions()

void ptModel::cleanNormals()
{
	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertices[i].nx = 0;
		m_vertices[i].ny = 0;
		m_vertices[i].nz = 0;
	}
}

void ptModel::generateNormals()
{
	printf("Generating Normals\n");
	cleanNormals();

	Vector3 A;
	Vector3 B;
	Vector3 C;
	Vector3 normal;
	Vector3 unitNormal;

	for (int i = 0; i < m_indexCount / 3; i++)
	{
		A.setX(m_vertices[m_triangles[i].a].x);
		A.setY(m_vertices[m_triangles[i].a].y);
		A.setZ(m_vertices[m_triangles[i].a].z);

		B.setX(m_vertices[m_triangles[i].b].x);
		B.setY(m_vertices[m_triangles[i].b].y);
		B.setZ(m_vertices[m_triangles[i].b].z);

		C.setX(m_vertices[m_triangles[i].c].x);
		C.setY(m_vertices[m_triangles[i].c].y);
		C.setZ(m_vertices[m_triangles[i].c].z);

		normal = Vectormath::Scalar::Aos::cross((B - A), (C - A));

		unitNormal = Vectormath::Scalar::Aos::normalize(normal);

		m_vertices[m_triangles[i].a].nx += unitNormal.getX();
		m_vertices[m_triangles[i].a].ny += unitNormal.getY();
		m_vertices[m_triangles[i].a].nz += unitNormal.getZ();

		m_vertices[m_triangles[i].b].nx += unitNormal.getX();
		m_vertices[m_triangles[i].b].ny += unitNormal.getY();
		m_vertices[m_triangles[i].b].nz += unitNormal.getZ();

		m_vertices[m_triangles[i].c].nx += unitNormal.getX();
		m_vertices[m_triangles[i].c].ny += unitNormal.getY();
		m_vertices[m_triangles[i].c].nz += unitNormal.getZ();
	}

	normalizeNormals();
}


void ptModel::normalizeNormals()
{

	Vector3 sumNormal;
	Vector3 unitSumNormal;

	for (int i = 0; i < m_vertexCount; i++)
	{
		sumNormal.setX(m_vertices[i].nx);
		sumNormal.setY(m_vertices[i].ny);
		sumNormal.setZ(m_vertices[i].nz);

		unitSumNormal = Vectormath::Scalar::Aos::normalize(sumNormal);

		m_vertices[i].nx = unitSumNormal.getX();
		m_vertices[i].ny = unitSumNormal.getY();
		m_vertices[i].nz = unitSumNormal.getZ();
	}
}

//*************************************************************************************//






int ptModel::loadModelOBJ(const char* _filename, LinearAllocator* _garlicAlloc)
{
	int l_error = SCE_OK;
	danFileParser myDFP;
	LinearAllocator myOnionAllocator;
	int l_pCount = 0;					//vertex positions
	int l_uCount = 0;					//vertex texture coordinates
	int l_nCount = 0;					//vertex normals
	int l_fCount = 0;					//faces
	int l_tCount = 0;					//triangles
	int l_vCount = 0;					//vertex index sets
	char l_lineType[50];		   		//read in the data type
	char l_vertexString[50];			//for vertex-index triples
	float l_A = 0, l_B = 0, l_C = 0;	//for float data
	int l_smoothingGroup;				//keep a track of the smoothing group
	m_centralizePositions = true;
	m_normalizePositions = true;

	l_error = myOnionAllocator.initialize(m_onionMemorySize, SCE_KERNEL_WB_ONION, SCE_KERNEL_PROT_CPU_RW | SCE_KERNEL_PROT_GPU_ALL);

	if (l_error != SCE_OK)
	{
		printf("Onion allocator failed to initialise 0x%08X\n", l_error);
		return l_error;
	}

	l_error = myDFP.openFile(_filename);

	if (l_error != SCE_OK)
	{
		printf("Unable to load file in model\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	while (!myDFP.atEOF())
	{
		if (myDFP.getWord(l_lineType)) // Only runs block if a valid char is found
		{
			if (myDFP.stringCompare(l_lineType, "v"))
			{
				l_pCount++;
			} // if
			else if (myDFP.stringCompare(l_lineType, "vt"))
			{
				l_uCount++;
			} // else if
			else if (myDFP.stringCompare(l_lineType, "vn"))
			{
				l_nCount++;
			} // else if
			else if (myDFP.stringCompare(l_lineType, "f"))
			{
				int counter = 0;
				while (myDFP.getWordNoNewLine(l_vertexString))
				{
					counter++;
				} // while
				l_vCount += counter;
				l_tCount += counter - 2;
				l_fCount++;
			} // else if
			myDFP.nextLine(); // Calls the next line in the file
		} //while
	}

	if (m_verbose) printf("Found %i positions, %i texcoords and %i normals\n", l_pCount, l_uCount, l_nCount);
	if (m_verbose) printf("Found %i triangles, in %i faces (using %i vertices)\n", l_tCount, l_fCount, l_vCount);

	m_vertexCount = l_pCount;
	m_indexCount = l_tCount * 3;

	if (l_nCount == 0)
	{
		m_generateNormals = true;
	}

	// danObjPosition
	size_t t_objPosSize = l_pCount * sizeof(danObjPosition);
	danObjPosition* l_objPositions = (danObjPosition*)myOnionAllocator.allocate(t_objPosSize, Gnm::kAlignmentOfBufferInBytes);
	if (!l_objPositions)
	{
		printf("Unable to allocate memory for ObjPositions in ptModel::loadModelOBJ\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	// danObjNormal
	size_t t_objNormalSize = l_nCount * sizeof(danObjNormal);
	danObjNormal* l_objNormals = (danObjNormal*)myOnionAllocator.allocate(t_objNormalSize, Gnm::kAlignmentOfBufferInBytes);
	if (!l_objNormals)
	{
		printf("Unable to allocate memory for ObjNormals in ptModel::loadModelOBJ\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	// danObjTexcoord
	size_t t_objTexcoordSize = l_uCount * sizeof(danObjTexcoord);
	danObjTexcoord* l_objTexcoords = (danObjTexcoord*)myOnionAllocator.allocate(t_objTexcoordSize, Gnm::kAlignmentOfBufferInBytes);
	if (!l_objTexcoords)
	{
		printf("Unable to allocate memory for ObjTexcoord in ptModel::loadModelOBJ\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	// danObjTriple
	size_t t_objTripleSize = l_vCount * sizeof(danObjTriple);
	danObjTriple* l_objTriples = (danObjTriple*)myOnionAllocator.allocate(t_objTripleSize, Gnm::kAlignmentOfBufferInBytes);
	if (!l_objTriples)
	{
		printf("Unable to allocate memory for ObjTriples in ptModel::loadModelOBJ\n");
		return SCE_ERROR_ERROR_FLAG;
	}


	//m_pIndices memory. This is will eventually be the final index data
	//indices will start by using indices to danObjTriple objects
	m_indicesSize = sizeof(uint16_t) * m_indexCount;
	m_indices = (uint16_t*)myOnionAllocator.allocate(m_indicesSize, Gnm::kAlignmentOfBufferInBytes);
	if (!m_indices)
	{
		printf("Unable to allocate memory for m_indices in ptModel::loadModelOBJ\n");
		return SCE_ERROR_ERROR_FLAG;
	}
	m_triangles = (ptTriangle*)m_indices;

	if (l_nCount == 0)
	{
		m_generateNormals = true;
	}


	//Create a dynamic array of bools for integrity checking
	bool* t_uCheck = new bool[m_vertexCount];

	//Set all elements to false
	for (int i = 0; i < m_vertexCount; i++)
	{
		t_uCheck[i] = false;
	}

	myDFP.reset();
	l_pCount = 0;					//vertex positions
	l_uCount = 0;					//vertex texture coordinates
	l_nCount = 0;					//vertex normals
	l_fCount = 0;					//faces
	l_tCount = 0;					//triangles
	l_vCount = 0;					//vertex index sets

									// Second Pass
	while (!myDFP.atEOF())
	{
		if (myDFP.getWord(l_lineType)) // Only runs block if a valid char is found
		{
			if (myDFP.stringCompare(l_lineType, "v")) // Vertex positions
			{

				if (myDFP.getFloat(l_A) && myDFP.getFloat(l_B) && myDFP.getFloat(l_C))
				{
					l_objPositions[l_pCount].x = l_A;
					l_objPositions[l_pCount].y = l_B;
					l_objPositions[l_pCount].z = l_C;

					if (m_verbose)
					{
						printf("<V> Position[%i] = (%i, %i, %i)\n", (int)l_pCount, (int)l_A, (int)l_B, (int)l_C);
					} //if
					l_pCount++;
				} // if

			} // if
			else if (myDFP.stringCompare(l_lineType, "vt")) // Vertex textures
			{

				if (myDFP.getFloat(l_A) && myDFP.getFloat(l_B))
				{


					t_uCheck[l_uCount] = true;      //Set to true as data is valid

					l_objTexcoords[l_uCount].u = l_A;
					l_objTexcoords[l_uCount].v = l_B;

					if (m_verbose)
					{
						printf("<VT> Texcoord[%i] = (%i, %i)\n", (int)l_uCount, (int)l_A, (int)l_B);
					} //if
					l_uCount++;
				} // if

			} // else if
			else if (myDFP.stringCompare(l_lineType, "vn")) // Vertex normals
			{

				if (myDFP.getFloat(l_A) && myDFP.getFloat(l_B) && myDFP.getFloat(l_C))
				{
					l_objNormals[l_nCount].x = l_A;
					l_objNormals[l_nCount].y = l_B;
					l_objNormals[l_nCount].z = l_C;

					if (m_verbose)
					{
						printf("<VN> Normal[%i] = (%i, %i, %i)\n", (int)l_nCount, (int)l_A, (int)l_B, (int)l_C);
					} //if
					l_nCount++;
				} // if

			} // else if
			else if (myDFP.stringCompare(l_lineType, "s"))
			{
				if (myDFP.getFloat(l_A))
				{
					if ((l_A < 0) || (l_A > __UINT16_MAX__) || !l_A)
					{
						l_smoothingGroup = 0;
					}
					l_smoothingGroup = l_A;
					if (m_verbose)
					{
						// printf("<S> Smoothing Group: [%i]\n", (int)l_A);
					} //if
				}
			} // else if
			else if (myDFP.stringCompare(l_lineType, "f"))
			{

				int t_counter = 0;
				int t_triA = l_vCount;

				//parse index data into our ptObjTriples structure
				while (myDFP.getWordNoNewLine(l_vertexString))
				{
					l_objTriples[l_vCount].parseTriple(l_vertexString, l_pCount, l_uCount, l_nCount, l_smoothingGroup);
					t_counter++;
					l_vCount++;
				}

				//create triangles from faces
				//this is tricky to work out the logic, basically a face is a triangle fan
				int t_secondCounter = 2;
				while (t_secondCounter < t_counter)
				{
					m_triangles[l_tCount].a = t_triA;
					m_triangles[l_tCount].b = t_triA + t_secondCounter - 1;
					m_triangles[l_tCount].c = t_triA + t_secondCounter;
					t_secondCounter++;
					l_tCount++;
				}//while
				l_fCount++;

			} // else if
		}
		myDFP.nextLine(); // Calls the next line in the file
	}//while

	//stage to compress data, by removing duplicate triples
	if (!m_verbose)
	{
		printf("Compressing triples data to remove duplicates. Please wait\n");
	}


	//find duplicates
	for (int i = 0; i < l_vCount; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (l_objTriples[i].matchAndMark(&l_objTriples[j], j))
			{
				if (m_verbose) printf("Triple %i is a duplicate of %i\n", i, j);
				j = i;
			}
		} // for
		
	} // for

	printf("DONE!!\n");

	  //Checking if all Texcoords are present
	for (int i = 0; i < m_vertexCount; i++)
	{
		int temp = 0;

		if (t_uCheck[i] == false)
		{
			temp++;
		}

		if (temp == 0)
		{
			m_gotTexcoords = true;
		}
	}


	//mark "real index" on originals by counting through them
	int l_rCount = 0;
	for (int i = 0; i < l_vCount; i++)
	{
		if (!l_objTriples[i].m_duplicate)
		{
			l_objTriples[i].m_realIndex = l_rCount;
			l_rCount++;
		} //if
	} //for


	  //create memory for final vertex data
	m_vertexCount = l_rCount;
	m_verticesSize = sizeof(ptVertex)*m_vertexCount;
	m_vertices = (ptVertex*)myOnionAllocator.allocate(m_verticesSize, Gnm::kAlignmentOfBufferInBytes);
	if (!m_vertices)
	{
		printf("Unable to allocate memory for m_vertices in ptModel::loadModelOBJ\n");
		return SCE_ERROR_ERROR_FLAG;
	}


	//copy vertex data from intermediate arrays to final array 
	//use counter to ONLY transfer the originals and not duplicates 
	int t_counter = 0;
	for (int i = 0; i < l_vCount; i++)
	{
		if (!l_objTriples[i].m_duplicate)
		{
			if (l_objTriples[i].m_gotPosition)
			{
				m_vertices[t_counter].x = l_objPositions[l_objTriples[i].m_positionIndex].x;
				m_vertices[t_counter].y = l_objPositions[l_objTriples[i].m_positionIndex].y;
				m_vertices[t_counter].z = l_objPositions[l_objTriples[i].m_positionIndex].z;
			} //if
			if (l_objTriples[i].m_gotNormal)
			{
				m_vertices[t_counter].nx = l_objNormals[l_objTriples[i].m_normalIndex].x;
				m_vertices[t_counter].ny = l_objNormals[l_objTriples[i].m_normalIndex].y;
				m_vertices[t_counter].nz = l_objNormals[l_objTriples[i].m_normalIndex].z;
			} //if
			if (l_objTriples[i].m_gotTexcoord)
			{
				m_vertices[t_counter].u = l_objTexcoords[l_objTriples[i].m_texcoordIndex].u;
				m_vertices[t_counter].v = l_objTexcoords[l_objTriples[i].m_texcoordIndex].v;

			} //if

			t_counter++;
		} //if
	} //for




	//correct indices in m_indices to point to correct places in m_vertices
	for (int i = 0; i < m_indexCount; i++)
	{
		if (l_objTriples[m_indices[i]].m_duplicate)
		{
			m_indices[i] = l_objTriples[l_objTriples[m_indices[i]].m_duplicateIndex].m_realIndex;
		} // if
		else
		{
			m_indices[i] = l_objTriples[m_indices[i]].m_realIndex;
		} // else
	} // for



	 //Generate normals if defined 
	if (m_generateNormals)
	{
		generateNormals();
	}

	//Centralise and normalise positions if defined
	if (m_centralizePositions && m_normalizePositions)
	{
		centralizePositions();
		normalizePositions();
	}

	//copying data to the GPU
	l_error = copyDataToGPU(_garlicAlloc);
	if (l_error != SCE_OK) { printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error);  return l_error; }

	


	m_validData = true;
	myOnionAllocator.terminate();

	return l_error;
} // loadModelOBJ





void ptModel::printPositions()
{
	for (int i = 0; i < m_vertexCount; i++)
	{
		printf("P %i %f %f %f\n", i, l_gpuVertexData[i].x, l_gpuVertexData[i].y, l_gpuVertexData[i].z);

	}//for
}

void ptModel::printNormals()
{
	for (int i = 0; i < m_vertexCount; i++)
	{
		printf("N %i %f %f %f\n", i, l_gpuVertexData[i].nx, l_gpuVertexData[i].ny, l_gpuVertexData[i].nz);
	}
}

void ptModel::printColours()
{
	for (int i = 0; i < m_vertexCount; i++)
	{
		printf("C %i %f %f %f\n", i, l_gpuVertexData[i].r, l_gpuVertexData[i].g, l_gpuVertexData[i].b);
	}

}


void ptModel::printTexcoords()
{
	for (int i = 0; i < m_vertexCount; i++)
	{
		printf("U %i %f %f\n", i, l_gpuVertexData[i].u, l_gpuVertexData[i].v);
	}
}

void ptModel::printTriangles()
{
	for (int i = 0; i < m_indexCount / 3; i++)
	{
		printf("T %i %i %i %i\n", i, m_triangles[i].a, m_triangles[i].b, m_triangles[i].c);
	}
}

void ptModel::convertToPTM()
{
	printPositions();

	printNormals();

	//printColours();

	printTexcoords();

	printTriangles();
}
///////////////////////////////////////////////////////////////////////////////////////////////////


//Load Model in from a file
//Parameter: _fileName is the name of the file to be read from
//Parameter: _garlicAlloc is the garlic memory allocator
int ptModel::loadModelPTM(const char* _fileName, LinearAllocator* _garlicAlloc)
{
	int l_error = SCE_OK;     //Error flag
	char l_lineType;          //Stores the character in file being pointed to by cursor
	int l_pCount = 0;           //Number of vertex positions 
	int l_cCount = 0;           //Number of vertex colours 
	int l_tCount = 0;           //Number of triangle descriptions 
	int l_nCount = 0;           //Number of normals
	int l_uCount = 0;           //Number of texcoords
	int l_index = 0;         //Vertex Index
	int l_indexCheck = 0;
	float l_X = 0;              //Vertex X value
	float l_Y = 0;              //Vertex Y value
	float l_Z = 0;              //Vertex Z value
	float l_r = 0;              //Vertex X value
	float l_g = 0;              //Vertex Y value
	float l_b = 0;              //Vertex Z value
	int l_A = 0;                //A vertex position for triangle
	int l_B = 0;				//B vertex position for triangle
	int l_C = 0;				//C vertex position for triangle 
	char l_word[50];



	//Lets have our own memory allocator
	LinearAllocator myOnionAllocator;
	l_error = myOnionAllocator.initialize(m_onionMemorySize, SCE_KERNEL_WB_ONION, SCE_KERNEL_PROT_CPU_RW | SCE_KERNEL_PROT_GPU_ALL);
	if (l_error != SCE_OK)
	{
		printf("Onion allocator failed to initialise: 0x%08X\n", l_error);
		return l_error;
	}


	//file parser
	danFileParser myDFP;
	l_error = myDFP.openFile(_fileName);
	if (l_error != SCE_OK)                       //Checking if load was successful
	{
		printf("Unable to load file in model\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	while (!myDFP.atEOF())                  //Run through file until it ends
	{
		if (myDFP.getChar(l_lineType))      //If data is a char
		{
			switch (l_lineType)
			{
			case 'P':
				l_pCount++;
				break;
			case 'C':
				l_cCount++;
				break;
			case 'T':
				l_tCount++;
				break;
			case 'X':
				if (myDFP.getWord(l_word))
				{
					if (myDFP.stringCompare(l_word, "GEN_SEQUENTIAL_TRIS"))
					{
						m_genSequentialTris = true;
					}

					if (myDFP.stringCompare(l_word, "CENTRALIZE"))
					{
						m_centralizePositions = true;
					}

					if (myDFP.stringCompare(l_word, "NORMALIZE"))
					{
						m_normalizePositions = true;
					}

					if (myDFP.stringCompare(l_word, "GEN_SPLAYED_NORMALS"))
					{
						m_generateNormals = true;
					}

					if (myDFP.stringCompare(l_word, "GEN_NORMALS"))
					{
						m_generateNormals = true;
					}

					if (myDFP.stringCompare(l_word, "SINGLE_COLOUR"))
					{
						m_oneColour = true;
					}

					if (myDFP.stringCompare(l_word, "NO_COLOUR"))
					{
						m_noColour = true;
					}

					if (myDFP.stringCompare(l_word, "RANDOM_COLOUR"))
					{
						m_useRandomColour = true;
					}
				}


				break;
			case 'N':
				l_nCount++;
				break;
			case 'U':
				l_uCount++;
				break;
			default:
				break;
			}
		}

		myDFP.nextLine();               //Move to next line of file
	}


	if (l_nCount != l_pCount)
	{
		m_generateNormals = true;
	}

	if (l_cCount == 0)
	{
		m_oneColour = true;
	}

	//If file is still being parsed 
	if (m_verbose)
	{
		printf("found %i positions, %i colours, %i normals in %i triangles\n", l_pCount, l_cCount, l_nCount, l_tCount);
	}

	m_vertexCount = l_pCount;                              //Set m_vertexCount to the number of vertex positions extracted 
	m_verticesSize = sizeof(ptVertex) * m_vertexCount;

	m_indexCount = l_tCount * 3;                           //Set m_indexCount to number of triangles detected * 3
	m_indicesSize = sizeof(uint16_t) * m_indexCount;


	//Allocate memory for the vertices
	m_vertices = (ptVertex*)myOnionAllocator.allocate(m_verticesSize, Gnm::kAlignmentOfBufferInBytes);

	if (!m_vertices)
	{
		printf("Unable to allocate memory for m_vertices in ptModel::loadModelPTM\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	//Allocate memory for indicies 
	m_indices = (uint16_t*)myOnionAllocator.allocate(m_indicesSize, Gnm::kAlignmentOfBufferInBytes);

	if (!m_indices)
	{
		printf("Unable to allocate memory for m_indicies in ptModel::loadModelPTM\n");
		return SCE_ERROR_ERROR_FLAG;
	}

	//Create a dynamic array of bools for integrity checking
	bool* t_pCheck = new bool[m_vertexCount];


	//Set all elements to false
	for (int i = 0; i < m_vertexCount; i++)
	{
		t_pCheck[i] = false;
	}

	//Create a dynamic array of bools for integrity checking
	bool* t_cCheck = new bool[m_vertexCount];


	//Set all elements to false
	for (int i = 0; i < m_vertexCount; i++)
	{
		t_cCheck[i] = false;
	}

	//Create a dynamic array of bools for integrity checking
	bool* t_tCheck = new bool[l_tCount];

	//Set all elements to false
	for (int i = 0; i < l_tCount; i++)
	{
		t_tCheck[i] = false;
	}


	//Create a dynamic array of bools for integrity checking
	bool* t_nCheck = new bool[l_nCount];

	//Set all elements to false
	for (int i = 0; i < m_vertexCount; i++)
	{
		t_nCheck[i] = false;
	}


	//Create a dynamic array of bools for integrity checking
	bool* t_uCheck = new bool[m_vertexCount];

	//Set all elements to false
	for (int i = 0; i < m_vertexCount; i++)
	{
		t_uCheck[i] = false;
	}





	//If file is still being parsed 
	if (m_verbose)
	{
		printf("Memory allocated: %i for vertices, %i for indices\n", (int)m_verticesSize, (int)m_indicesSize);
	}

	m_triangles = (ptTriangle*)m_indices;    //Set m_triangles to point to m_indicies using a cast 


	myDFP.reset();      //Reset file


						//Check if indicies are continous from 0
	int t_pContinuityCheck = 0;
	int t_cContinuityCheck = 0;
	int t_tContinuityCheck = 0;


	while (!myDFP.atEOF())     //Run through file
	{
		if (myDFP.getChar(l_lineType))        //Check file for char
		{
			switch (l_lineType)
			{
			case 'P':                                                                                                 //If char is 'P' get the following integers and 3 floats 
				if (myDFP.getInt(l_index) && myDFP.getFloat(l_X) && myDFP.getFloat(l_Y) && myDFP.getFloat(l_Z))
				{
					//Integrity check
					if (t_pContinuityCheck != l_index)
					{
						return SCE_ERROR_ERROR_FLAG;
					}

					t_pContinuityCheck = l_index;
					t_pContinuityCheck++;

					//Checking if index is out of range
					if (l_index > m_vertexCount)
					{
						printf("Position index out of range\n");
						return SCE_ERROR_ERROR_FLAG;
					}

					//Checking if data has been duplicated 
					if (t_pCheck[l_index])
					{
						printf("Duplicate position for index %i, replacing previous data\n", l_index);
					}

					t_pCheck[l_index] = true;      //Set to true as data is valid

												   //Set vertex position elements using extracted data
					m_vertices[l_index].x = l_X;
					m_vertices[l_index].y = l_Y;
					m_vertices[l_index].z = l_Z;

					if (m_verbose) printf("Position[%i] (%f, %f, %f)\n", l_index, l_X, l_Y, l_Z);
				}//if
				break;
			case 'C':
				if (myDFP.getInt(l_index) && myDFP.getFloat(l_r) && myDFP.getFloat(l_g) && myDFP.getFloat(l_b))
				{

					//Checking if memory is continous from 0
					if (t_cContinuityCheck != l_index)
					{
						printf("index is not continous from 0\n");
						return SCE_ERROR_ERROR_FLAG;
					}

					t_cContinuityCheck = l_index;    //Set to index
					t_cContinuityCheck++;            //Add one for nect check

													 //Checking if index is out of range
					if (l_index > m_vertexCount)
					{
						printf("Colour index out of range\n");
						return SCE_ERROR_ERROR_FLAG;
					}

					//Checking if data has been duplicated 
					if (t_cCheck[l_index])
					{
						printf("Duplicate position for index %i, replacing previous data\n", l_index);
					}//if



					 //If NO_COLOUR AND SINGLE_COLOUR hasnt been specified
					if (m_noColour == false && m_oneColour == false)
					{
						t_cCheck[l_index] = true;      //Set to true as data is valid

													   //Set vertex colour elements using extracted data
						m_vertices[l_index].r = l_r;
						m_vertices[l_index].g = l_g;
						m_vertices[l_index].b = l_b;

						if (m_verbose) printf("Colour[%i] (%f, %f, %f)\n", l_index, l_r, l_g, l_b);
					}//if
					 //If SINGLE_COLOUR has been defined
					else if (m_oneColour && l_index == 0)
					{
						t_cCheck[l_index] = true;      //Set to true as data is valid

													   //Set vertex colour elements using extracted data
						m_vertices[l_index].r = l_r;
						m_vertices[l_index].g = l_g;
						m_vertices[l_index].b = l_b;

						if (m_verbose) printf("Colour[%i] (%f, %f, %f)\n", l_index, l_r, l_g, l_b);
					}//else if
				}//if

				break;
			case 'T':


				if (!m_genSequentialTris)
				{
					//If char is 'T' get the following 4 integers
					if (myDFP.getInt(l_index) && myDFP.getInt(l_A) && myDFP.getInt(l_B) && myDFP.getInt(l_C))
					{


						if (l_index > l_tCount)
						{
							printf("Triangle index is out of range\n");
							return SCE_ERROR_ERROR_FLAG;
						}

						if (t_tCheck[l_index])
						{
							printf("Duplicate position for index %i, replacing previous data\n", l_index);
							return SCE_ERROR_ERROR_FLAG;
						}

						if (l_A < 0 || l_B < 0 || l_C < 0 || l_A >(m_vertexCount - 1)
							|| l_B >(m_vertexCount - 1) || l_C >(m_vertexCount - 1))
						{
							printf("A vertex index is out of range\n", l_index);
							return SCE_ERROR_ERROR_FLAG;
						}

						//Set triangle Vertex positions using extracted data
						m_triangles[l_index].a = l_A;
						m_triangles[l_index].b = l_B;
						m_triangles[l_index].c = l_C;

						if (m_verbose) printf("Triangle[%i] (%i, %i, %i)\n", l_index, l_A, l_B, l_C);
					}//if
				}
				break;
			case'N':
				if (myDFP.getInt(l_index) && myDFP.getFloat(l_X) && myDFP.getFloat(l_Y) && myDFP.getFloat(l_Z))
				{

					//Checking if index is out of range
					if (l_index > m_vertexCount)
					{
						printf("Normal index out of range\n");
						return SCE_ERROR_ERROR_FLAG;
					}

					//Checking if data has been duplicated 
					if (t_nCheck[l_index])
					{
						printf("Duplicate normal for index %i, replacing previous data\n", l_index);
					}

					t_nCheck[l_index] = true;      //Set to true as data is valid

												   //Set vertex position elements using extracted data
					m_vertices[l_index].nx = l_X;
					m_vertices[l_index].ny = l_Y;
					m_vertices[l_index].nz = l_Z;

					if (m_verbose) printf("Normal[%i] (%f, %f, %f)\n", l_index, l_X, l_Y, l_Z);
				}
				break;
			case 'U':
				if (myDFP.getInt(l_index) && myDFP.getFloat(l_X) && myDFP.getFloat(l_Y))
				{
					//Checking if index is out of range
					if (l_index > m_vertexCount)
					{
						printf("Normal index out of range\n");
						return SCE_ERROR_ERROR_FLAG;
					}

					//Checking if data has been duplicated 
					if (t_uCheck[l_index])
					{
						printf("Duplicate normal for index %i, replacing previous data\n", l_index);
					}

					t_uCheck[l_index] = true;      //Set to true as data is valid

					m_vertices[l_index].u = l_X;
					m_vertices[l_index].v = l_Y;
				}
				break;
			case 'X':


				if (myDFP.getWord(l_word))
				{
					if (myDFP.stringCompare(l_word, "SINGLE_COLOUR"))
					{
						m_oneColour = true;
					}//if
					else if (myDFP.stringCompare(l_word, "NO_COLOUR"))
					{
						m_noColour = true;
					}//else if


				}//if
				break;
			default:
				break;
			}//switch

		}//if

		myDFP.nextLine();     //Next line in file
	}//while



	 //Integrity check for vertex position
	for (int i = 0; i < m_vertexCount; i++)
	{
		if (t_pCheck[i] == false)
		{
			printf("Integrity error for vertex positions\n");
			return SCE_ERROR_ERROR_FLAG;
		}
	}


	//Checking if all Texcoords are present
	for (int i = 0; i < m_vertexCount; i++)
	{
		int temp = 0;

		if (t_uCheck[i] == false)
		{
			temp++;
		}

		if (temp == 0)
		{
			m_gotTexcoords = true;
		}
	}




	//Integrity check for vertex colour 
	//If one colour is true and and no colour has 
	//been assigned to the first vertex
	if (m_oneColour && !t_cCheck[0])
	{
		m_oneColour = false;
		m_noColour = true;
	}

	//Integrity Check for vertex colour
	if (m_oneColour == false && m_noColour == false)
	{
		for (int i = 0; i < m_vertexCount; i++)
		{
			if (t_cCheck[i] = false)
			{
				m_vertices[i].r = m_defaultColour[0];
				m_vertices[i].g = m_defaultColour[1];
				m_vertices[i].b = m_defaultColour[2];
			}
		}
	}






	//If SINGLE_COLOUR fill vertices with first vertex colour
	if (m_oneColour)
	{
		fillColour(Vector3(m_vertices[0].r, m_vertices[0].g, m_vertices[0].b));
		printf("SINGLE COLOUR\n");
	}//if
	 //If NO_COLOUR fill vertices with default colour
	else if (m_noColour)
	{
		printf("NO COLOUR\n");
		fillColour(m_defaultColour);
	}//else if


	//Generate sequential triangles if defined
	if (m_genSequentialTris)
	{
		generateSeqTriangles(&myOnionAllocator);
		printf("Sequential Triangles Generated\n");
	}


	//Generate Normals if defined 
	if (m_generateNormals)
	{
		generateNormals();
		printf("Normals have been generated\n");
	}




	//Centralise and normalise positions if defined
	if (m_centralizePositions && m_normalizePositions)
	{
		centralizePositions();
		normalizePositions();

	}

	//Fill with random colour if defined
	if (m_useRandomColour)
	{
		fillRandomColour();
	}
	


	//copy data to garlic memory
	l_error = copyDataToGPU(_garlicAlloc);
	if (l_error != SCE_OK) { printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error);  return l_error; }


	//terminate our local memory allocator 
	myOnionAllocator.terminate();


	//leave this near end to protect against bad data      
	if ((m_vertexCount > 2) && (m_indexCount > 2))
	{
		m_validData = true;
	}

	delete[] t_pCheck;
	delete[] t_cCheck;
	delete[] t_tCheck;

	return l_error;        //Return 
}


//***************************************************************//
//fills models with specified colour
void ptModel::fillColour(Vector3 _colour)
{
	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertices[i].r = _colour.getX().getAsFloat();
		m_vertices[i].g = _colour.getY().getAsFloat();
		m_vertices[i].b = _colour.getZ().getAsFloat();
	}

	printf("Colour of model has been set to {%f, %f, %f}\n"),
		m_vertices[0].r, m_vertices[0].g, m_vertices[0].b;
}



void ptModel::fillRandomColour()
{
	danRandom l_Random;
	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertices[i].r = l_Random.getFraction();
		m_vertices[i].g = l_Random.getFraction();
		m_vertices[i].b = l_Random.getFraction();
	}//for

	printf("Colour of model has been set randomly\n");
}//fillColour()



void ptModel::generateSeqTriangles(LinearAllocator* _onionAllocator)
{

	for (int i = 0; i < m_vertexCount; i++)
	{
		m_indices[i] = i;
	}

	m_indicesSize = sizeof(uint16_t) * m_vertexCount;

	m_indices = (uint16_t*)_onionAllocator->allocate(m_indicesSize, Gnm::kAlignmentOfBufferInBytes);
}



////////////////////////////////////////////////////////////////////////////////
void ptModel::loadHardModel(PT_HARD_MODEL _model, LinearAllocator* _garlicAlloc)
{
	switch (_model)
	{
	case PT_HARD_MODEL::CUBE:
		m_vertices = sc_vertexDataCube;
		m_verticesSize = sizeof(sc_vertexDataCube);
		m_indices = sc_indexDataCube;
		m_indicesSize = sizeof(sc_indexDataCube);

		break;
	case PT_HARD_MODEL::TETRA:
		m_vertices = sc_vertexDataTetra;
		m_verticesSize = sizeof(sc_vertexDataTetra);
		m_indices = sc_indexDataTetra;
		m_indicesSize = sizeof(sc_indexDataTetra);
		break;
	case PT_HARD_MODEL::OCTA:
		m_vertices = sc_vertexDataOCTA;
		m_verticesSize = sizeof(sc_vertexDataOCTA);
		m_indices = sc_indexDataOCTA;
		m_indicesSize = sizeof(sc_indexDataOCTA);
		break;
	case PT_HARD_MODEL::ICOS:
		m_vertices = sc_vertexDataIcos;
		m_verticesSize = sizeof(sc_vertexDataIcos);
		m_indices = sc_indexDataIcos;
		m_indicesSize = sizeof(sc_indexDataIcos);
		break;
	case PT_HARD_MODEL::CUBE_PVC:
		m_vertices = sc_vertexDataCube_pvc;
		m_verticesSize = sizeof(sc_vertexDataCube_pvc);
		m_indices = sc_indexDataCube_pvc;
		m_indicesSize = sizeof(sc_indexDataCube_pvc);
		break;
	case PT_HARD_MODEL::TETRA_PVC:
		m_vertices = sc_vertexDataTetra_pvc;
		m_verticesSize = sizeof(sc_vertexDataTetra_pvc);
		m_indices = sc_indexDataTetra_pvc;
		m_indicesSize = sizeof(sc_indexDataTetra_pvc);
		break;
	case PT_HARD_MODEL::OCTA_PVC:
		break;
	case PT_HARD_MODEL::ICOS_PVC:
		m_vertices = sc_vertexDataIcos_pvc;
		m_verticesSize = sizeof(sc_vertexDataIcos_pvc);
		m_indices = sc_indexDataIcos_pvc;
		m_indicesSize = sizeof(sc_indexDataIcos_pvc);
		break;
	default:
		printf("No model data found\n");
		break;
	}


	m_vertexCount = (m_verticesSize / sizeof(m_vertices[0]));
	m_indexCount = (m_indicesSize / sizeof(m_indices[0]));




	int result = copyDataToGPU(_garlicAlloc);


	if (result == SCE_OK && m_vertexCount >= 3 && m_indexCount >= 3)
	{
		m_validData = true;
	}


}//loadHardModel()



 ////////////////////////////////////////////////////////////////////


int ptModel::copyDataToGPU(LinearAllocator* _garlicAlloc)
{

	//the data created above for the model (vertex and index data)
	//needs to be copied across to "garlic" memory to be fast-accessible by the shaders.

	// Allocate the vertex buffer memory
	l_gpuVertexData = static_cast<ptVertex*>(_garlicAlloc->allocate(m_verticesSize, Gnm::kAlignmentOfBufferInBytes));
	if (!l_gpuVertexData) { printf("Cannot allocate vertex data\n"); return SCE_KERNEL_ERROR_ENOMEM; }


	// Allocate the index buffer memory
	l_gpuIndexData = static_cast<uint16_t*>(_garlicAlloc->allocate(m_indicesSize, Gnm::kAlignmentOfBufferInBytes));
	if (!l_gpuIndexData) { printf("Cannot allocate index data\n"); return SCE_KERNEL_ERROR_ENOMEM; }


	// Copy the vertex/index data onto the GPU mapped memory
	memcpy(l_gpuVertexData, m_vertices, m_verticesSize);
	memcpy(l_gpuIndexData, m_indices, m_indicesSize);

	initVertexBuffer();

	int l_result = SCE_OK;

	return l_result;

}//copyDataToGPU()

 /////////////////////////////////////////////////////////////////

void ptModel::initVertexBuffer()
{
	// Initialize the vertex buffers pointing to each vertex element
	// these are used to map the input data to the vertex shader 
	myVertexBuffers[PT_VERTEX_POSITION].initAsVertexBuffer(
		&l_gpuVertexData->x,
		Gnm::kDataFormatR32G32B32Float,
		sizeof(m_vertices[0]),
		m_vertexCount);
	myVertexBuffers[PT_VERTEX_COLOUR].initAsVertexBuffer(
		&l_gpuVertexData->r,
		Gnm::kDataFormatR32G32B32Float,
		sizeof(m_vertices[0]),
		m_vertexCount);
	myVertexBuffers[PT_VERTEX_NORMAL].initAsVertexBuffer(
		&l_gpuVertexData->nx,
		Gnm::kDataFormatR32G32B32Float,
		sizeof(m_vertices[0]),
		m_vertexCount);
	myVertexBuffers[PT_VERTEX_TEXCOORDS].initAsVertexBuffer(
		&l_gpuVertexData->u,
		Gnm::kDataFormatR32G32Float,
		sizeof(m_vertices[0]),
		m_vertexCount);

}