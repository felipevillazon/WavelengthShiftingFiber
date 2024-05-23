#ifndef FiActionInitialization_h
#define FiActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "FiRunAction.hh"

/// Action initialization class.

class FiActionInitialization : public G4VUserActionInitialization
{
  public:
  FiActionInitialization();
  ~FiActionInitialization();
  
  virtual void Build() const;
};



#endif

    
