#include "pch.h"
#include "Utils.h"
#include "Mesh.h"
#include "Cluster.h"

using namespace FbxSDK;

Vector3 ReadNormal(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex);
Vector3 ReadBinormal(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex);
Vector3 ReadTangent(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex);
Vector2 ReadUV(FbxMesh* mesh, int elementIndex, int controlPointIndex, int uvIndex);
Color ReadColor(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex);

template <typename GeometryElement, typename ValueType>
bool ReadGeometryElement(GeometryElement* geometryElement, int controlPointIndex, int vertexIndex, ValueType& result);

int Mesh::GetPolygonCount()
{
	return mesh->GetPolygonCount();
}

int Mesh::GetElementCount(VertexElementType elementType)
{
	switch (elementType)
	{
	case VertexElementType::Binormal:
		return mesh->GetElementBinormalCount();
	case VertexElementType::Tangent:
		return mesh->GetElementTangentCount();
	case VertexElementType::Color:
		return mesh->GetElementVertexColorCount();
	case VertexElementType::UV:
		return mesh->GetElementUVCount();
	case VertexElementType::MaterialMapping:
		return mesh->GetElementMaterialCount();
	default:
		break;
	}

	return 0;
}

Vector3 Mesh::GetCoordinate(int polygonIndex, int positionInPolygon)
{
	FbxVector4 vector = mesh->GetControlPoints()[mesh->GetPolygonVertex(polygonIndex, positionInPolygon)];
	return Vector3(vector[0], vector[1], vector[2]);
}

Vector3 Mesh::GetNormal(int elementIndex, int polygonIndex, int positionInPolygon)
{
	return ReadNormal(mesh, elementIndex, mesh->GetPolygonVertex(polygonIndex, positionInPolygon), 3 * polygonIndex + positionInPolygon);
}

Vector3 Mesh::GetBinormal(int elementIndex, int polygonIndex, int positionInPolygon)
{
	return ReadBinormal(mesh, elementIndex, mesh->GetPolygonVertex(polygonIndex, positionInPolygon), 3 * polygonIndex + positionInPolygon);
}

Vector3 Mesh::GetTangent(int elementIndex, int polygonIndex, int positionInPolygon)
{
	return ReadTangent(mesh, elementIndex, mesh->GetPolygonVertex(polygonIndex, positionInPolygon), 3 * polygonIndex + positionInPolygon);
}

Vector2 Mesh::GetUV(int elementIndex, int polygonIndex, int positionInPolygon)
{
	return ReadUV(mesh, elementIndex, mesh->GetPolygonVertex(polygonIndex, positionInPolygon), mesh->GetTextureUVIndex(polygonIndex, positionInPolygon));
}

Color Mesh::GetColor(int elementIndex, int polygonIndex, int positionInPolygon)
{
	return ReadColor(mesh, elementIndex, mesh->GetPolygonVertex(polygonIndex, positionInPolygon), 3 * polygonIndex + positionInPolygon);
}

int Mesh::GetMaterialMapping(int elementIndex, int polygonIndex)
{
	FbxGeometryElementMaterial* material = mesh->GetElementMaterial(elementIndex);
	return material->GetIndexArray().GetAt(polygonIndex);
}

int Mesh::GetSkinDeformerCount()
{
	return mesh->GetDeformerCount(FbxDeformer::eSkin);
}

int Mesh::GetClusterCount(int skinDeformerIndex)
{
	return ((FbxSkin*)mesh->GetDeformer(skinDeformerIndex, FbxDeformer::eSkin))->GetClusterCount();
}

Cluster^ Mesh::GetCluster(int skinDeformerIndex, int clusterIndex)
{
	return gcnew Cluster(((FbxSkin*)mesh->GetDeformer(skinDeformerIndex, FbxDeformer::eSkin))->GetCluster(clusterIndex));
}

Vector3 ReadNormal(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex)
{
	FbxGeometryElementNormal* normal = mesh->GetElementNormal(elementIndex);
	FbxVector4 result;
	if (ReadGeometryElement(normal, controlPointIndex, vertexIndex, result))
		return Vector3(result[0], result[1], result[2]);
	return Vector3(0, 0, 0);
}

Vector3 ReadBinormal(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex)
{
	FbxGeometryElementBinormal* binormal = mesh->GetElementBinormal(elementIndex);
	FbxVector4 result;
	if (ReadGeometryElement(binormal, controlPointIndex, vertexIndex, result))
		return Vector3(result[0], result[1], result[2]);
	return Vector3(0, 0, 0);
}

Vector3 ReadTangent(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex)
{
	FbxGeometryElementTangent* tangent = mesh->GetElementTangent(elementIndex);
	FbxVector4 result;
	if (ReadGeometryElement(tangent, controlPointIndex, vertexIndex, result))
		return Vector3(result[0], result[1], result[2]);
	return Vector3(0, 0, 0);
}

Vector2 ReadUV(FbxMesh* mesh, int elementIndex, int controlPointIndex, int uvIndex)
{
	FbxGeometryElementUV* uv = mesh->GetElementUV(elementIndex);
	FbxVector2 result;
	if (ReadGeometryElement(uv, controlPointIndex, uvIndex, result))
		return Vector2(result[0], result[1]);
	return Vector2(0, 0);
}

Color ReadColor(FbxMesh* mesh, int elementIndex, int controlPointIndex, int vertexIndex)
{
	FbxGeometryElementVertexColor* color = mesh->GetElementVertexColor(elementIndex);
	FbxColor result;
	if (ReadGeometryElement(color, controlPointIndex, vertexIndex, result))
		return Color(result[0], result[1], result[2], result[3]);
	return Color(0, 0, 0, 0);
}

template <typename GeometryElement, typename ValueType>
bool ReadGeometryElement(GeometryElement* geometryElement, int controlPointIndex, int vertexIndex, ValueType& result)
{
	if (!geometryElement)
		return false;

	switch (geometryElement->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:
		switch (geometryElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			result = geometryElement->GetDirectArray().GetAt(controlPointIndex);
			return true;
		}
		break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = geometryElement->GetIndexArray().GetAt(controlPointIndex);
			result = geometryElement->GetDirectArray().GetAt(index);
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
			result = geometryElement->GetDirectArray().GetAt(vertexIndex);
			return true;
		}
		break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = geometryElement->GetIndexArray().GetAt(vertexIndex);
			result = geometryElement->GetDirectArray().GetAt(index);
			return true;
		}
		break;
		}
		break;
	}

	DebugLine("Failed to read geometry element");
	return false;
}

/*
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
} */