#include "Mesh.h"

using namespace FbxSDK;

Mesh::Mesh(FbxMesh* mesh) : mesh(mesh)
{
	int polygonCount = mesh->GetPolygonCount();
	int* vertices = mesh->GetPolygonVertices();

	int controlPointsCount = mesh->GetControlPointsCount();

	for (int i = 0; i < controlPointsCount; ++i)
	{
		FbxVector4 vec = mesh->GetControlPointAt(i);
	}

	for (int i = 0; i < polygonCount; ++i)
	{
		float normal[3];
		float tangent[3];
		float binormal[3];
		float UV[3][2];

		for (int j = 0; j < 3; ++j)
		{
			int vertex = mesh->GetPolygonVertex(i, j);
		}
	}
}