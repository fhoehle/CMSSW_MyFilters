// -*- C++ -*-
//
// Package:    DiMuonMcFilter
// Class:      DiMuonMcFilter
// 
/**\class DiMuonMcFilter DiMuonMcFilter.cc MyFilters/DiMuonMcFilter/src/DiMuonMcFilter.cc

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

#include "CMSSW_MyFilters/DiLepMcFilter/interface/DiLepMcFilters.h"
//
// class declaration
//

class DiMuonMcFilter : public edm::EDFilter {
   public:
      explicit DiMuonMcFilter(const edm::ParameterSet&);
      ~DiMuonMcFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      edm::InputTag ttbarEventTag_;
	int lowerpdgId_;
	int upperpdgId_;
        bool invert_;
      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DiMuonMcFilter::DiMuonMcFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
	ttbarEventTag_ = iConfig.getUntrackedParameter<edm::InputTag>("ttbarEventTag");
        invert_  = iConfig.getParameter<bool>("invert");
//	lowerpdgId_ = iConfig.getParameter<int>("lowerpdgId");
//	upperpdgId_ = iConfig.getParameter<int>("upperpdgId");
}


DiMuonMcFilter::~DiMuonMcFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
DiMuonMcFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	edm::Handle< edm::View< std::vector<reco::GenParticle> > > ttbarEvent; //std::vector< std::vector<std::vector<reco::GenParticle> > >
    	iEvent.getByLabel(ttbarEventTag_, ttbarEvent);
        if (ttbarEvent->size() != 10){ std::cout<<"error ttbarEvent has WRONG size "<<ttbarEvent->size()<<std::endl; return false;}
	reco::GenParticle WplusDecay1; WplusDecay1 = (*ttbarEvent)[3][0];
	reco::GenParticle WplusDecay2; WplusDecay2 = (*ttbarEvent)[4][0];
	
	reco::GenParticle WminusDecay1; WminusDecay1 = (*ttbarEvent)[8][0];
	reco::GenParticle WminusDecay2; WminusDecay2 = (*ttbarEvent)[9][0];

        bool res = (isMuonic(WplusDecay1)  && isMuonic(WminusDecay1) );
	return (invert_) ? ! res : res; 
}

// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonMcFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DiMuonMcFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonMcFilter);
