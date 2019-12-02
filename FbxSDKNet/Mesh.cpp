#include "pch.h"
#include "Mesh.h"
#include "Utils.h"
#include <string>

using namespace FbxSDK;
using namespace System;
using namespace System::Collections::Generic;

Vector3 ReadNormal(FbxMesh* mesh, int controlPointIndex, int vertexIndex);
Vector3 ReadBinormal(FbxMesh* mesh, int controlPointIndex, int vertexIndex);
Vector3 ReadTangent(FbxMesh* mesh, int controlPointIndex, int vertexIndex);
Vector2 ReadUV(FbxMesh* mesh, int controlPointIndex, int uvIndex);

template <typename GeometryElement, unsigned int Dimmension>
bool ReadGeometryElement(GeometryElement* geometryElement, int controlPointIndex, int vertexIndex, float& x, float& y, float& z);

String^ Vector2::ToString()
{
	std::string str = "{ " + std::to_string(x) + ", " + std::to_string(y) + " }";
	return gcnew String(str.c_str());
}

String^ Vector3::ToString()
{
	std::string str = "{ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " }";
	return gcnew String(str.c_str());
}

Mesh::Mesh(FbxMesh* mesh) : mesh(mesh)
{
	FbxVector4* controlPoints = mesh->GetControlPoints();

	int polygonCount = mesh->GetPolygonCount();

	bool hasNoraml = mesh->GetElementNormalCount() > 0;
	bool hasBinormal = mesh->GetElementBinormalCount() > 0;
	bool hasTangent = mesh->GetElementTangentCount() > 0;
	bool hasUV = mesh->GetElementUVCount() > 0;

	bool hasPolygonVertexMapping = false;

	if (hasNoraml)
		hasPolygonVertexMapping |= mesh->GetElementNormal(0)->GetMappingMode() == FbxGeometryElement::eByPolygonVertex;
	if (hasBinormal)
		hasPolygonVertexMapping |= mesh->GetElementBinormal(0)->GetMappingMode() == FbxGeometryElement::eByPolygonVertex;
	if (hasTangent)
		hasPolygonVertexMapping |= mesh->GetElementTangent(0)->GetMappingMode() == FbxGeometryElement::eByPolygonVertex;
	if (hasUV)
		hasPolygonVertexMapping |= mesh->GetElementUV(0)->GetMappingMode() == FbxGeometryElement::eByPolygonVertex;

	if (hasPolygonVertexMapping)
	{
		indices = gcnew array<int>(3 * polygonCount);
		vertices = gcnew array<Vector3>(3 * polygonCount);
		if (hasNoraml)
			normals = gcnew array<Vector3>(3 * polygonCount);
		if (hasBinormal)
			binoramls = gcnew array<Vector3>(3 * polygonCount);
		if (hasTangent)
			tangents = gcnew array<Vector3>(3 * polygonCount);
		if (hasUV)
			uvs = gcnew array<Vector2>(3 * polygonCount);

		int vertexIndex = 0;

		for (int i = 0; i < polygonCount; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				int controlPointIndex = mesh->GetPolygonVertex(i, j);
				FbxVector4* point = &controlPoints[controlPointIndex];

				indices[vertexIndex] = vertexIndex;
				vertices[vertexIndex] = Vector3(point->mData[0], point->mData[1], point->mData[2]);
				if (hasNoraml)
					normals[vertexIndex] = ReadNormal(mesh, controlPointIndex, vertexIndex);
				if (hasBinormal)
					binoramls[vertexIndex] = ReadBinormal(mesh, controlPointIndex, vertexIndex);
				if (hasTangent)
					tangents[vertexIndex] = ReadTangent(mesh, controlPointIndex, vertexIndex);
				if (hasUV)
					uvs[vertexIndex] = ReadUV(mesh, controlPointIndex, mesh->GetTextureUVIndex(i, j));

				vertexIndex++;
			}
		}
	}
	else
	{
		int controlPointCount = mesh->GetControlPointsCount();

		indices = gcnew array<int>(3 * polygonCount);
		vertices = gcnew array<Vector3>(controlPointCount);
		if (hasNoraml)
			normals = gcnew array<Vector3>(controlPointCount);
		if (hasBinormal)
			binoramls = gcnew array<Vector3>(controlPointCount);
		if (hasTangent)
			tangents = gcnew array<Vector3>(controlPointCount);
		if (hasUV)
			uvs = gcnew array<Vector2>(controlPointCount);

		for (int i = 0; i < controlPointCount; ++i)
		{
			FbxVector4* point = &controlPoints[i];
			vertices[i] = Vector3(point->mData[0], point->mData[1], point->mData[2]);
			if (hasNoraml)
				normals[i] = ReadNormal(mesh, i, -1);
			if (hasBinormal)
				binoramls[i] = ReadBinormal(mesh, i, -1);
			if (hasTangent)
				tangents[i] = ReadTangent(mesh, i, -1);
			if (hasUV)
				uvs[i] = ReadUV(mesh, i, -1);
		}

		int vertexIndex = 0;
		for (int i = 0; i < polygonCount; ++i)
			for (int j = 0; j < 3; ++j)
				indices[vertexIndex++] = mesh->GetPolygonVertex(i, j);
	}
}

