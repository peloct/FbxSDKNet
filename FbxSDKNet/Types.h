#pragma once

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
	};
}