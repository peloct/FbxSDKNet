#include "pch.h"
#include <fbxsdk.h>
#include "Node.h"
#include "Mesh.h"

using namespace FbxSDK;

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

bool Node::IsMesh()
{
	return node->GetNodeAttribute() != nullptr && node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh;
}

Mesh^ Node::GetMesh()
{
	if (!IsMesh())
		return nullptr;

	FbxMesh* mesh = (FbxMesh*)node->GetNodeAttribute();
	return gcnew Mesh(mesh);
}