// Class automatically generated by Dev-C++ New Class wizard

#include "script.h" // class's header file

// -- class constructor -------------------------------------------
script::script(symbolTablePtr _symbolTable)
{
   inputVars.clear();
   outputVars.clear();

   smbTable = _symbolTable;
}

// -- class destructor --------------------------------------------
script::~script()
{
   inputVars.clear();
   outputVars.clear();
}

// --   -----------------------------------------------------------
void script :: addTriggerCoords(int x, int y, int size_x, int size_y)
{
   coordX = x;
   coordY = y;
   sizeX  = size_x;
   sizeY  = size_y;
}

// --   -----------------------------------------------------------
void script :: addNewInputVar(string name, unsigned int value)
{
    assert(inputVars.count(name) == 0);
    inputVars[name] = value;
}

// --   -----------------------------------------------------------
void script :: addNewOutputVar(string name, unsigned int value)
{
    assert(outputVars.count(name) == 0);
    outputVars[name] = value;
}

// --   -----------------------------------------------------------
bool script :: checkInputVars()
{
    bool allOk = true;
    for( map<string, unsigned int>::iterator it = inputVars.begin() ;
         it != inputVars.end() && allOk;
         it++ )
    {
//        cout << "analyzing var " << it->first << " current value is " << *(smbTable->GetPointerByName(it->first)) << endl;
        if( *(smbTable->GetPointerByName(it->first)) != inputVars[it->first] )
        {
           allOk = false;
        }
    }
    if( allOk )
    {        
        this->updateOutputVars();
//        cout << " correct check " << endl;                
    }
//    else
//    {
//        cout << " bad check " << endl;
//    }

    return allOk;
}

// --   -----------------------------------------------------------
bool script :: updateOutputVars()
{
   for( map<string, unsigned int>::iterator it = outputVars.begin() ;
        it != outputVars.end();
        it++ )
   {
//       cout << it->first << endl;
       *(smbTable->GetPointerByName(it->first)) = outputVars[it->first];
   }

}