String^ Mesh::GetName()
{
	return gcnew String(mesh->GetName());
}

Vector3 ReadNormal(FbxMesh* mesh, int controlPointIndex, int vertexIndex)
{
	FbxGeometryElementNormal* normal = mesh->GetElementNormal(0);
	float x, y, z;
	if (ReadGeometryElement<FbxGeometryElementNormal, 3>(normal, controlPointIndex, vertexIndex, x, y, z))
		return Vector3(x, y, z);
	return Vector3(0, 0, 0);
}

Vector3 ReadBinormal(FbxMesh* mesh, int controlPointIndex, int vertexIndex)
{
	FbxGeometryElementBinormal* binormal = mesh->GetElementBinormal(0);
	float x, y, z;
	if (ReadGeometryElement<FbxGeometryElementBinormal, 3>(binormal, controlPointIndex, vertexIndex, x, y, z))
		return Vector3(x, y, z);
	return Vector3(0, 0, 0);
}

Vector3 ReadTangent(FbxMesh* mesh, int controlPointIndex, int vertexIndex)
{
	FbxGeometryElementTangent* tangent = mesh->GetElementTangent(0);
	float x, y, z;
	if (ReadGeometryElement<FbxGeometryElementTangent, 3>(tangent, controlPointIndex, vertexIndex, x, y, z))
		return Vector3(x, y, z);
	return Vector3(0, 0, 0);
}

Vector2 ReadUV(FbxMesh* mesh, int controlPointIndex, int uvIndex)
{
	FbxGeometryElementUV* uv = mesh->GetElementUV(0);
	float x, y, z;
	if (ReadGeometryElement<FbxGeometryElementUV, 2>(uv, controlPointIndex, uvIndex, x, y, z))
		return Vector2(x, y);
	return Vector2(0, 0);
}

template <typename GeometryElement, unsigned int Dimmension>
bool ReadGeometryElement(GeometryElement* geometryElement, int controlPointIndex, int vertexIndex, float& x, float& y, float& z)
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;

	switch (geometryElement->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:
		switch (geometryElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			x = geometryElement->GetDirectArray().GetAt(controlPointIndex).mData[0];
			y = geometryElement->GetDirectArray().GetAt(controlPointIndex).mData[1];
			z = Dimmension >= 3 ? geometryElement->GetDirectArray().GetAt(controlPointIndex).mData[2] : 0.0f;
			return true;
		}
		break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = geometryElement->GetIndexArray().GetAt(controlPointIndex);
			x = geometryElement->GetDirectArray().GetAt(index).mData[0];
			y = geometryElement->GetDirectArray().GetAt(index).mData[1];
			z = Dimmension == 3 ? geometryElement->GetDirectArray().GetAt(index).mData[2] : 0;
			return true;
		}
		break;
		}
		break;
	case FbxGeometryElement::eByPolygonVertex:
		switch (geometryElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			x = geometryElement->GetDirectArray().GetAt(vertexIndex).mData[0];
			y = geometryElement->GetDirectArray().GetAt(vertexIndex).mData[1];
			z = Dimmension == 3 ? geometryElement->GetDirectArray().GetAt(vertexIndex).mData[2] : 0;
			return true;
		}
		break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = geometryElement->GetIndexArray().GetAt(vertexIndex);
			x = geometryElement->GetDirectArray().GetAt(index).mData[0];
			y = geometryElement->GetDirectArray().GetAt(index).mData[1];
			z = Dimmension == 3 ? geometryElement->GetDirectArray().GetAt(index).mData[2] : 0;
			return true;
		}
		break;
		}
		break;
	}

	DebugLine("Failed to read geometry element");
	return false;
}

void ProcessSkeletonHierarchy(FbxNode* inRootNode)
{
	for (int childIndex = 0; childIndex < inRootNode->GetChildCount(); ++childIndex)
	{
		FbxNode* currNode = inRootNode->GetChild(childIndex);
		ProcessSkeletonHierarchyRecursively(currNode, 0, 0, -1);
	}
} // inDepth is not needed here, I used it for debug but forgot to remove it

void ProcessSkeletonHierarchyRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex)
{
	if(inNode->GetNodeAttribute() && inNode->GetNodeAttribute()->GetAttributeType() && inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		FbxSkeleton* skeleton = (FbxSkeleton*)inNode->GetNodeAttribute();
		Joint currJoint;
		currJoint.mParentIndex = inParentIndex;
		currJoint.mName = inNode->GetName();
		mSkeleton.mJoints.push_back(currJoint);
	}
	
	for (int i = 0; i < inNode->GetChildCount(); i++)
	{
		ProcessSkeletonHierarchyRecursively(inNode->GetChild(i), inDepth + 1, mSkeleton.mJoints.size(), myIndex);
	}
} 

