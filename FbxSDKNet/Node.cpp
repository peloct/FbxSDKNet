#include "pch.h"
#include "Node.h"
#include "Scene.h"
#include "NodeAttribute.h"
#include "Material.h"

namespace FbxSDK
{
	Node^ Node::GetNode(Scene^ scene, FbxNode* node)
	{
		if (node == nullptr)
			return nullptr;

		Node^ ret = static_cast<Node^>(scene->FindObject(node));

		if (ret)
			return ret;
		else
			return gcnew Node(scene, node);
	}

	Node^ Node::GetChild(int index)
	{
		if (!isChildrenArrayValid)
			childrenArray = gcnew array<Node^>(GetChildCount());

		isChildrenArrayValid = true;

		FbxNode* child = node->GetChild(index);

		if (!child)
			return nullptr;

		if (childrenArray[index] == nullptr)
			childrenArray[index] = GetNode(GetScene(), child);
		return childrenArray[index];
	}

	Node^ Node::GetParent()
	{
		if (isParentNodeValid)
			return parentNode;

		isParentNodeValid = true;
		parentNode = GetNode(GetScene(), node->GetParent());
		return parentNode;
	}

	int Node::GetChildCount()
	{
		return node->GetChildCount();
	}

	Node^ Node::GetTarget()
	{
		if (isTargetNodeValid)
			return targetNode;

		isTargetNodeValid = true;
		targetNode = GetNode(GetScene(), node->GetTarget());
		return targetNode;
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
		return Matrix(node->GetGeometricTranslation(FbxNode::eSourcePivot), node->GetGeometricRotation(FbxNode::eSourcePivot), node->GetGeometricScaling(FbxNode::eSourcePivot), GetRotationOrder());
	}

	RotationOrder Node::GetRotationOrder()
	{
		EFbxRotationOrder rotationOrder;
		node->GetRotationOrder(FbxNode::eSourcePivot, rotationOrder);
		return static_cast<RotationOrder>(rotationOrder);
	}

	Matrix Node::EvaluateGlobalTransform(Time time)
	{
		return Matrix(node->EvaluateGlobalTransform(time.ToFbxTime()), GetRotationOrder());
	}

	int Node::GetMaterialCount()
	{
		return node->GetMaterialCount();
	}

	Material^ Node::GetMaterial(int materialIndex)
	{
		return Material::GetMaterial(GetScene(), node->GetMaterial(materialIndex));
	}
}