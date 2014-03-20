#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

bool isLeptonic(reco::GenParticle part){
	if(abs(part.pdgId()) >= 11 && abs(part.pdgId()) <= 14 ) return true;
	else return false;
}
bool isMuonic(reco::GenParticle part){
	return (abs(part.pdgId()) >= 13 && abs(part.pdgId()) <= 14 );
}
bool isHadronic(reco::GenParticle part){
	return (abs(part.pdgId()) <=6 && part.pdgId()!= 0 );
}
bool isElectronic(reco::GenParticle part){
        return (abs(part.pdgId()) >= 11 && abs(part.pdgId()) <= 12 );
}

