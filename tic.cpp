#include <iostream>
#include <iomanip>
#include <algorithm>
#include <unistd.h>
#include "term.h"
#include "tic.h"
#include "application.h"


using namespace std;
static string defaultMessage = "Arrows to move cursor, Enter to select";

//constructor
Tic::Tic() : Widget(1, 1, 53, 6)
{
    int _x, _y; //screen position of the pegs

    _x = 4;
    _y = 3;

    //set up the peg board
   
    pegs.push_back(new Peg(10, 10));
	pegs.push_back(new Peg(15, 10));
	pegs.push_back(new Peg(20, 10));
	pegs.push_back(new Peg(10, 12));
	pegs.push_back(new Peg(15, 12));
	pegs.push_back(new Peg(20, 12));
	pegs.push_back(new Peg(10, 14));
	pegs.push_back(new Peg(15, 14));
	pegs.push_back(new Peg(20, 14));
	

    
    //set up initial selection
	first = 1;
    cursor = 1;
    toMove = -1;
    pegs[cursor]->selected(true);
    
    //set up initial message
    message = defaultMessage;
}


//destructor
Tic::~Tic() 
{
    //delete all the pegs
    for(int i=0; i<pegs.size(); i++) {
        delete pegs[i];
    }
}


//widget functions
void 
Tic::handleEvent(Event *e)
{
    //we only want keyboard events here!
    if(e->type() != "keyboard") { return; }
    
    //assume the default message
    message=defaultMessage;
    
    KeyboardEvent *k = (KeyboardEvent *) e;
    
    switch(k->key()) {
        case ESC:
            //exit the application
            ((Application *) parent())->running(false);
            break;
            
        case LEFT:
            //move the cursor left
            selectPeg(cursor-1);
            break;
			
		case UP:
            //move the cursor up
            selectPeg(cursor-3);
            break;
            
		case DOWN:
            //move the cursor left
            selectPeg(cursor+3);
            break;
			
        case RIGHT:
            //move the cursor right
            selectPeg(cursor+1);
            break;
            
        case ENTER:
         if(!pegs[cursor]->present()){
			 if(first){
				 pegs[cursor]->present(true);
				 pegs[cursor]->color(RED);
				 first = false;
				 end();
			 }else{
				 pegs[cursor]->present(true);
				 pegs[cursor]->color(BLUE);
				 first = true;
				 end();
			 }
			 
		 }
            break;  
    }
    
    display(); 
}

void 
Tic::display()
{
	cout<<cursorPosition(58,8)<<"INSTRUCTIONS";
	cout<<cursorPosition(30,10)<< "1. Alternate placing";
	cout<<cursorPosition(51,10)<< blue << "Blue X's" << normal;
	cout<<cursorPosition(60,10)<< "and ";
	cout<<cursorPosition(64,10)<< red << "Red X's" << normal;
	cout<<cursorPosition(72,10)<< "on the grid.";
	cout<<cursorPosition(30,11)<<"2. When either color places three X's in a row vertically, horizontally, or diagonally";
	cout<<cursorPosition(33,12)<<"that color wins.";
	

    //display the grid
	cout<<cursorPosition(14,9)<<blue<< "|" << endl;
	cout<<cursorPosition(14,10)<< blue <<"|" << endl;
	cout<<cursorPosition(14,11)<< blue << "|" << endl;
	cout<<cursorPosition(14,12)<< blue << "|" << endl;
	cout<<cursorPosition(14,13)<< blue << "|" << endl;
	cout<<cursorPosition(14,14)<< blue << "|" << endl;
	cout<<cursorPosition(14,15)<< blue << "|" << normal << endl;
	
	cout<<cursorPosition(18,9)<<blue<< "|" << endl;
	cout<<cursorPosition(18,10)<< blue <<"|" << endl;
	cout<<cursorPosition(18,11)<< blue << "|" << endl;
	cout<<cursorPosition(18,12)<< blue << "|" << endl;
	cout<<cursorPosition(18,13)<< blue << "|" << endl;
	cout<<cursorPosition(18,14)<< blue << "|" << endl;
	cout<<cursorPosition(18,15)<< blue << "|" << normal << endl;
	
	cout<<cursorPosition(10,11)<< blue << "-" << endl;
	cout<<cursorPosition(11,11)<< blue << "-" << endl;
	cout<<cursorPosition(12,11)<< blue << "-" << endl;
	cout<<cursorPosition(13,11)<< blue << "-" << endl;
	cout<<cursorPosition(14,11)<< blue << "-" << endl;
	cout<<cursorPosition(15,11)<< blue << "-" << endl;
	cout<<cursorPosition(16,11)<< blue << "-" << endl;
	cout<<cursorPosition(17,11)<< blue << "-" << endl;
	cout<<cursorPosition(18,11)<< blue << "-" << endl;
	cout<<cursorPosition(19,11)<< blue << "-" << endl;
	cout<<cursorPosition(20,11)<< blue << "-" << endl;
	cout<<cursorPosition(21,11)<< blue << "-" << endl;
	cout<<cursorPosition(11,11)<< blue << "-" << normal << endl;
	
	cout<<cursorPosition(10,13)<< blue << "-" << endl;
	cout<<cursorPosition(11,13)<< blue << "-" << endl;
	cout<<cursorPosition(12,13)<< blue << "-" << endl;
	cout<<cursorPosition(13,13)<< blue << "-" << endl;
	cout<<cursorPosition(14,13)<< blue << "-" << endl;
	cout<<cursorPosition(15,13)<< blue << "-" << endl;
	cout<<cursorPosition(16,13)<< blue << "-" << endl;
	cout<<cursorPosition(17,13)<< blue << "-" << endl;
	cout<<cursorPosition(18,13)<< blue << "-" << endl;
	cout<<cursorPosition(19,13)<< blue << "-" << endl;
	cout<<cursorPosition(20,13)<< blue << "-" << endl;
	cout<<cursorPosition(21,13)<< blue << "-" << endl;
	cout<<cursorPosition(11,13)<< blue << "-" << normal << endl;
	
	
	
	//title
	cout<<cursorPosition(11,7)<< green << "TIC TAC TOE" << normal << endl;
	
    //display the pegs
    for(int i=0; i<pegs.size(); i++) {
        pegs[i]->display();
    }
    
    //display the move marker
    if(toMove != -1) {
        cout << cursorPosition(pegs[toMove]->x()+1, pegs[toMove]->y() + 1) << '^';
    }
    
    //display the message
    cout << cursorPosition(x(), y()+25) << left << setw(width()) << message << right;
    
    //flush the buffer
    cout.flush();
}

