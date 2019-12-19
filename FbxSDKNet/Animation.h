#pragma once

#include <fbxsdk.h>
#include "Object.h"
#include "Time.h"

namespace FbxSDK
{
	ref class Node;
	ref class Scene;
	ref class AnimationStack;
	ref class AnimationLayer;
	ref class AnimationCurve;

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
		CameraOpticalCenterX,
		CameraOpticalCenterY,
		CameraRoll,
		Count
	};

	public enum class AnimationInterpolationType
	{
		InterpolationConstant = 0x00000002,
		InterpolationLinear = 0x00000004,
		InterpolationCubic = 0x00000008
	};

	public ref class AnimationCurve : Object
	{
	private:
		FbxAnimCurve* curve;
		AnimationCurve(AnimationLayer^ owner, FbxAnimCurve* curve);

	internal:
		static AnimationCurve^ GetAnimCurve(AnimationLayer^ owner, FbxAnimCurve* curve);

	public:
		int GetKeyCount();
		Time GetKeyTime(int index);
		double GetKeyValue(int index);
		AnimationInterpolationType GetKeyInterpolation(int index);
	};

	public ref class AnimationLayer : Object
	{
	private:
		FbxAnimLayer* layer;
		AnimationLayer(AnimationStack^ owner, FbxAnimLayer* layer);

	internal:
		static AnimationLayer^ GetAnimLayer(AnimationStack^ owner, FbxAnimLayer* layer);

	public:
		AnimationCurve^ GetAnimationCurve(Node^ node, AnimationCurveChannel curveChannel);
	};

	public ref class AnimationStack : Object
	{
	private:
		AnimationStack(Scene^ owner, FbxAnimStack* animStack) : Object(owner, animStack), animStack(animStack) {}

	internal:
		FbxAnimStack* animStack;
		static AnimationStack^ GetAnimStack(Scene^ owner, FbxAnimStack* animStack);

	public:
		int GetAnimationLayerCount();
		AnimationLayer^ GetAnimationLayer(int layerIndex);
	};
}