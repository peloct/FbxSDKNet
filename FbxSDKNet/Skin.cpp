#include "pch.h"
#include "Skin.h"
#include "Cluster.h"

namespace FbxSDK
{
	SkinningType Skin::GetSkinningType()
	{
		return static_cast<SkinningType>(skin->GetSkinningType());
	}

	int Skin::GetClusterCount()
	{
		return skin->GetClusterCount();
	}

	Cluster^ Skin::GetCluster(int clusterIndex)
	{
		return gcnew Cluster(skin->GetCluster(clusterIndex));
	}

	int Skin::GetControlPointIndicesCount()
	{
		return skin->GetControlPointIndicesCount();
	}

	double Skin::GetControlPointBlendWeight(int indicesArrayIndex)
	{
		return skin->GetControlPointBlendWeights()[indicesArrayIndex];
	}

	int Skin::GetControlPointIndex(int indicesArrayIndex)
	{
		return skin->GetControlPointIndices()[indicesArrayIndex];
	}
}
