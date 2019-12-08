#pragma once

#include <fbxsdk.h>
#include "Types.h"
#include "Object.h"

using namespace System;

namespace FbxSDK
{
	ref class Node;

	public enum class LinkMode
	{
		Normalize,
		Additive,
		Total1
	};

	public ref class Cluster : Object
	{
	private:
		FbxCluster* cluster;

	internal:
		Cluster(FbxCluster* cluster) : Object(cluster), cluster(cluster) {}

	public:
		LinkMode GetLinkMode();
		Node^ GetLink();
		int GetControlIndicesCount();
		int GetControlPointIndex(int index);
		double GetControlPointWeight(int index);
		Matrix GetTransformMatrix();
		Matrix GetTransformLinkMatrix();
		bool HasAssociateModel();
		Matrix GetTransformAssociateModelMatrix();
	};
}