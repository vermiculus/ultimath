#include <string>
using namespace std;

	enum State
	{
		Solid,
		Liquid,
		Gas,
		Plasma
	};

	enum Type
	{
		AlkaliMetal,
		AlkalineEarthMetal,
		TransitionMetal,
		OtherMetal,
		Metalloid,
		NonMetal,
		Halogen,
		NobleGas,
		RareEarthElement
	};
struct Element
{
    public:
        // element class constructor
        Element( string iname, Type itype, State iphase, string ielecConfig, int iatomNumber, int iatomWeight, int ineutronNumber, int ielecNumber, double imelt, double iboil, double itriple, double icritical, double iheatFusion, double iheatVapor, double iheatSpecific );
        // "get" methods for data
        string getName( );
        string getType( );
        string getPhase( );
        string getElecConfig( );
        string getInfos( );
           int getatomNumber( );
           int getatomWeight( );
           int getneutronNumber( );
           int getelecNumber( );
        double getMelt( );
        double getBoil( );
        double getTriple( );
        double getCritical( );
        double getHeatFusion( );
        double getHeatVapor( );
        double getHeatSpecific( );
    private:
        // Element infos
        string name;
        string type;
        string phase;
        string elecConfig;
        int atomNumber;
        int atomWeight;
        int neutronNumber;
        int elecNumber;
        double melt;
        double boil;
        double triple;
        double critical;
        double heatFusion;
        double heatVapor;
        double heatSpecific;
};
