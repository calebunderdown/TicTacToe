#ifndef TIC_H
#define TIC_H
#include <vector>
#include <string>
#include "widget.h"
#include "peg.h"

class Tic : public Widget
{
public:
    //constructor
    Tic();
    
    //destructor
    ~Tic();

    //widget functions
    virtual void handleEvent(Event *e);
    virtual void display();

    virtual void selectPeg(int cursor);
   
	
	virtual bool end();

private:
	bool first;
    std::vector<Peg *> pegs;
    int cursor;  //the peg where the cursor is
    int toMove;  //the peg selected to move
    std::string message;  //the message to display below the board
};
#endif
