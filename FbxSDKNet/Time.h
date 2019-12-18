#pragma once

#include <fbxsdk.h>

namespace FbxSDK
{
	public enum class TimeMode
	{
		DefaultMode,
		Frames120,
		Frames100,
		Frames60,
		Frames50,
		Frames48,
		Frames30,
		Frames30Drop,
		NTSCDropFrame,
		NTSCFullFrame,
		PAL,
		Frames24,
		Frames1000,
		FilmFullFrame,
		Custom,
		Frames96,
		Frames72,
		Frames59dot94,
		ModesCount
	};

	ref class Scene;

	public value struct Time
	{
	private:
		FbxLongLong time;

	internal:
		Time(FbxTime& fbxTime) : time(fbxTime.Get()) {}

		FbxTime ToFbxTime()
		{
			FbxTime ret;
			ret.Set(time);
			return ret;
		}

	public:
		Time(FbxLongLong time) : time(time) {}

		Time(int hour, int minute, int second, int frame, TimeMode timeMode)
		{
			FbxTime time;
			time.SetTime(hour, minute, second, frame, 0, static_cast<FbxTime::EMode>(timeMode));
			this->time = time.Get();
		}

		static Time Infinite()
		{
			return Time(FBXSDK_TIME_INFINITE);
		}

		static Time MinusInfinite()
		{
			return Time(FBXSDK_TIME_MINUS_INFINITE);
		}

		static Time operator+(const Time^ a, const Time^ b)
		{
			return Time(a->time + b->time);
		}

		static Time operator-(const Time^ a, const Time^ b)
		{
			return Time(a->time - b->time);
		}

		static void operator+=(Time^ a, const Time^ b)
		{
			a->time += b->time;
		}

		static void operator-=(Time^ a, const Time^ b)
		{
			a->time -= b->time;
		}

		static bool operator<(const Time^ a, const Time^ b)
		{
			return a->time < b->time;
		}

		static bool operator>(const Time^ a, const Time^ b)
		{
			return a->time > b->time;
		}

		static bool operator<=(const Time^ a, const Time^ b)
		{
			return a->time <= b->time;
		}

		static bool operator>=(const Time^ a, const Time^ b)
		{
			return a->time >= b->time;
		}

		static bool operator==(const Time^ a, const Time^ b)
		{
			return a->time == b->time;
		}

		static bool operator!=(const Time^ a, const Time^ b)
		{
			return a->time != b->time;
		}
	};
	
	public value struct TimeSpan
	{
	public:
		Time start;
		Time stop;
	};
}