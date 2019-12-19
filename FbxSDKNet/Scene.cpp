#include "pch.h"
#include "Scene.h"
#include "Manager.h"
#include "Utils.h"
#include "Node.h"
#include "Animation.h"
#include "Pose.h"
#include "Object.h"

namespace FbxSDK
{
	using namespace System::Collections::Generic;

	Scene::!Scene()
	{
		if (!sceneReference->isDisposed)
			sceneReference->Destroy();

		DebugLine("Scene Disposed");
		manager = nullptr;
	}

	void Scene::AddObject(void* pointer, FbxSDK::Object^ object)
	{
		objectDic->Add((long long)pointer, object);
	}

	FbxSDK::Object^ Scene::FindObject(void* pointer)
	{
		long long address = (long long)pointer;

		if (address == 0)
			return nullptr;

		FbxSDK::Object^ ret = nullptr;
		objectDic->TryGetValue(address, ret);
		return ret;
	}

	Scene::Scene(Manager^ manager, SceneReference^ sceneReference) : manager(manager), sceneReference(sceneReference)
	{
		objectDic = gcnew Dictionary<long long, FbxSDK::Object^>();
	}

	Node^ Scene::GetRootNode()
	{
		if (rootNode)
			return rootNode;

		rootNode = Node::GetNode(this, sceneReference->scene->GetRootNode());
		return rootNode;
	}

	int Scene::GetAnimStackCount()
	{
		return sceneReference->scene->GetSrcObjectCount<FbxAnimStack>();
	}

	AnimationStack^ Scene::GetAnimStack(int animationStackIndex)
	{
		FbxAnimStack* animStack = sceneReference->scene->GetSrcObject<FbxAnimStack>(animationStackIndex);
		return AnimationStack::GetAnimStack(this, animStack);
	}

	void Scene::SetCurrentAnimStack(AnimationStack^ animationStack)
	{
		sceneReference->scene->SetCurrentAnimationStack(animationStack->animStack);
	}

	TimeSpan Scene::GetAnimTimelineTimeSpan(AnimationStack^ animationStack)
	{
		TimeSpan ret;

		FbxTakeInfo* takeInfo = sceneReference->scene->GetTakeInfo(animationStack->animStack->GetName());
		if (takeInfo)
		{
			ret.start = Time(takeInfo->mLocalTimeSpan.GetStart());
			ret.stop = Time(takeInfo->mLocalTimeSpan.GetStop());
		}
		else
		{
			FbxTimeSpan span;
			sceneReference->scene->GetGlobalSettings().GetTimelineDefaultTimeSpan(span);
			ret.start = Time(span.GetStart());
			ret.stop = Time(span.GetStop());
		}

		return ret;
	}

	AxisSystem Scene::GetAxisSystem()
	{
		AxisSystem ret;
		FbxGlobalSettings& globalSetting = sceneReference->scene->GetGlobalSettings();
		FbxAxisSystem axisSystem = globalSetting.GetAxisSystem();
		FbxAxisSystem::ECoordSystem coordSystem = axisSystem.GetCoorSystem();
		ret.coordSystem = static_cast<AxisSystem::CoordSystem>(static_cast<int>(coordSystem));
		ret.upVector = static_cast<AxisSystem::UpVector>(axisSystem.GetUpVector(ret.upVectorSign));
		ret.frontVector = static_cast<AxisSystem::FrontVector>(axisSystem.GetFrontVector(ret.frontVectorSign));
		return ret;
	}

	void Scene::ConvertAxisSystem(AxisSystem axisSystem)
	{
		FbxAxisSystem fbxAxisSystem(
			static_cast<FbxAxisSystem::EUpVector>(axisSystem.upVector),
			static_cast<FbxAxisSystem::EFrontVector>(axisSystem.frontVector),
			static_cast<FbxAxisSystem::ECoordSystem>(axisSystem.coordSystem));
		fbxAxisSystem.ConvertScene(sceneReference->scene);
	}

	TimeMode Scene::GetGlobalTimeMode()
	{
		return static_cast<TimeMode>(sceneReference->scene->GetGlobalSettings().GetTimeMode());
	}

	int Scene::GetPoseCount()
	{
		return sceneReference->scene->GetPoseCount();
	}

	Pose^ Scene::GetPose(int poseIndex)
	{
		return Pose::GetPose(this, sceneReference->scene->GetPose(poseIndex));
	}
}
