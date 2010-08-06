#include "Physics.h"
#include "Global Constants.h"
#include <stdio.h>
#include <cmath>
#include <iostream>
#include "Basics.h"

double Physics::Gravity::Gravity( double MassOne, double MassTwo, double Distance ){ 
	if(MassOne == 0 || MassTwo == 0 || Distance == 0)
		return -1; //need to find out how exceptions work in C++
	return (Physics::Gravity::GravitationalConstant*MassOne*MassTwo) / (Distance*Distance);}

Physics::Kepler::Set::Set(double Ta, double Tb, double Ra, double Rb)
{
	this->Ta = Ta;
	this->Tb = Tb;
	this->Ra = Ra;
	this->Rb = Rb;
}

Physics::Kepler::Set::~Set( void ) { }

void Physics::Kepler::Set::Complete( void ) { }

void Physics::Kepler::Set::GetValues( void )
{
	printf("Enter a value for Ta: ");
	scanf_s("%e", this->Ra);
}

void Physics::Kepler::Set::Display( void )
{
	printf("Ta: %e\nTb: %e\nRa: %e\nRb: %e\n",
		this->Ta, this->Tb, this->Ra, this->Rb); // has issues when GetValues is done before Display... 
	//"Unhandled exception at 0x0fec936c (msvcr90d.dll) in Ultimath Library.exe: 0xC0000005: Access violation writing location 0x00000000."
}

//                                     Physics::Vector
Physics::Vector::Vector( void )
{ }

Physics::Vector::Vector( double Magnitude, double Direction )
{
	this->magnitude = Magnitude;
	this->direction = Direction;
	this->Components.vertical = Magnitude * sin( Direction );
	this->Components.horizontal = Magnitude * cos( Direction );
}

void Physics::Vector::Set_Components( double Vertical, double Horizontal )
{
	//return Vector(
	//	sqrt( pow( Vertical, 2 ) + pow( Horizontal, 2 ) ), // magnitude
	//	atan2( Vertical, Horizontal )); // direction
	this->direction = atan2( Vertical, Horizontal );
	this->magnitude = sqrt( pow( Vertical, 2 ) + pow( Horizontal, 2 ) );
	this->Components.vertical = Vertical;
	this->Components.horizontal = Horizontal;
}

Physics::Vector Physics::Vector::operator+(Physics::Vector operand)
{
	Vector sum;	sum.Set_Components(this->Components.vertical + operand.Components.vertical, this->Components.horizontal + operand.Components.horizontal);
	return sum;
}

Physics::Vector Physics::Vector::operator-(Physics::Vector operand)
{
	Vector difference;	difference.Set_Components(this->Components.vertical - operand.Components.vertical, this->Components.horizontal - operand.Components.horizontal);
	return difference;
}

void Physics::Vector::Display( void )
{
	if(this->magnitude < 0)
	{
		this->direction += PI / 2;
		this->magnitude = -1 * this->magnitude;
	}
	printf("Magnitude: %f\nDirection: %f\n",
		this->magnitude, this->direction);
}

void Physics::Vector::Components::Display( void )
{
	printf("Horizontal: %f\n  Vertical: %f\n",
		this->horizontal, this->vertical);
}