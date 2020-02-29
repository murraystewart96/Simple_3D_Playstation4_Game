#ifndef __PT_VERTEX__
#define __PT_VERTEX__





// struct to hold vertex data. Needs to reflect the input to the vertex shader, ptVSInput
struct ptVertex
{
	float x, y, z;	// Position
	float r, g, b;	// Color
	float nx, ny, nz; //Normal
	float u, v;     //Texcoords

};//struct

  //a list of the vertex data elements
enum ptVertexElements
{
	PT_VERTEX_POSITION = 0,
	PT_VERTEX_COLOUR,
	PT_VERTEX_NORMAL,
	PT_VERTEX_TEXCOORDS,
	PT_VERTEX_ELEM_COUNT
};//enum
    


struct ptTriangle
{
	uint16_t a, b, c;
};

#endif