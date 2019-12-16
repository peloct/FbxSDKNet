#pragma once

#include <fbxsdk.h>
#include "Object.h"
#include "Time.h"

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

	internal:
		AnimationCurve(FbxAnimCurve* curve) : Object(curve), curve(curve) {}

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

	internal:
		AnimationLayer(FbxAnimLayer* layer) : Object(layer), layer(layer) {}

	public:
		AnimationCurve^ GetAnimationCurve(Node^ node, AnimationCurveChannel curveChannel);
	};

	public ref class AnimationStack : Object
	{
	internal:
		FbxAnimStack* animStack;
		AnimationStack(FbxAnimStack* animStack) : Object(animStack), animStack(animStack) {}

	public:
		int GetAnimationLayerCount();
		AnimationLayer^ GetAnimationLayer(int layerIndex);
	};
}