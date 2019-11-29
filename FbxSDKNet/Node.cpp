#include "pch.h"
#include <fbxsdk.h>
#include "Node.h"
#include "Mesh.h"

using namespace FbxSDK;

Mesh^ Node::FindMesh()
{
	if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
		return gcnew Mesh(node->GetMesh());

	int childCount = node->GetChildCount();

	for (int i = 0; i < childCount; ++i)
	{
		Node^ child = GetChild(i);
		Node^ meshNode = child->FindMesh();

		if (meshNode != nullptr)
			return meshNode;
	}

	return nullptr;
}

Node^ Node::GetChild(int index)
{
	FbxNode* child = node->GetChild(index);
	if (child == nullptr)
		return nullptr;
	else
		return gcnew Node(this, child);
}

Node^ Node::GetParent()
{
	return parent;
}

int Node::GetChildCount()
{
	return node->GetChildCount();
}