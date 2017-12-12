#include "Etat.h"
#include "Test/TestRecord.h"
#include <iostream>

using namespace std;
using namespace Etat;


int main(int argc,char* argv[]) 
{
    //Exemple exemple;
    //exemple.setX(53);
    if (argc == 1 )
        cout << "It works !"<< endl;
    else if (argc == 2 )
    {
        if ((string)argv[1] == "record")
            Test::TestRecord();
         
    }else
        cout << "trop d'arguments"<<endl;
        

    return 0;
}
