#include <iostream>
#include <string>
#include <sstream>
#include "element.h"

using namespace std;

Element::Element(string iname, Type itype, State iphase, string ielecConfig, int iatomNumber, int iatomWeight, int ineutronNumber, int ielecNumber, double imelt, double iboil, double itriple, double icritical, double iheatFusion, double iheatVapor, double iheatSpecific)
{
    this->name = iname;
    this->type = itype;
    this->phase = iphase;
    this->elecConfig = ielecConfig;
    this->atomNumber = iatomNumber;
    this->atomWeight = iatomWeight;
    this->neutronNumber = ineutronNumber;
    this->elecNumber = ielecNumber;
    this->melt = imelt;
    this->boil = iboil;
    this->triple = itriple;
    this->critical = icritical;
    this->heatFusion = iheatFusion;
    this->heatVapor = iheatVapor;
    this->heatSpecific = iheatSpecific;
}

//get**

string Element::getInfos( )
{
    /*string infoString; char buffer[15];
	infoString.append(this->name);									infoString.append(" ");
	infoString.append(this->type);									infoString.append(" ");
	infoString.append(this->phase);									infoString.append(" ");
	infoString.append(this->elecConfig);							infoString.append(" ");
	infoString.append(_itoa(this->atomNumber,		buffer, 10));	infoString.append(" ");
	infoString.append(_itoa(this->atomWeight,		buffer, 10));	infoString.append(" ");
	infoString.append(_itoa(this->neutronNumber,	buffer, 10));	infoString.append(" ");
	infoString.append(_itoa(this->elecNumber,		buffer, 10));	infoString.append(" ");
	infoString.append(_itoa(this->melt,				buffer, 10));	infoString.append(" ");
	infoString.append(_itoa(this->boil,				buffer, 10));	infoString.append(" ");
	infoString.append(_itoa(this->triple,			buffer, 10));	infoString.append(" ");
	infoString.append(_itoa(this->critical,			buffer, 10));	infoString.append(" ");
	infoString.append(_itoa(this->heatFusion,		buffer, 10));	infoString.append(" ");
	infoString.append(_itoa(this->heatVapor,		buffer, 10));	infoString.append(" ");
	infoString.append(_itoa(this->heatSpecific,		buffer, 10));	infoString.append(" ");
    return infoString;*/
	ostringstream str;
	string output;
	str << this->name
		<< this->type
		<< this->phase
		<< this->elecConfig
		<< this->atomNumber
		<< this->atomWeight
		<< this->neutronNumber
		<< this->elecNumber
		<< this->melt
		<< this->boil
		<< this->triple
		<< this->critical
		<< this->heatFusion
		<< this->heatVapor
		<< this->heatSpecific;

	output = str.str();
	output.replace( output.begin(), output.end(), 'a', '~');
	return output;
}
string Element::getName( ) { return name; }
string Element::getType( ) { return type; }
string Element::getPhase( ) { return phase; }
string Element::getElecConfig( ) { return elecConfig; }
int Element::getatomNumber( ) { return atomNumber; }
int Element::getatomWeight( ) { return atomWeight; }
int Element::getneutronNumber( ) { return neutronNumber; }
int Element::getelecNumber( ) { return elecNumber; }
double Element::getMelt( ) { return melt; }
double Element::getBoil( ) { return boil; }
double Element::getTriple( ) { return triple; }
double Element::getCritical( ) { return critical; }
double Element::getHeatFusion( ) { return heatFusion; }
double Element::getHeatVapor( ) { return heatVapor; }
double Element::getHeatSpecific( ) { return heatSpecific; }