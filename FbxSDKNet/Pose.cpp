#include "pch.h"
#include "Pose.h"
#include "Node.h"
#include "Scene.h"
#include <memory.h>

namespace FbxSDK
{
	Pose^ Pose::GetPose(Scene^ scene, FbxPose* pose)
	{
		if (!pose)
			return nullptr;

		Pose^ ret = static_cast<Pose^>(scene->FindObject(pose));
		if (ret)
			return ret;
		else
			return gcnew Pose(scene, pose);
	}

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
		Node^ node = Node::GetNode(GetScene(), pose->GetNode(nodeIndex));
		FbxMatrix matrix = pose->GetMatrix(nodeIndex);

		memcpy((double*)poseMatrix, (double*)matrix, sizeof(matrix.mData));
		return Matrix(poseMatrix, node->GetRotationOrder());
	}
}