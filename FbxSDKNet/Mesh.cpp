#include "pch.h"
#include "Mesh.h"
#include "Utils.h"
#include <string>

using namespace FbxSDK;
using namespace System;
using namespace System::Collections::Generic;

Vector3^ ReadNormal(FbxMesh* mesh, int controlPointIndex, int vertexIndex);
Vector3^ ReadBinormal(FbxMesh* mesh, int controlPointIndex, int vertexIndex);
Vector3^ ReadTangent(FbxMesh* mesh, int controlPointIndex, int vertexIndex);
Vector2^ ReadUV(FbxMesh* mesh, int controlPointIndex, int uvIndex);

template <typename GeometryElement, unsigned int Dimmension>
bool ReadGeometryElement(GeometryElement* geometryElement, int controlPointIndex, int vertexIndex, float& x, float& y, float& z);

String^ Vector2::ToString()
{
	std::string str = "{ " + std::to_string(x) + ", " + std::to_string(y) + " }";
	return gcnew String(str.c_str());
}

String^ Vector3::ToString()
{
	std::string str = "{ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " }";
	return gcnew String(str.c_str());
}

Mesh::Mesh(FbxMesh* mesh) : mesh(mesh)
{
	FbxVector4* controlPoints = mesh->GetControlPoints();

	int polygonCount = mesh->GetPolygonCount();

	bool hasNoraml = mesh->GetElementNormalCount() > 0;
	bool hasBinormal = mesh->GetElementBinormalCount() > 0;
	bool hasTangent = mesh->GetElementTangentCount() > 0;
	bool hasUV = mesh->GetElementUVCount() > 0;

	bool hasPerVertexElement = false;

	if (hasNoraml)
		hasPerVertexElement |= mesh->GetElementNormal(0)->GetMappingMode() == FbxGeometryElement::eByPolygonVertex;
	if (hasBinormal)
		hasPerVertexElement |= mesh->GetElementBinormal(0)->GetMappingMode() == FbxGeometryElement::eByPolygonVertex;
	if (hasNoraml)
		hasPerVertexElement |= mesh->GetElementTangent(0)->GetMappingMode() == FbxGeometryElement::eByPolygonVertex;
	if (hasNoraml)
		hasPerVertexElement |= mesh->GetElementUV(0)->GetMappingMode() == FbxGeometryElement::eByPolygonVertex;

	vertices = gcnew array<Vector3>(3 * polygonCount);
	if (hasNoraml)
		normals = gcnew array<Vector3>(3 * polygonCount);
	if (hasBinormal)
		binoramls = gcnew array<Vector3>(3 * polygonCount);
	if (hasTangent)
		tangents = gcnew array<Vector3>(3 * polygonCount);
	if (hasUV)
		uvs = gcnew array<Vector2>(3 * polygonCount);

	int vertexIndex = 0;

	for (int i = 0; i < polygonCount; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int controlPointIndex = mesh->GetPolygonVertex(i, j);
			FbxVector4* point = &controlPoints[controlPointIndex];
			Vector3^ position = gcnew Vector3(point->mData[0], point->mData[1], point->mData[2]);
			Vector3^ normal = ReadNormal(mesh, controlPointIndex, vertexIndex);
			Vector3^ binormal = ReadBinormal(mesh, controlPointIndex, vertexIndex);
			Vector3^ tangent = ReadTangent(mesh, controlPointIndex, vertexIndex);
			Vector2^ uv = ReadUV(mesh, controlPointIndex, mesh->GetTextureUVIndex(i, j));

			vertices[vertexIndex++] = gcnew Vertex(position, normal, binormal, tangent, uv);
		}
	}
}

String^ Mesh::GetName()
{
	return gcnew String(mesh->GetName());
}

Vector3^ ReadNormal(FbxMesh* mesh, int controlPointIndex, int vertexIndex)
{
	if (mesh->GetElementNormalCount() < 1)
		return nullptr;

	FbxGeometryElementNormal* normal = mesh->GetElementNormal(0);
	float x, y, z;
	if (ReadGeometryElement<FbxGeometryElementNormal, 3>(normal, controlPointIndex, vertexIndex, x, y, z))
		return gcnew Vector3(x, y, z);

	return nullptr;
}

Vector3^ ReadBinormal(FbxMesh* mesh, int controlPointIndex, int vertexIndex)
{
	if (mesh->GetElementBinormalCount() < 1)
		return nullptr;

	FbxGeometryElementBinormal* binormal = mesh->GetElementBinormal(0);
	float x, y, z;
	if (ReadGeometryElement<FbxGeometryElementBinormal, 3>(binormal, controlPointIndex, vertexIndex, x, y, z))
		return gcnew Vector3(x, y, z);

	return nullptr;
}

Vector3^ ReadTangent(FbxMesh* mesh, int controlPointIndex, int vertexIndex)
{
	if (mesh->GetElementTangentCount() < 1)
		return nullptr;

	FbxGeometryElementTangent* tangent = mesh->GetElementTangent(0);
	float x, y, z;
	if (ReadGeometryElement<FbxGeometryElementTangent, 3>(tangent, controlPointIndex, vertexIndex, x, y, z))
		return gcnew Vector3(x, y, z);

	return nullptr;
}

Vector2^ ReadUV(FbxMesh* mesh, int controlPointIndex, int uvIndex)
{
	if (mesh->GetElementUVCount() < 1)
		return nullptr;

	FbxGeometryElementUV* uv = mesh->GetElementUV(0);
	float x, y, z;
	if (ReadGeometryElement<FbxGeometryElementUV, 2>(uv, controlPointIndex, uvIndex, x, y, z))
		return gcnew Vector2(x, y);

	return nullptr;
}

template <typename GeometryElement, unsigned int Dimmension>
bool ReadGeometryElement(GeometryElement* geometryElement, int controlPointIndex, int vertexIndex, float& x, float& y, float& z)
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;

	switch (geometryElement->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:
		switch (geometryElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			x = geometryElement->GetDirectArray().GetAt(controlPointIndex).mData[0];
			y = geometryElement->GetDirectArray().GetAt(controlPointIndex).mData[1];
			z = Dimmension >= 3 ? geometryElement->GetDirectArray().GetAt(controlPointIndex).mData[2] : 0.0f;
			return true;
		}
		break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = geometryElement->GetIndexArray().GetAt(controlPointIndex);
			x = geometryElement->GetDirectArray().GetAt(index).mData[0];
			y = geometryElement->GetDirectArray().GetAt(index).mData[1];
			z = Dimmension == 3 ? geometryElement->GetDirectArray().GetAt(index).mData[2] : 0;
			return true;
		}
		break;
		}
		break;
	case FbxGeometryElement::eByPolygonVertex:
		switch (geometryElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			x = geometryElement->GetDirectArray().GetAt(vertexIndex).mData[0];
			y = geometryElement->GetDirectArray().GetAt(vertexIndex).mData[1];
			z = Dimmension == 3 ? geometryElement->GetDirectArray().GetAt(vertexIndex).mData[2] : 0;
			return true;
		}
		break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = geometryElement->GetIndexArray().GetAt(vertexIndex);
			x = geometryElement->GetDirectArray().GetAt(index).mData[0];
			y = geometryElement->GetDirectArray().GetAt(index).mData[1];
			z = Dimmension == 3 ? geometryElement->GetDirectArray().GetAt(index).mData[2] : 0;
			return true;
		}
		break;
		}
		break;
	}

	DebugLine("Failed to read geometry element");
	return false;
}

