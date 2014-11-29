/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Multi-Purpose Analysis Framework                                     **
**                                                                          **
** Constantin Heidegger, Matthieu Marionneau                                **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/

#ifndef __VC_
#define __VC_

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <TROOT.h>
#include <TLorentzVector.h>
#include <TBranch.h>
#include <TBranchSTL.h>
#include <TClass.h>
#include <TObjArray.h>
#include <TTree.h>
#include <TBits.h>
#include <TChain.h>

#include "analysis/utils/SystUtils.hh"


using namespace std;


typedef map<string, vector<int>* > mapVI;
typedef map<string, vector<unsigned int>* > mapVUI;
typedef map<string, vector<unsigned long>* > mapVUL;
typedef map<string, vector<double>* > mapVD;
typedef map<string, vector<float>* > mapVF;
typedef map<string, vector<string>* > mapVS;
typedef map<string, vector<bool>* > mapVB;

typedef map<string, vector<int>* >::iterator itMapVI;
typedef map<string, vector<unsigned int>* >::iterator itMapVUI;
typedef map<string, vector<unsigned long>* >::iterator itMapVUL;
typedef map<string, vector<double>* >::iterator itMapVD;
typedef map<string, vector<float>* >::iterator itMapVF;
typedef map<string, vector<string>* >::iterator itMapVS;
typedef map<string, vector<bool>* >::iterator itMapVB;

typedef map<string, int* > mapAI; 
typedef map<string, unsigned int* > mapAUI; 
typedef map<string, unsigned long* > mapAUL; 
typedef map<string, double* > mapAD; 
typedef map<string, float* > mapAF; 
typedef map<string, string* > mapAS; 
typedef map<string, bool* > mapAB; 
 
typedef map<string, int* >::iterator itMapAI; 
typedef map<string, unsigned int* >::iterator itMapAUI; 
typedef map<string, unsigned long* >::iterator itMapAUL; 
typedef map<string, double* >::iterator itMapAD; 
typedef map<string, float* >::iterator itMapAF; 
typedef map<string, string* >::iterator itMapAS; 
typedef map<string, bool* >::iterator itMapAB;

typedef map<string, int > mapI;
typedef map<string, unsigned int > mapUI;
typedef map<string, unsigned long > mapUL;
typedef map<string, double > mapD;
typedef map<string, float > mapF;
typedef map<string, bool > mapB;
typedef map<string, string > mapS;

typedef map<string, TBits* > mapTB;

typedef map<string, int >::iterator itMapI;
typedef map<string, unsigned int >::iterator itMapUI;
typedef map<string, unsigned long >::iterator itMapUL;
typedef map<string, double >::iterator itMapD;
typedef map<string, float >::iterator itMapF;
typedef map<string, bool >::iterator itMapB;
typedef map<string, string >::iterator itMapS;

typedef map<string, TBits* >::iterator itMapTB;




class VarClass {


	// Private Template Members

private:

	//____________________________________________________________________________
	template<typename T> inline vector<float> convertVal(T val) {
		/*
		converts a scalar of arbitrary type to a vetor of one float
		parameters: val (the scalar)
		return: the vector
		*/

		vector<float> vf;
		vf.push_back((float) val);

		return vf;

	};


	//____________________________________________________________________________
	template<typename T> inline vector<float> convertVal(vector<T> vals) {
		/*
		converts a vector of arbitrary type to a vector of floats
		parameters: vals (the vector)
		return: vector of floats
		*/

		vector<float> vf;

		for(size_t iv = 0; iv < vals.size(); ++iv)
			vf.push_back( (float) vals[iv] );

		return vf;

	};

 
	//____________________________________________________________________________
	template<typename T> inline void storeAccess(string mvar, map<string, T>& imap, map<string, T>& cmap) {
		/*
		adds a scalar variable mvar to the map cmap taking the values from imap, if it is 
		not already registered; if it is, it reinitializes the map cmap for new events,
		otherwise loads the value from cmap into imap
		parameters: mvar, imap, cmap
		return: none
		*/
	
		typename map<string, T>::const_iterator it = cmap.find(mvar);
	
		// variable not yet registered in the backup map	
		if( it == cmap.end() ) { 
			cmap[ mvar ] = imap[ mvar ];
			//cout<<" init step : "<<mvar<<"  "<<cmap[ mvar ]<<" / "<<imap[ mvar ]<<"   "<<(&(cmap[ mvar ]))<<endl;
		}
	
		// variable already registered, reinitialization
		else { 
			if(_nextEvent)
				cmap[ mvar ] = imap[ mvar ];
			else
				imap[ mvar ] = cmap[ mvar ];
			//cout<<" back step : "<<cmap[ mvar ]<<" / "<<imap[ mvar ]<<"   "<<(&(cmap[ mvar ]))<<endl;
		}
	};


	//____________________________________________________________________________
	template<typename T> inline void storeAccessV(string mvar, map<string, vector<T>* >& imap, map<string, vector<T>* >& cmap) {
		/*
		adds a vector variable mvar to a map cmap with values taken from imap if it is 
		not already registered; if it is, it reinitializes the vector in the map cmap 
		for new events, otherwise it reinitializes the map imap with values from cmap
		parameters: mvar (the variable), imap, cmap
		return: none
		*/
	
		typename map<string, vector<T>* >::const_iterator it = cmap.find(mvar);
	
		// variable not yet registered in the backup map
		if( it == cmap.end() ) { 
	
			cmap[ mvar ] = new vector<T>;
			for(size_t ie = 0; ie < imap[mvar] -> size(); ++ie) {
				cmap[ mvar ] -> push_back( imap[ mvar ] -> at(ie) );
				//cout << " init step : " << cmap[ mvar ] -> at(ie) << " / " << imap[ mvar ] -> at(ie) << endl;
			}
		}
	
		// variable already registered, reinitialization
		else { 
	
			// vector reinitialization (for new events)
			if( _nextEvent ) {
	
				cmap[ mvar ] -> resize( imap[mvar] -> size() );
				for(size_t ie = 0; ie < imap[mvar] -> size(); ++ie)
					cmap[ mvar ] -> at(ie) = imap[ mvar ] -> at(ie);
			}
	
			else {
				for(size_t ie = 0; ie < imap[mvar] -> size(); ++ie) {
					imap[ mvar ] -> at(ie) = cmap[ mvar ] -> at(ie);
					//cout << " back step : " << cmap[ mvar ] -> at(ie) << " / " << imap[ mvar ] -> at(ie) << endl;
				}
			}
		}
	};


