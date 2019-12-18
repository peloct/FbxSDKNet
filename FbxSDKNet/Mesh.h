#pragma once

#include <fbxsdk.h>
#include "Types.h"
#include "NodeAttribute.h"

using namespace System;

namespace FbxSDK
{
	ref class Skin;

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
		int GetControlPointsCount();
		int GetPolygonCount();
		int GetElementCount(VertexElementType elementType);
		Vector3 GetControlPoint(int controlPointIndex);
		int GetControlPointIndex(int polygonIndex, int positionInPolygon);
		Vector3 GetCoordinate(int polygonIndex, int positionInPolygon);
		Vector3 GetNormal(int elementIndex, int polygonIndex, int positionInPolygon);
		Vector3 GetBinormal(int elementIndex, int polygonIndex, int positionInPolygon);
		Vector3 GetTangent(int elementIndex, int polygonIndex, int positionInPolygon);
		Vector2 GetUV(int elementIndex, int polygonIndex, int positionInPolygon);
		Color GetColor(int elementIndex, int polygonIndex, int positionInPolygon);
		int GetMaterialMapping(int elementIndex, int polygonIndex);
		int GetSkinDeformerCount();
		Skin^ GetSkinDeformer(int skinDeformerIndex);
		// No support for a "VertexCache" and "Shape" deformer at the moment
	};
}