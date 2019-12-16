#pragma once

#include <fbxsdk.h>
#include "Types.h"
#include "Object.h"
#include "Time.h"

using namespace System;

namespace FbxSDK
{
	ref class Mesh;
	ref class NodeAttribute;
	ref class Material;
	ref class Pose;

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