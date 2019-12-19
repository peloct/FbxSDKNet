#pragma once

#include <fbxsdk.h>
#include "Types.h"
#include "Object.h"

namespace FbxSDK
{
	ref class Node;
	ref class Skin;

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
		Cluster(Skin^ owner, FbxCluster* cluster);

	internal:
		Skin^ ownerSkin;
		static Cluster^ GetCluster(Skin^ owner, FbxCluster* cluster);

	public:
		LinkMode GetLinkMode();
		Node^ GetLink();
		int GetControlIndicesCount();
		int GetControlPointIndex(int indicesArrayIndex);
		double GetControlPointWeight(int indicesArrayIndex);
		Matrix GetTransformMatrix();
		Matrix GetTransformLinkMatrix();
		bool HasAssociateModel();
		Node^ GetAssociateModel();
		Matrix GetTransformAssociateModelMatrix();
	};
}