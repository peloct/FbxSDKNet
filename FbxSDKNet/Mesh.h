#pragma once

#include <fbxsdk.h>

using namespace System;
using namespace System::Collections::Generic;

namespace FbxSDK
{
	public value struct Vector2
	{
	public:
		float x;
		float y;

		Vector2(float x, float y) : x(x), y(y) {}

		bool operator==(const Vector2^ other)
		{
			return x == other->x && y == other->y;
		}

		String^ ToString() override;
	};

	public value struct Vector3
	{
	public:
		float x;
		float y;
		float z;

		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		bool operator==(const Vector3^ other)
		{
			return x == other->x && y == other->y && z == other->z;
		}

		String^ ToString() override;
	};

	public ref struct Vertex
	{
	public:
		Vector3^ position;
		Vector3^ normal;
		Vector3^ binormal;
		Vector3^ tangent;
		Vector2^ uv;

		Vertex(Vector3^ position, Vector3^ normal, Vector3^ binormal, Vector3^ tangent, Vector2^ uv) :
			position(position), normal(normal), binormal(binormal), tangent(tangent), uv(uv)
		{ }

		bool operator==(const Vertex^ other)
		{
			return
				position == other->position
				&& normal == other->normal
				&& binormal == other->binormal
				&& tangent == other->tangent
				&& uv == other->uv;
		}
	};

	public ref class Mesh
	{
	private:
		FbxMesh* mesh;

	internal:
		Mesh(FbxMesh* mesh);

	public:
		array<Vector3>^ vertices;
		array<Vector3>^ normals;
		array<Vector3>^ binoramls;
		array<Vector3>^ tangents;
		array<Vector2>^ uvs;

		String^ GetName();
	};
}