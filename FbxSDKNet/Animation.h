#pragma once

#include <fbxsdk.h>
#include "Object.h"

namespace FbxSDK
{
	ref class Node;

	public enum class AnimationCurveChannel
	{
		TranslationX,
		TranslationY,
		TranslationZ,
		RotationX,
		RotationY,
		RotationZ,
		ScalingX,
		ScalingY,
		ScalingZ,
		AttributeColorRed,
		AttributeColorGreen,
		AttributeColorBlue,
		LightIntensity,
		LightOuterAngle,
		LightFog,
		CameraFieldOfViewX,
		CameraFieldOfViewY,
		CameraFieldOfViewZ,
		CameraOpticalCenterX,
		CameraOpticalCenterY,
		CameraOpticalCenterZ,
		CameraRoll,
		Count
	};

	public ref class AnimationCurve
	{

	};

	public ref class AnimationLayer
	{
	public:
		AnimationCurve^ GetAnimationCurve(Node^ node, AnimationCurveChannel curveChannel);
	};

	public ref class AnimationStack : Object
	{
	private:
		FbxAnimStack* animStack;

	internal:
		AnimationStack(FbxAnimStack* animStack) : Object(animStack), animStack(animStack) {}

	public:
		int GetAnimationLayerCount();
		AnimationLayer^ GetAnimationLayer(int index);
	};
}