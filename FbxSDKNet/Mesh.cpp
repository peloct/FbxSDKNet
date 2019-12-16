#include "pch.h"
#include "Utils.h"
#include "Mesh.h"
#include "Skin.h"

namespace FbxSDK
{
	Vector3 ReadNormal(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex);
	Vector3 ReadBinormal(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex);
	Vector3 ReadTangent(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex);
	Vector2 ReadUV(FbxMesh* mesh, int elementIndex, int controlPointIndex, int uvIndex);
	Color ReadColor(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex);

	template <typename GeometryElement, typename ValueType>
	bool ReadGeometryElement(GeometryElement* geometryElement, int controlPointIndex, int vertexIndex, ValueType& result);

	int Mesh::GetPolygonCount()
	{
		return mesh->GetPolygonCount();
	}

	int Mesh::GetElementCount(VertexElementType elementType)
	{
		switch (elementType)
		{
		case VertexElementType::Binormal:
			return mesh->GetElementBinormalCount();
		case VertexElementType::Tangent:
			return mesh->GetElementTangentCount();
		case VertexElementType::Color:
			return mesh->GetElementVertexColorCount();
		case VertexElementType::UV:
			return mesh->GetElementUVCount();
		case VertexElementType::MaterialMapping:
			return mesh->GetElementMaterialCount();
		default:
			break;
		}

		return 0;
	}

	Vector3 Mesh::GetCoordinate(int polygonIndex, int positionInPolygon)
	{
		FbxVector4 vector = mesh->GetControlPoints()[mesh->GetPolygonVertex(polygonIndex, positionInPolygon)];
		return Vector3(vector[0], vector[1], vector[2]);
	}

	Vector3 Mesh::GetNormal(int elementIndex, int polygonIndex, int positionInPolygon)
	{
		return ReadNormal(mesh, elementIndex, mesh->GetPolygonVertex(polygonIndex, positionInPolygon), 3 * polygonIndex + positionInPolygon);
	}

	Vector3 Mesh::GetBinormal(int elementIndex, int polygonIndex, int positionInPolygon)
	{
		return ReadBinormal(mesh, elementIndex, mesh->GetPolygonVertex(polygonIndex, positionInPolygon), 3 * polygonIndex + positionInPolygon);
	}

	Vector3 Mesh::GetTangent(int elementIndex, int polygonIndex, int positionInPolygon)
	{
		return ReadTangent(mesh, elementIndex, mesh->GetPolygonVertex(polygonIndex, positionInPolygon), 3 * polygonIndex + positionInPolygon);
	}

	Vector2 Mesh::GetUV(int elementIndex, int polygonIndex, int positionInPolygon)
	{
		return ReadUV(mesh, elementIndex, mesh->GetPolygonVertex(polygonIndex, positionInPolygon), mesh->GetTextureUVIndex(polygonIndex, positionInPolygon));
	}

	Color Mesh::GetColor(int elementIndex, int polygonIndex, int positionInPolygon)
	{
		return ReadColor(mesh, elementIndex, mesh->GetPolygonVertex(polygonIndex, positionInPolygon), 3 * polygonIndex + positionInPolygon);
	}

	int Mesh::GetMaterialMapping(int elementIndex, int polygonIndex)
	{
		FbxGeometryElementMaterial* material = mesh->GetElementMaterial(elementIndex);
		return material->GetIndexArray().GetAt(polygonIndex);
	}

	int Mesh::GetSkinDeformerCount()
	{
		return mesh->GetDeformerCount(FbxDeformer::eSkin);
	}

	Skin^ Mesh::GetSkinDeformer(int skinDeformerIndex)
	{
		return gcnew Skin((FbxSkin*)mesh->GetDeformer(skinDeformerIndex, FbxDeformer::eSkin));
	}

	Vector3 ReadNormal(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex)
	{
		FbxGeometryElementNormal* normal = mesh->GetElementNormal(elementIndex);
		FbxVector4 result;
		if (ReadGeometryElement(normal, controlPointIndex, vertexIndex, result))
			return Vector3(result[0], result[1], result[2]);
		return Vector3(0, 0, 0);
	}

	Vector3 ReadBinormal(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex)
	{
		FbxGeometryElementBinormal* binormal = mesh->GetElementBinormal(elementIndex);
		FbxVector4 result;
		if (ReadGeometryElement(binormal, controlPointIndex, vertexIndex, result))
			return Vector3(result[0], result[1], result[2]);
		return Vector3(0, 0, 0);
	}

	Vector3 ReadTangent(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex)
	{
		FbxGeometryElementTangent* tangent = mesh->GetElementTangent(elementIndex);
		FbxVector4 result;
		if (ReadGeometryElement(tangent, controlPointIndex, vertexIndex, result))
			return Vector3(result[0], result[1], result[2]);
		return Vector3(0, 0, 0);
	}

	Vector2 ReadUV(FbxMesh* mesh, int elementIndex, int controlPointIndex, int uvIndex)
	{
		FbxGeometryElementUV* uv = mesh->GetElementUV(elementIndex);
		FbxVector2 result;
		if (ReadGeometryElement(uv, controlPointIndex, uvIndex, result))
			return Vector2(result[0], result[1]);
		return Vector2(0, 0);
	}

	Color ReadColor(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex)
	{
		FbxGeometryElementVertexColor* color = mesh->GetElementVertexColor(elementIndex);
		FbxColor result;
		if (ReadGeometryElement(color, controlPointIndex, vertexIndex, result))
			return Color(result[0], result[1], result[2], result[3]);
		return Color(0, 0, 0, 0);
	}

	template <typename GeometryElement, typename ValueType>
	bool ReadGeometryElement(GeometryElement* geometryElement, int controlPointIndex, int vertexIndex, ValueType& result)
	{
		if (!geometryElement)
			return false;

		switch (geometryElement->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (geometryElement->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				result = geometryElement->GetDirectArray().GetAt(controlPointIndex);
				return true;
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int index = geometryElement->GetIndexArray().GetAt(controlPointIndex);
				result = geometryElement->GetDirectArray().GetAt(index);
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
				result = geometryElement->GetDirectArray().GetAt(vertexIndex);
				return true;
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int index = geometryElement->GetIndexArray().GetAt(vertexIndex);
				result = geometryElement->GetDirectArray().GetAt(index);
				return true;
			}
			break;
			}
			break;
		}

		DebugLine("Failed to read geometry element");
		return false;
	}
}