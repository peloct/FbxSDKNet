#pragma once

#include <fbxsdk.h>
#include "Types.h"
#include "NodeAttribute.h"

using namespace System;

namespace FbxSDK
{
	ref class Cluster;

	public enum class VertexElementType
	{
		Normal,
		Binormal,
		Tangent,
		UV,
		Color,
		MaterialMapping
	};

	public ref class Mesh : NodeAttribute
	{
	private:
		FbxMesh* mesh;

	internal:
		Mesh(Node^ node, FbxMesh* mesh) : NodeAttribute(node, mesh), mesh(mesh) {}

	public:
		int GetPolygonCount();
		int GetElementCount(VertexElementType elementType);
		Vector3 GetCoordinate(int polygonIndex, int positionInPolygon);
		Vector3 GetNormal(int elementIndex, int polygonIndex, int positionInPolygon);
		Vector3 GetBinormal(int elementIndex, int polygonIndex, int positionInPolygon);
		Vector3 GetTangent(int elementIndex, int polygonIndex, int positionInPolygon);
		Vector2 GetUV(int elementIndex, int polygonIndex, int positionInPolygon);
		Color GetColor(int elementIndex, int polygonIndex, int positionInPolygon);
		int GetMaterialMapping(int elementIndex, int polygonIndex);
		int GetSkinDeformerCount();
		int GetClusterCount(int skinDeformerIndex);
		Cluster^ GetCluster(int skinDeformerIndex, int clusterIndex);
	};
}