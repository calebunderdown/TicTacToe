/////////////////////////////////////////////////////////////////////
// This is a widget for use in peg puzzle games.  It allows a peg to
// be placed or removed from a slot.  The peg can also be set to 
// one of several colors.
// $Revision: 1.1 $
//   $Log: peg.h,v $
//   Revision 1.1  2017/03/29 13:47:31  1ea49c2b19284e86b645075d033e28d0
//   Initial revision
//
/////////////////////////////////////////////////////////////////////
#ifndef PEG_H
#define PEG_H
#include "widget.h"

enum PegColor { DEFAULT, RED, BLUE, GREEN, YELLOW };

class Peg : public Widget
{
public:
    //constructors
    Peg();
    Peg(int _x, int _y);

    //widget functions
    virtual void handleEvent(Event *e);
    virtual void display();

    //handle peg color
    virtual void color(PegColor _color);
    virtual PegColor color();

    //present is true if there is a peg in this hole
    virtual void present(bool _present);
    virtual bool present();

    //pegs can also be selected, this causes them to 
    //display in reverse video
    virtual void selected(bool _selected);
    virtual bool selected();

private:
    PegColor _color;  //the peg's color
    bool _present;    //whether it is filled or not
    bool _selected;   //whether or not it is selected
};

#endif
