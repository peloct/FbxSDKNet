#pragma once
#include <fbxsdk.h>
#include "Time.h"

namespace FbxSDK
{
	ref class Manager;
	ref class SceneReference;
	ref class Node;
	ref class AnimationStack;
	ref class AnimationEvaluator;
	ref class Pose;

	public value struct AxisSystem
	{
	public:
		enum class CoordSystem { RightHanded = 0, LeftHanded = 1 };
		enum class UpVector { X = 1, Y = 2, Z = 3 };
		enum class FrontVector { ParityEven = 1, ParityOdd = 2 };

	internal:
		CoordSystem coordSystem;
		int upVectorSign;
		UpVector upVector;
		int frontVectorSign;
		FrontVector frontVector;

	public:
		CoordSystem GetCoordSystem() { return coordSystem; }
		UpVector GetUpVector([System::Runtime::InteropServices::Out] int% sign) { return upVector; sign = upVectorSign; }
		FrontVector GetFrontVector([System::Runtime::InteropServices::Out] int% sign) { return frontVector; sign = frontVectorSign; }

		void SetCoordSystem(CoordSystem coordSystem) { this->coordSystem = coordSystem; }
		void SetUpVector(UpVector upVector) { this->upVector = upVector; }
		void SetFrontVector(FrontVector frontVector) { this->frontVector = frontVector; }

		AxisSystem(CoordSystem coordSystem, UpVector upVector, FrontVector frontVector) : coordSystem(coordSystem), upVector(upVector), frontVector(frontVector) {}
	};

	public ref class Scene
	{
	private:
		Manager^ manager;
		SceneReference^ sceneReference;

		~Scene() {}
		!Scene();

	internal:
		Scene(Manager^ manager, SceneReference^ sceneReference) : manager(manager), sceneReference(sceneReference) {}

	public:
		Node^ GetRootNode();
		
		int GetAnimStackCount();
		AnimationStack^ GetAnimStack(int animationStackIndex);
		void SetCurrentAnimStack(AnimationStack^ animationStack);

		TimeSpan GetAnimTimelineTimeSpan(AnimationStack^ animationStack);

		AxisSystem GetAxisSystem();
		void ConvertAxisSystem(AxisSystem axisSystem);

		TimeMode GetGlobalTimeMode();

		int GetPoseCount();
		Pose^ GetPose(int poseIndex);
	};
}