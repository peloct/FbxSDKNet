#pragma once
#include <fbxsdk.h>
#include "Object.h"

namespace FbxSDK
{
	public enum class SkinningType
	{
		Linear,
		Rigid,
		DualQuaternion,
		Blend
	};

	ref class Mesh;
	ref class Cluster;

	public ref class Skin : Object
	{
	private:
		FbxSkin* skin;
		Skin(Mesh^ owner, FbxSkin* skin);

	internal:
		Mesh^ ownerMesh;
		static Skin^ GetSkin(Mesh^ owner, FbxSkin* skin);

	public:
		SkinningType GetSkinningType();
		int GetClusterCount();
		Cluster^ GetCluster(int clusterIndex);
		int GetControlPointIndicesCount();
		double GetControlPointBlendWeight(int indicesArrayIndex);
		int GetControlPointIndex(int indicesArrayIndex);
	};
}