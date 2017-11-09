#ifndef ETAT__COUT__H
#define ETAT__COUT__H


namespace Etat {

  /// class Cout - 
  class Cout {
    // Attributes
  private:
    int inc;
    int black;
    int blue;
    int green;
    int discard;
    int life;
    int permanent;
    int meule;
    int exile;
    // Operations
  public:
    int GetDiscard () const;
    int GetLife () const;
    int GetPermanent () const;
    int GetMeule () const;
    int GetExile () const;
    int GetInc () const;
    int GetBlue () const;
    int GetBlack () const;
    int GetGreen () const;
    void SetCost (int inc = 0, int blue = 0, int black = 0, int green = 0, int discard = 0, int life = 0, int permanent = 0, int exile = 0, int meule = 0);
    // Setters and Getters
  };

};

#endif
