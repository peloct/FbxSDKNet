#include "pch.h"
#include "Pose.h"
#include "Node.h"
#include <memory.h>

namespace FbxSDK
{
	int Pose::Find(Node^ node)
	{
		return pose->Find(node->node);
	}

	bool Pose::IsBindPose()
	{
		return pose->IsBindPose();
	}

	bool Pose::IsLocalMatrix(int nodeIndex)
	{
		return pose->IsLocalMatrix(nodeIndex);
	}

	Matrix Pose::GetMatrix(int nodeIndex)
	{
		FbxAMatrix poseMatrix;
		FbxMatrix matrix = pose->GetMatrix(nodeIndex);

		memcpy((double*)poseMatrix, (double*)matrix, sizeof(matrix.mData));
		return Matrix(poseMatrix);
	}
}