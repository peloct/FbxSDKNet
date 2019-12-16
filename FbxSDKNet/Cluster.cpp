#include "pch.h"
#include "Node.h"
#include "Cluster.h"

namespace FbxSDK
{
	LinkMode Cluster::GetLinkMode()
	{
		return static_cast<LinkMode>(static_cast<int>(cluster->GetLinkMode()));
	}

	Node^ Cluster::GetLink()
	{
		FbxNode* node = cluster->GetLink();
		if (node == nullptr)
			return nullptr;
		return gcnew Node(node);
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
		return Matrix(matrix);
	}

	Matrix Cluster::GetTransformLinkMatrix()
	{
		FbxAMatrix matrix;
		cluster->GetTransformLinkMatrix(matrix);
		return Matrix(matrix);
	}

	bool Cluster::HasAssociateModel()
	{
		return cluster->GetAssociateModel() != nullptr;
	}

	Node^ Cluster::GetAssociateModel()
	{
		FbxNode* node = cluster->GetAssociateModel();
		if (node == nullptr)
			return nullptr;
		return gcnew Node(node);
	}

	Matrix Cluster::GetTransformAssociateModelMatrix()
	{
		FbxAMatrix matrix;
		cluster->GetTransformAssociateModelMatrix(matrix);
		return Matrix(matrix);
	}
}
