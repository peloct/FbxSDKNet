#pragma once

#include <fbxsdk.h>

using namespace System;

namespace FbxSDK
{
	public value struct Vector2
	{
	public:
		double x;
		double y;

		Vector2(double x, double y) : x(x), y(y) {}

		bool operator==(const Vector2^ other)
		{
			return x == other->x && y == other->y;
		}

		String^ ToString() override;
	};

	public value struct Vector3
	{
	public:
		double x;
		double y;
		double z;

		Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

		bool operator==(const Vector3^ other)
		{
			return x == other->x && y == other->y && z == other->z;
		}

		String^ ToString() override;
	};

	public value struct Color
	{
	public:
		double r;
		double g;
		double b;
		double a;

		Color(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}

		bool operator==(const Color^ other)
		{
			return r == other->r && g == other->g && b == other->b && a == other->a;
		}

		String^ ToString() override;
	};

	public value struct Matrix
	{
	public:
		Vector3 translation;
		Vector3 rotation;
		Vector3 scaling;

		Matrix(Vector3& translation, Vector3& rotation, Vector3& scaling) : translation(translation), rotation(rotation), scaling(scaling) {}

		bool operator==(const Matrix^% other)
		{
			return translation == other->translation && rotation == other->rotation && scaling == other->scaling;
		}

		String^ ToString() override;

	internal:
		Matrix(FbxAMatrix& matrix)
		{
			FbxVector4 t = matrix.GetT();
			FbxVector4 r = matrix.GetR();
			FbxVector4 s = matrix.GetS();
			this->translation = Vector3(t[0], t[1], t[2]);
			this->rotation = Vector3(r[0], r[1], r[2]);
			this->scaling = Vector3(s[0], s[1], s[2]);
		}

		Matrix(FbxVector4& translation, FbxVector4& rotation, FbxVector4& scaling)
		{
			this->translation = Vector3(translation[0], translation[1], translation[2]);
			this->rotation = Vector3(rotation[0], rotation[1], rotation[2]);
			this->scaling = Vector3(scaling[0], scaling[1], scaling[2]);
		}
	};
}