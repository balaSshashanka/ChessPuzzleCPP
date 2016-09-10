#include <iostream>
#include "Output.h"

#include "GameController.h"
using namespace std;

int main()
{
    GameController game;
    bool val = game.Simulate();
     //(val==1)?cout<<"Enemy Commander defeated":cout<<"User Defeated";
         Output* out;
         out = Output::getInstance();
         cout<<out->jsonMsg;
    return 0;
}
