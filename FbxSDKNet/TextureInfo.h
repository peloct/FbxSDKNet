#pragma once

#include <fbxsdk.h>
#include "Object.h"

using namespace System;

namespace FbxSDK
{
	public enum class TextureAlphaSource
	{
		None,
		RGBIntensity,
		Black
	};

	public enum class TextureMappingType
	{
		Null,
		Planar,
		Spherical,
		Cylindrical,
		Box,
		Face,
		UV,
		Environment
	};
	
	public enum class TextureMaterialUse
	{
		ModelMaterial,
		DefaultMaterial
	};

	public enum class TextureUse
	{
		Standard,
		ShadowMap,
		LightMap,
		SphericalReflectionMap,
		SphereReflectionMap,
		BumpNormalMap
	};

	public enum class TextureBlendMode
	{
		Translucent,
		Additive,
		Modulate,
		Modulate2,
		Over,
		Normal,
		Dissolve,
		Darken,
		ColorBurn,
		LinearBurn,
		DarkerColor,
		Lighten,
		Screen,
		ColorDodge,
		LinearDodge,
		LighterColor,
		SoftLight,
		HardLight,
		VividLight,
		LinearLight,
		PinLight,
		HardMix,
		Difference,
		Exclusion,
		Substract,
		Divide,
		Hue,
		Saturation,
		Color,
		Luminosity,
		Overlay
	};

	public ref class TextureInfo : Object
	{
	private:
		FbxLayeredTexture* layeredTexture;
		FbxTexture* texture;

	internal:
		TextureInfo(FbxTexture* texture);

	public:
		bool IsLayeredTexture();
		int GetChildCount();
		bool GetChildTexture(int index,
			[Runtime::InteropServices::Out] TextureInfo^% texutreInfo,
			[Runtime::InteropServices::Out] TextureBlendMode& blendMode,
			[Runtime::InteropServices::Out] double& alpha);

		bool IsFileTexture();
		String^ GetFileName();
		TextureMaterialUse GetMaterialUse();

		double GetScaleU();
		double GetScaleV();
		double GetTranslationU();
		double GetTranslationV();
		bool GetSwapUV();
		double GetRotationU();
		double GetRotationV();
		double GetRotationW();
		TextureAlphaSource GetAlphaSource();
		double GetCroppingLeft();
		double GetCroppingTop();
		double GetCroppingRight();
		double GetCroppingBottom();
		TextureMappingType GetMappingType();
		int GetPlanarMappingNormal();
		double GetDefaultAlpha();
		TextureUse GetTextureUse();
	};
}