#pragma once

#include <fbxsdk.h>
#include "Object.h"

namespace FbxSDK
{
	ref class TextureInfo;

	public enum class TextureChannel
	{
		Diffuse,
		DiffuseFactor,
		Emissive,
		EmissiveFactor,
		Ambient,
		AmbientFactor,
		Specular,
		SpecularFactor,
		Shininess,
		Bump,
		NormalMap,
		TransparentColor,
		TransparencyFactor,
		Reflection,
		ReflectionFactor,
		Count
	};

	public ref class Material : Object
	{
	private:
		FbxSurfaceMaterial* material;
		Material(Scene^ scene, FbxSurfaceMaterial* material) : Object(scene, material), material(material) {}

	internal:
		static Material^ GetMaterial(Scene^ scene, FbxSurfaceMaterial* material);

	public:
		array<TextureInfo^>^ GetTextureInfo(TextureChannel textureChannel);
	};
}