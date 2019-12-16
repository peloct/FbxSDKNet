#include "pch.h"
#include "Node.h"
#include "NodeAttribute.h"
#include "Material.h"

namespace FbxSDK
{
	Node^ Node::GetChild(int index)
	{
		FbxNode* child = node->GetChild(index);
		if (child == nullptr)
			return nullptr;
		else
			return gcnew Node(child);
	}

	Node^ Node::GetParent()
	{
		return gcnew Node(node->GetParent());
	}

	int Node::GetChildCount()
	{
		return node->GetChildCount();
	}

	Node^ Node::GetTarget()
	{
		FbxNode* fbxNode = node->GetTarget();
		if (fbxNode == nullptr)
			return nullptr;
		return gcnew Node(fbxNode);
	}

	NodeAttribute^ Node::GetAttribute()
	{
		FbxNodeAttribute* attribute = node->GetNodeAttribute();
		if (!attribute)
			return nullptr;
		return ConvertNodeAttribute(this, attribute);
	}

	Vector3 Node::GetGeometricTranslation()
	{
		FbxVector4 vector = node->GetGeometricTranslation(FbxNode::eSourcePivot);
		return Vector3(vector[0], vector[1], vector[2]);
	}

	Vector3 Node::GetGeometricRotation()
	{
		FbxVector4 vector = node->GetGeometricRotation(FbxNode::eSourcePivot);
		return Vector3(vector[0], vector[1], vector[2]);
	}

	Vector3 Node::GetGeometricScaling()
	{
		FbxVector4 vector = node->GetGeometricScaling(FbxNode::eSourcePivot);
		return Vector3(vector[0], vector[1], vector[2]);
	}

	Matrix Node::GetGeometryOffset()
	{
		return Matrix(node->GetGeometricTranslation(FbxNode::eSourcePivot), node->GetGeometricRotation(FbxNode::eSourcePivot), node->GetGeometricScaling(FbxNode::eSourcePivot));
	}

	RotationOrder Node::GetRotationOrder()
	{
		EFbxRotationOrder rotationOrder;
		node->GetRotationOrder(FbxNode::eSourcePivot, rotationOrder);
		return static_cast<RotationOrder>(rotationOrder);
	}

	Matrix Node::EvaluateGlobalTransform(Time time)
	{
		return Matrix(node->EvaluateGlobalTransform(time.ToFbxTime()));
	}

	int Node::GetMaterialCount()
	{
		return node->GetMaterialCount();
	}

	Material^ Node::GetMaterial(int materialIndex)
	{
		FbxSurfaceMaterial* material = node->GetMaterial(materialIndex);
		if (material)
			return gcnew Material(material);
		return nullptr;
	}

}