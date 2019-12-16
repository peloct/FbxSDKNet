#include "pch.h"
#include "NodeAttribute.h"
#include "Mesh.h"

namespace FbxSDK
{
	NodeAttributeType ConvertAttributeType(FbxNodeAttribute::EType attributeType)
	{
		return static_cast<NodeAttributeType>(static_cast<int>(attributeType));
	}

	NodeAttribute^ ConvertNodeAttribute(Node^ node, FbxNodeAttribute* attribute)
	{
		switch (attribute->GetAttributeType())
		{
		case FbxNodeAttribute::EType::eMesh:
			return gcnew Mesh(node, static_cast<FbxMesh*>(attribute));
		default:
			return nullptr;
		}
	}
}