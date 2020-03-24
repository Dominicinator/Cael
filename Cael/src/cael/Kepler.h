#pragma once
namespace Cael {
	namespace Kepler {
		
		class Orbit
		{
		public:
			Orbit();

			~Orbit();
		};
		class Elements 
		{
		public:
			double e; //eccentricity

			Elements();
			~Elements();
		};
		void toCartesian(Elements& elements);
	}

	
}


