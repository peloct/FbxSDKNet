#include "pch.h"
#include "Skin.h"
#include "Cluster.h"
#include "Mesh.h"
#include "Scene.h"

namespace FbxSDK
{
	Skin::Skin(Mesh^ owner, FbxSkin* skin) : Object(owner->GetScene(), skin), skin(skin), ownerMesh(owner) {}

	Skin^ Skin::GetSkin(Mesh^ owner, FbxSkin* skin)
	{
		if (skin == nullptr)
			return nullptr;

		Skin^ ret = static_cast<Skin^>(owner->GetScene()->FindObject(skin));
		if (ret)
			return ret;
		else
			return gcnew Skin(owner, skin);
	}

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
		return Cluster::GetCluster(this, skin->GetCluster(clusterIndex));
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
