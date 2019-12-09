#pragma once

#include <fbxsdk.h>
#include "Types.h"
#include "Object.h"

using namespace System;

namespace FbxSDK
{
	ref class Mesh;
	ref class NodeAttribute;
	ref class Material;

	public enum class RotationOrder
	{
		EulerXYZ,
		EulerXZY,
		EulerYXZ,
		EulerYZX,
		EulerZXY,
		EulerZYX,
		SphericXYZ
	};

	public ref class Node : Object
	{
	internal:
		FbxNode* node;
		Node(FbxNode* node) : Object(node), node(node) {}

	public:
		Node^ GetChild(int index);
		Node^ GetParent();
		int GetChildCount();

		NodeAttribute^ GetAttribute();

		Vector3 GetTranslation();
		Vector3 GetRotation();
		Vector3 GetScaling();

		RotationOrder GetRotationOrder();

		int GetMaterialCount();
		Material^ GetMaterial(int index);
	};
}