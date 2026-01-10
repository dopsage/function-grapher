
#include "Application.hpp"
#include "SGF/FunctionParser.hpp"

using namespace std;
using namespace sgf;

int main()
{
    //FunctionParser f = FunctionParser(L"twi(spa)=spa*(spa-1)*(spa+2)-spa^((spa-1.25)^2/(2*spa^2))+0.000625");
    /*FunctionParser f = FunctionParser(L"f(x)=2x*5"); // + * 
    wcout << L"Definition\t" << f.getDefinitionString() << endl;
    wcout << L"Function\t" << f.getFunctionName() << endl;
    wcout << L"Argument\t" << f.getArgumentName() << endl;
    
    int error = (int)f.getError();
    if(error)   wcout << L"Error:\t" << error << endl;
    else for(int i = -3; i < 4; i++)
        wcout << L"f(" << i << L")=" << f.getValue(i) << endl;
    
    return 0;*/
    
    Application app;
    
    // Maybe some resources config or something? ...
    
    return app.run();
}
