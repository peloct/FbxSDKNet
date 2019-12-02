#pragma once

#include <fbxsdk.h>

namespace FbxSDK
{
	ref class Mesh;

	public ref class Node
	{
	private:
		Node^ parent;
		FbxNode* node;

	internal:
		Node(Node^ parent, FbxNode* node) : parent(parent), node(node) {}

	public:
		Node^ GetChild(int index);
		Node^ GetParent();
		int GetChildCount();

		bool IsMesh();
		Mesh^ GetMesh();
	};
}