#pragma once

namespace Physics
{
	namespace Gravity
    {
        const double GravitationalConstant = 6.67e-11;
        const double EarthRadius = 6.3713e6;
        const double EarthMass = 5.9742e24;
        double Gravity( double MassOne, double MassTwo, double Distance );
	}

    namespace Kepler
    {
        struct Set
		{
			double Ta, Tb, Ra, Rb;
			Set(double Ta, double Tb, double Ra, double Rb);
			~Set( void );
			void Complete( void );
			void GetValues( void );
			void Display( void );
		};
	}
	namespace Momentum
	{

	}
	namespace Energy
	{

	}
	struct Vector
	{
		struct Components
		{
			double vertical;
			double horizontal;
			  void Display( void );
		};
		Vector( void );
		Vector( double Magnitude, double Direction );
		void Set_Components( double Vertical, double Horizontal );
		  void Display( void );
		double magnitude;
		double direction;
		Vector operator+( Vector operand );
		Vector operator-( Vector operand );
		Components Components;
	};

	struct Motion
	{
		Motion(double displacement, double time);
		double Time;
		double Displacement;
		double Velocity;
		double Acceleration;
		double Jerk;
	};
}