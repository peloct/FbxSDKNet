#pragma once

#include <fbxsdk.h>
#include "Types.h"
#include "Object.h"
#include "Time.h"

using namespace System;

namespace FbxSDK
{
	ref class Scene;
	ref class Mesh;
	ref class NodeAttribute;
	ref class Material;
	ref class Pose;

	public ref class Node : Object
	{
	private:
		bool isParentNodeValid;
		Node^ parentNode;

		bool isTargetNodeValid;
		Node^ targetNode;

		bool isChildrenArrayValid;
		array<Node^>^ childrenArray;
		
		Node(Scene^ owner, FbxNode* node) : Object(owner, node), node(node),
			isParentNodeValid(false), parentNode(nullptr),
			isTargetNodeValid(false), targetNode(nullptr),
			isChildrenArrayValid(false), childrenArray(nullptr) {}

	internal:
		FbxNode* node;
		static Node^ GetNode(Scene^ scene, FbxNode* node);

	public:
		Node^ GetChild(int index);
		Node^ GetParent();
		int GetChildCount();

		Node^ GetTarget();

		NodeAttribute^ GetAttribute();

		Vector3 GetGeometricTranslation();
		Vector3 GetGeometricRotation();
		Vector3 GetGeometricScaling();
		Matrix GetGeometryOffset();

		RotationOrder GetRotationOrder();

		Matrix EvaluateGlobalTransform(Time time);

		int GetMaterialCount();
		Material^ GetMaterial(int materialIndex);
	};
}