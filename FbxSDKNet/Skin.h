#pragma once
#include <fbxsdk.h>

namespace FbxSDK
{
	public enum class SkinningType
	{
		Linear,
		Rigid,
		DualQuaternion,
		Blend
	};

	ref class Cluster;

	public ref class Skin
	{
	private:
		FbxSkin* skin;

	internal:
		Skin(FbxSkin* skin) : skin(skin) {}

	public:
		SkinningType GetSkinningType();
		int GetClusterCount();
		Cluster^ GetCluster(int clusterIndex);
		int GetControlPointIndicesCount();
		double GetControlPointBlendWeight(int indicesArrayIndex);
		int GetControlPointIndex(int indicesArrayIndex);
	};
}