#include "pch.h"
#include "Node.h"
#include "Cluster.h"

using namespace FbxSDK;

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

int Cluster::GetControlPointIndex(int index)
{
	return cluster->GetControlPointIndices()[index];
}

double Cluster::GetControlPointWeight(int index)
{
	return cluster->GetControlPointWeights()[index];
}

Matrix ConvertMatrix(FbxAMatrix& matrix)
{
	FbxVector4 t = matrix.GetT();
	FbxVector4 r = matrix.GetR();
	FbxVector4 s = matrix.GetS();

	return Matrix(Vector3(t[0], t[1], t[2]), Vector3(r[0], r[1], r[2]), Vector3(s[0], s[1], s[2]));
}

Matrix Cluster::GetTransformMatrix()
{
	FbxAMatrix matrix;
	matrix = cluster->GetTransformMatrix(matrix);
	return ConvertMatrix(matrix);
}

Matrix Cluster::GetTransformLinkMatrix()
{
	FbxAMatrix matrix;
	matrix = cluster->GetTransformLinkMatrix(matrix);
	return ConvertMatrix(matrix);
}

bool Cluster::HasAssociateModel()
{
	return cluster->GetAssociateModel() != nullptr;
}

Matrix Cluster::GetTransformAssociateModelMatrix()
{
	FbxAMatrix matrix;
	matrix = cluster->GetTransformAssociateModelMatrix(matrix);
	return ConvertMatrix(matrix);
}
