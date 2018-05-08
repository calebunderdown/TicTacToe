/////////////////////////////////////////////////////////////////////
// This is a widget for use in peg puzzle games.  It allows a peg to
// be placed or removed from a slot.  The peg can also be set to 
// one of several colors.
// $Revision: 1.1 $
//   $Log: peg.cpp,v $
//   Revision 1.1  2017/03/29 13:47:31  1ea49c2b19284e86b645075d033e28d0
//   Initial revision
//
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include "peg.h"
#include "term.h"

using namespace std;

//constructors
Peg::Peg() : Peg(0, 0)
{
    //this constructor's work is done by the other version
}


Peg::Peg(int _x, int _y) : Widget(_x, _y, 3, 1)
{
    _color = DEFAULT;
    _present = false;
    _selected = false;
}


//widget functions
void 
Peg::handleEvent(Event *e)
{
    //the peg does not respond to events
}


void 
Peg::display()
{
    //set the cursor position and draw the beginning of the hole
    cout << cursorPosition(x(), y());
    cout << ' ';

    //set the color of the peg
    if(color() == RED) {
        cout << red;
    } else if(color() == BLUE) {
        cout << blue;
    } else if(color() == GREEN) {
        cout << green;
    } else if(color() == YELLOW) {
        cout << yellow;
    }

    //if it is selected, display in reverse video
    if(selected()) {
        cout << reverseVideo;
    }

    //draw the peg itself
    if(present()) {
        cout << 'X';
    } else {
        cout << ' ';
    }

    //finish out the hole in normal color
    cout << normal << ' ';

    cout.flush();  //all done!
}


//handle peg color
void 
Peg::color(PegColor _color)
{
    this->_color = _color;
    display();
}


PegColor 
Peg::color()
{
    return this->_color;
}


//present is true if there is a peg in this hole
void 
Peg::present(bool _present)
{
    this->_present = _present;
    display();
}


bool 
Peg::present()
{
    return this->_present;
}


//pegs can also be selected, this causes them to 
//display in reverse video
void 
Peg::selected(bool _selected)
{
    this->_selected = _selected;
    display();
}


bool 
Peg::selected()
{
    return this->_selected;
}
