// -*- C++ -*-
//
// Package:    DiLepMcFilter
// Class:      DiLepMcFilter
// 
/**\class DiLepMcFilter DiLepMcFilter.cc MyFilters/DiLepMcFilter/src/DiLepMcFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Felix Hoehle
//         Created:  Fri Dec  3 14:16:41 CET 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//
// class declaration
//

class DiLepMcFilter : public edm::EDFilter {
   public:
      explicit DiLepMcFilter(const edm::ParameterSet&);
      ~DiLepMcFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      edm::InputTag ttbarEventTag_;
	int lowerpdgId_;
	int upperpdgId_;
//	bool isLeptonic(reco::GenParticle part);
	bool isMuonic(reco::GenParticle part);
	bool isElectronic(reco::GenParticle part);
	bool isHadronic(reco::GenParticle part);
      // ----------member data ---------------------------
};
//bool DiLepMcFilter::isLeptonic(reco::GenParticle part){
//	if(abs(part.pdgId()) >= 11 && abs(part.pdgId()) <= 14 ) return true;
//	else return false;
//}
bool DiLepMcFilter::isMuonic(reco::GenParticle part){
	return (abs(part.pdgId()) >= 13 && abs(part.pdgId()) <= 14 );
}
bool DiLepMcFilter::isHadronic(reco::GenParticle part){
	return (abs(part.pdgId()) <=6 && part.pdgId()!= 0 );
}
bool DiLepMcFilter::isElectronic(reco::GenParticle part){
        return (abs(part.pdgId()) >= 11 && abs(part.pdgId()) <= 12 );
}

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DiLepMcFilter::DiLepMcFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
	ttbarEventTag_ = iConfig.getUntrackedParameter<edm::InputTag>("ttbarEventTag");
//	lowerpdgId_ = iConfig.getParameter<int>("lowerpdgId");
//	upperpdgId_ = iConfig.getParameter<int>("upperpdgId");
}


DiLepMcFilter::~DiLepMcFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
DiLepMcFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	edm::Handle< edm::View< std::vector<reco::GenParticle> > > ttbarEvent; //std::vector< std::vector<std::vector<reco::GenParticle> > >
    	iEvent.getByLabel(ttbarEventTag_, ttbarEvent);
	reco::GenParticle WplusDecay1; WplusDecay1 = (*ttbarEvent)[3][0];
	reco::GenParticle WplusDecay2; WplusDecay2 = (*ttbarEvent)[4][0];
	
	reco::GenParticle WminusDecay1; WminusDecay1 = (*ttbarEvent)[8][0];
	reco::GenParticle WminusDecay2; WminusDecay2 = (*ttbarEvent)[9][0];


	bool muonicDecayWplus = (isMuonic(WplusDecay1) && isMuonic(WplusDecay2));
	bool muonicDecayWminus = (isMuonic(WminusDecay1) && isMuonic(WminusDecay2));

	bool hadronicDecayWplus = (isHadronic(WplusDecay1) && isHadronic(WplusDecay2));
	bool hadronicDecayWminus = (isHadronic(WminusDecay1) && isHadronic(WminusDecay2));
	//if( (leptonicDecayWplus && !leptonicDecayWminus) || (!leptonicDecayWplus && leptonicDecayWminus) ){
   		
		//std::cout<<"bling"<<std::endl;
	//	return true;
	//}
	//else return false;
	return (isMuonic(WplusDecay1) ||  isElectronic(WplusDecay1)) && (isElectronic(WminusDecay1) || isMuonic(WminusDecay1) ); 
}

// ------------ method called once each job just before starting event loop  ------------
void 
DiLepMcFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DiLepMcFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(DiLepMcFilter);
