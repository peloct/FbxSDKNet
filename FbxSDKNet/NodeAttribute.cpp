#include "pch.h"
#include "NodeAttribute.h"
#include "Mesh.h"
#include "Node.h"
#include "Scene.h"

namespace FbxSDK
{
	NodeAttribute::NodeAttribute(Node^ node, FbxNodeAttribute* attribute) : Object(node->GetScene(), attribute), attribute(attribute), node(node) {}

	NodeAttributeType ConvertAttributeType(FbxNodeAttribute::EType attributeType)
	{
		return static_cast<NodeAttributeType>(static_cast<int>(attributeType));
	}

	NodeAttribute^ ConvertNodeAttribute(Node^ node, FbxNodeAttribute* attribute)
	{
		switch (attribute->GetAttributeType())
		{
		case FbxNodeAttribute::EType::eMesh:
		{
			NodeAttribute^ ret = static_cast<NodeAttribute^>(node->GetScene()->FindObject(attribute));
			if (ret)
				return ret;
			else
				return gcnew Mesh(node, static_cast<FbxMesh*>(attribute));
		}
		default:
			return nullptr;
		}
	}
}