FbxAMatrix GetGeometryTransformation(FbxNode* inNode)
{
	if (!inNode)
	{
		throw std::exception("Null for mesh geometry");
	}
	
	const FbxVector4 lT = inNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	const FbxVector4 lR = inNode->GetGeometricRotation(FbxNode::eSourcePivot);
	const FbxVector4 lS = inNode->GetGeometricScaling(FbxNode::eSourcePivot);
	return FbxAMatrix(lT, lR, lS);
}

void ProcessJointsAndAnimations(FbxNode* inNode)
{
	FbxMesh* currMesh = inNode->GetMesh();
	unsigned int numOfDeformers = currMesh->GetDeformerCount();
	// This geometry transform is something I cannot understand
	// I think it is from MotionBuilder
	// If you are using Maya for your models, 99% this is just an
	// identity matrix
	// But I am taking it into account anyways......
	FbxAMatrix geometryTransform = GetGeometryTransformation(inNode);
	// A deformer is a FBX thing, which contains some clusters
	// A cluster contains a link, which is basically a joint
	// Normally, there is only one deformer in a mesh
	for (unsigned int deformerIndex = 0; deformerIndex < numOfDeformers; ++deformerIndex)
	{
		// There are many types of deformers in Maya,
		// We are using only skins, so we see if this is a skin
		FbxSkin* currSkin = reinterpret_cast<FbxSkin*>(currMesh->GetDeformer(deformerIndex, FbxDeformer::eSkin));
		if (!currSkin) { continue; }
		unsigned int numOfClusters = currSkin->GetClusterCount();
		for (unsigned int clusterIndex = 0; clusterIndex < numOfClusters; ++clusterIndex)
		{
			FbxCluster* currCluster = currSkin->GetCluster(clusterIndex);
			std::string currJointName = currCluster->GetLink()->GetName();
			unsigned int currJointIndex = FindJointIndexUsingName(currJointName);
			FbxAMatrix transformMatrix;
			FbxAMatrix transformLinkMatrix;
			FbxAMatrix globalBindposeInverseMatrix;
			currCluster->GetTransformMatrix(transformMatrix);
			// The transformation of the mesh at binding time
			currCluster->GetTransformLinkMatrix(transformLinkMatrix);
			// The transformation of the cluster(joint) at binding time from joint space to world space
			globalBindposeInverseMatrix = transformLinkMatrix.Inverse() * transformMatrix * geometryTransform;
			// Update the information in mSkeleton
			mSkeleton.mJoints[currJointIndex].mGlobalBindposeInverse = globalBindposeInverseMatrix;
			mSkeleton.mJoints[currJointIndex].mNode = currCluster->GetLink();
			// Associate each joint with the control points it affects
			unsigned int numOfIndices = currCluster->GetControlPointIndicesCount();
			for (unsigned int i = 0; i < numOfIndices; ++i)
			{
				BlendingIndexWeightPair currBlendingIndexWeightPair;
				currBlendingIndexWeightPair.mBlendingIndex = currJointIndex;
				currBlendingIndexWeightPair.mBlendingWeight = currCluster->GetControlPointWeights()[i];
				mControlPoints[currCluster->GetControlPointIndices()[i]]->mBlendingInfo.push_back(currBlendingIndexWeightPair);
			}
			// Get animation information
			// Now only supports one take

			FbxScene* mFBXScene;
			FbxAnimStack* currAnimStack = mFBXScene->GetSrcObject(0);
			FbxString animStackName = currAnimStack->GetName();
			char* mAnimationName = animStackName.Buffer();
			FbxTakeInfo* takeInfo = mFBXScene->GetTakeInfo(animStackName);
			FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
			FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
			long long int mAnimationLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;
			Keyframe** currAnim = &mSkeleton.mJoints[currJointIndex].mAnimation;
			for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24); i <= end.GetFrameCount(FbxTime::eFrames24); ++i)
			{
				FbxTime currTime;
				currTime.SetFrame(i, FbxTime::eFrames24);
				*currAnim = new Keyframe();
				(*currAnim)->mFrameNum = i;
				FbxAMatrix currentTransformOffset = inNode->EvaluateGlobalTransform(currTime) * geometryTransform;
				(*currAnim)->mGlobalTransform = currentTransformOffset.Inverse() * currCluster->GetLink()->EvaluateGlobalTransform(currTime);
				currAnim = &((*currAnim)->mNext);
			}
		}
	}
	// Some of the control points only have less than 4 joints
	// affecting them.
	// For a normal renderer, there are usually 4 joints
	// I am adding more dummy joints if there isn't enough
	BlendingIndexWeightPair currBlendingIndexWeightPair;
	currBlendingIndexWeightPair.mBlendingIndex = 0;
	currBlendingIndexWeightPair.mBlendingWeight = 0;
	for(auto itr = mControlPoints.begin(); itr != mControlPoints.end(); ++itr)
	{
		for(unsigned int i = itr->second->mBlendingInfo.size(); i <= 4; ++i)
		{
			itr->second->mBlendingInfo.push_back(currBlendingIndexWeightPair);
		}
	}
} 