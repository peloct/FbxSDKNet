#include "pch.h"
#include "Node.h"
#include "Cluster.h"
#include "Skin.h"
#include "Mesh.h"
#include "Scene.h"

namespace FbxSDK
{
	Cluster::Cluster(Skin^ owner, FbxCluster* cluster) : Object(owner->GetScene(), cluster), cluster(cluster), ownerSkin(owner) {}

	Cluster^ Cluster::GetCluster(Skin^ owner, FbxCluster* cluster)
	{
		if (cluster == nullptr)
			return nullptr;

		Cluster^ ret = static_cast<Cluster^>(owner->GetScene()->FindObject(cluster));
		if (ret)
			return ret;
		else
			return gcnew Cluster(owner, cluster);
	}

	LinkMode Cluster::GetLinkMode()
	{
		return static_cast<LinkMode>(static_cast<int>(cluster->GetLinkMode()));
	}

	Node^ Cluster::GetLink()
	{
		return Node::GetNode(GetScene(), cluster->GetLink());
	}

	int Cluster::GetControlIndicesCount()
	{
		return cluster->GetControlPointIndicesCount();
	}

	int Cluster::GetControlPointIndex(int indicesArrayIndex)
	{
		return cluster->GetControlPointIndices()[indicesArrayIndex];
	}

	double Cluster::GetControlPointWeight(int indicesArrayIndex)
	{
		return cluster->GetControlPointWeights()[indicesArrayIndex];
	}

	Matrix Cluster::GetTransformMatrix()
	{
		FbxAMatrix matrix;
		cluster->GetTransformMatrix(matrix);
		return Matrix(matrix, ownerSkin->ownerMesh->GetNode()->GetRotationOrder());
	}

	Matrix Cluster::GetTransformLinkMatrix()
	{
		FbxAMatrix matrix;
		cluster->GetTransformLinkMatrix(matrix);
		return Matrix(matrix, GetLink()->GetRotationOrder());
	}

	bool Cluster::HasAssociateModel()
	{
		return cluster->GetAssociateModel() != nullptr;
	}

	Node^ Cluster::GetAssociateModel()
	{
		return Node::GetNode(GetScene(), cluster->GetAssociateModel());
	}

	Matrix Cluster::GetTransformAssociateModelMatrix()
	{
		FbxAMatrix matrix;
		cluster->GetTransformAssociateModelMatrix(matrix);
		return Matrix(matrix, GetAssociateModel()->GetRotationOrder());
	}
}
