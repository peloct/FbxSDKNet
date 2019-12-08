#include "pch.h"
#include "Node.h"
#include "NodeAttribute.h"
#include "Material.h"

using namespace FbxSDK;

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

NodeAttribute^ Node::GetAttribute()
{
	FbxNodeAttribute* attribute = node->GetNodeAttribute();
	if (!attribute)
		return nullptr;
	return ConvertNodeAttribute(this, attribute);
}

Vector3 Node::GetTranslation()
{
	FbxVector4 vector = node->GetGeometricTranslation(FbxNode::eSourcePivot);
	return Vector3(vector[0], vector[1], vector[2]);
}

Vector3 Node::GetRotation()
{
	FbxVector4 vector = node->GetGeometricRotation(FbxNode::eSourcePivot);
	return Vector3(vector[0], vector[1], vector[2]);
}

Vector3 Node::GetScaling()
{
	FbxVector4 vector = node->GetGeometricScaling(FbxNode::eSourcePivot);
	return Vector3(vector[0], vector[1], vector[2]);
}

RotationOrder Node::GetRotationOrder()
{
	EFbxRotationOrder rotationOrder;
	node->GetRotationOrder(FbxNode::eSourcePivot, rotationOrder);

	switch (rotationOrder)
	{
	case eEulerXYZ:
		return RotationOrder::EulerXYZ;
	case eEulerXZY:
		return RotationOrder::EulerXZY;
	case eEulerYZX:
		return RotationOrder::EulerYXZ;
	case eEulerYXZ:
		return RotationOrder::EulerYZX;
	case eEulerZXY:
		return RotationOrder::EulerZXY;
	case eEulerZYX:
		return RotationOrder::EulerZYX;
	case eSphericXYZ:
		return RotationOrder::SphericXYZ;
	default:
		break;
	}

	return RotationOrder();
}

int Node::GetMaterialCount()
{
	return node->GetMaterialCount();
}

Material^ Node::GetMaterial(int index)
{
	FbxSurfaceMaterial* material = node->GetMaterial(index);
	if (material)
		return gcnew Material(material);
	return nullptr;
}