bool
Tic::end()
{
		if(((pegs[0]->color() == RED and pegs[1]->color()== RED and pegs[2]->color()==RED)) or
	   ((pegs[3]->color() == RED and pegs[4]->color()== RED and pegs[5]->color()==RED)) or
	   ((pegs[6]->color() == RED and pegs[7]->color()== RED and pegs[8]->color()==RED)) or
	   ((pegs[0]->color() == RED and pegs[3]->color()== RED and pegs[6]->color()==RED)) or
	   ((pegs[1]->color() == RED and pegs[4]->color()== RED and pegs[7]->color()==RED)) or
	   ((pegs[2]->color() == RED and pegs[5]->color()== RED and pegs[8]->color()==RED)) or
	   ((pegs[0]->color() == RED and pegs[4]->color()== RED and pegs[8]->color()==RED)) or
	   ((pegs[2]->color() == RED and pegs[4]->color()== RED and pegs[6]->color()==RED))){
		cout <<cursorPosition(12,17) << red << "RED WINS!" << normal << endl;
		return true;
	}
	
	else if(((pegs[0]->color() == BLUE and pegs[1]->color()== BLUE and pegs[2]->color()==BLUE)) or
	   ((pegs[3]->color() == BLUE and pegs[4]->color()== BLUE and pegs[5]->color()==BLUE)) or
	   ((pegs[6]->color() == BLUE and pegs[7]->color()== BLUE and pegs[8]->color()==BLUE)) or
	   ((pegs[0]->color() == BLUE and pegs[3]->color()== BLUE and pegs[6]->color()==BLUE)) or
	   ((pegs[1]->color() == BLUE and pegs[4]->color()== BLUE and pegs[7]->color()==BLUE)) or
	   ((pegs[2]->color() == BLUE and pegs[5]->color()== BLUE and pegs[8]->color()==BLUE)) or
	   ((pegs[0]->color() == BLUE and pegs[4]->color()== BLUE and pegs[8]->color()==BLUE)) or
	   ((pegs[2]->color() == BLUE and pegs[4]->color()== BLUE and pegs[6]->color()==BLUE))){
		cout << cursorPosition(12,17)<< blue << "BLUE WINS!" << normal << endl;
		return true;
	} else if((pegs[0]->present()==true) and 
			  (pegs[1]->present()==true) and
			  (pegs[2]->present()==true) and 
			  (pegs[3]->present()==true) and
			  (pegs[4]->present()==true) and 
			  (pegs[5]->present()==true) and
			  (pegs[6]->present()==true) and 
			  (pegs[7]->present()==true) and
			  (pegs[8]->present()==true)){
				cout<<cursorPosition(10,17)<<"IT IS A DRAW";
		  		return true;}
	
	return false;
}


//insanity functions

//move the cursor to a peg
void 
Tic::selectPeg(int cursor)
{
    //stand firm on invalid moves
    if(cursor < 0 or cursor >= pegs.size()) {
        return;
    }
    
    //first, we deselect the current peg
    pegs[this->cursor]->selected(false);
    
    //next, we select our peg
    this->cursor = cursor;
    pegs[this->cursor]->selected(true);
}



