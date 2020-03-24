#pragma once
#include <random>
#include <Eigen/Dense>
namespace Cael
{
	namespace Utility
	{
		namespace Units {
			const double G = 6.67430E-11;
			const double AU = 1.496E+11;
			const double EarthMasses = 5.972E+24;
			const double LunarMasses = 7.348E+22;
			const double SolarMasses = 2E+30;
			const double meters = 1.0;
			const double kg = 1.0;
			const double minute = 60.0;
			const double hour = 3600.0;
			const double day = 86400.0;
		}
		class RandomDouble
		{
		public:
			double upper;
			double lower;
			std::mt19937 generator;
			std::uniform_real_distribution<double> distribution;

			RandomDouble(const double & a, const double & b);
			virtual ~RandomDouble();

			double next();
		};
		class RandomFloat {
		public:
			float upper;
			float lower;
			std::mt19937 generator;
			std::uniform_real_distribution<float> distribution;

			RandomFloat(const float & a, const float & b);
			virtual ~RandomFloat();

			float next();
		};
	}
	typedef Eigen::Vector2d vec2d;
	typedef Eigen::Vector2f vec2f;
	typedef Eigen::Vector3d vec3d;
	typedef Eigen::Vector3f vec3f;
	typedef Eigen::Matrix2d m2x2; // for 2d state vectors
	typedef Eigen::Matrix<double, 3, 2> m3x2; //for 3d state vectors
}