	//____________________________________________________________________________
	template<typename T> inline void multiReinit(map<string, T>& imap, map<string, T> cmap) {
		/*
		reinitializes a map (imap) of scalars with values from another map (cmap)
		parameters: imap, cmap
		return: none
		*/

		typename map<string, T>::const_iterator it;
		
		for(it = cmap.begin(); it != cmap.end(); ++it)
			imap[ it -> first ] = it -> second;
		
	};


	//____________________________________________________________________________
	template<typename T> inline void multiReinitV(map<string, vector<T>* >& imap, map<string, vector<T>* > cmap) {
		/*
		reinitializes a map (imap) of vectors with values from another map (cmap)
		parameters: imap, cmap
		return: none
		*/
	
		typename map<string, vector<T>* >::const_iterator it;
	
		for(it = cmap.begin(); it != cmap.end(); ++it)
			for(size_t ie = 0; ie < imap[ it -> first ] -> size(); ++ie)
				imap[ it -> first ] -> at(ie) = it -> second -> at(ie);
	
	};




	// Public Non-Template Methods


public:

	VarClass();
	~VarClass();
	
	void reset();
	
	void registerVar(string name);
	void registerVar(string name, string type);
	bool isUsefulVar(string name);
	  
	int getI(string name, int idx=0);
	unsigned int getUI(string name, int idx=0);
	size_t getUL(string name, int idx=0);
	bool getB(string name, int idx=0);
	double getD(string name, int idx=0);
	float getF(string name, int idx=0);
	string getS(string name, int idx=0);
	
	vector<int> getVI(string name);
	vector<unsigned int> getVUI(string name);
	vector<size_t> getVUL(string name);
	vector<bool> getVB(string name);
	vector<double> getVD(string name);
	vector<float> getVF(string name);
	vector<string> getVS(string name);
	
	bool tryType(string name, string type);
	string getType(string name);
	
	unsigned int getSize(string name);
	
	void buildTree(TTree* tree, bool bypass);
	void registerBranch(TTree* tree, string name, string type, EDataType t);
	
	//systematic ucnertainty propagation     ============
	// void applySystVar(string name, int dir, string mvar, float mag, string type);
	// void applySystVar(string name, int dir, string mvar, vector<string> vars,
	// 		    string db, string type);
	// void backPortVar(string mvar);
	// void backPortAllVars();
	// void applyWSystVar(string name, int dir, float& w, vector<string> vars, 
	// 		     string db, string type);
	
	// void nextEvent(){ _nextEvent=true;};
	// void sameEvent(){ _nextEvent=false;};
	
	SystUtils* _su;
	//===================================================


	// Private Non-Template Methods

private:

	vector<float> getUnivF(string name);



	// Public Members

public: 



	// Private Members

private:

	enum {
		kInt=0,
		kUInt,
		kULong,
		kDouble,
		kFloat,
		kString,
		kBool,
		// kVInt,
		// kVUInt,
		// kVULong,
		// kVDouble,
		// kVFloat,
		// kVString,
		// kVBool,
		kNTypes
	};
	//static string objectType[VarClass::kNTypes];
	
	map<string, int> varTypes;
	map<string, int>::const_iterator itVt;
	
	//All variables
	mapVI varmVI;
	mapVUI varmVUI;
	mapVUL varmVUL;
	mapVD varmVD;
	mapVF varmVF;
	mapVB varmVB;
	mapVS varmVS;

	mapAI varmAI;
	mapAUI varmAUI;
	mapAUL varmAUL;
	mapAD varmAD;
	mapAF varmAF;
	mapAB varmAB;
	mapAS varmAS;	
	
	mapI varmI;
	mapUI varmUI;
	mapUL varmUL;
	mapS varmS;
	mapB varmB;
	mapD varmD;
	mapF varmF;
	
	mapTB varmTB;
	
	itMapVI itVI;
	itMapVUI itVUI;
	itMapVUL itVUL;
	itMapVD itVD;
	itMapVF itVF;
	itMapVB itVB;
	itMapVS itVS;

	itMapAI itAI;
	itMapAUI itAUI;
	itMapAUL itAUL;
	itMapAD itAD;
	itMapAF itAF;
	itMapAB itAB;
	itMapAS itAS;

	itMapI itI;
	itMapUI itUI;
	itMapUL itUL;
	itMapS itS;
	itMapB itB;
	itMapD itD;
	itMapF itF;
	itMapTB itTB;
	
	//list of variables
	vector<string> _varnames;
	std::map<string, std::pair<string,int> > _varTypes;

private:
  
	//backup maps for systeamtic uncertainty variations
	mapVI uncmVI;
	mapVUI uncmVUI;
	mapVUL uncmVUL;
	mapVD uncmVD;
	mapVF uncmVF;
	
	mapI uncmI;
	mapUI uncmUI;
	mapUL uncmUL;
	mapD uncmD;
	mapF uncmF;
	
	bool _nextEvent;
	
	//ClassDef(VarClass,0)

};

#endif
