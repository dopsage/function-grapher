
#include "SGF/FunctionParser.hpp"

using namespace sgf;

const wchar_t   FunctionParser::CH_EQUALS               = L'=';
const wchar_t   FunctionParser::CH_LEFT_PARENTHESIS     = L'(';
const wchar_t   FunctionParser::CH_RIGHT_PARENTHESIS    = L')';
const uint8_t   FunctionParser::ECT_OPERATOR            = 1;
const uint8_t   FunctionParser::ECT_NUMBER              = 0;
const uint8_t   FunctionParser::ECT_SYMBOL              = 2;
const wchar_t   FunctionParser::OP_ADD                  = L'+';
const wchar_t   FunctionParser::OP_DIV                  = L'/';
const wchar_t   FunctionParser::OP_MUL                  = L'*';
const wchar_t   FunctionParser::OP_POW                  = L'^';
const wchar_t   FunctionParser::OP_SUB                  = L'-';

bool FunctionParser::isLetter(wchar_t ch)
{
// NOTICE: Only ASCII letters are considered, but unicode ones may be implemented too
    return (ch > 0x40 && ch < 0x5b) || (ch > 0x60 && ch < 0x7b);
}

void FunctionParser::decode()
{
    int     savedPos        = 0;
    int     savedLength     = 0;
    bool    wasEqualSign    = false;
    int     gatheredNames   = 0;
    for(int pos = 0; pos < defString.length(); pos++)
    {
        wchar_t tar = defString[pos];
        
        if(wasEqualSign)
        {
            /*** Process function expression ***/
            
            // Implement expression chunks addition ...
            
            std::wcout << L"Process:\t" << tar << std::endl;
        }
        else
        {
            /*** Process function definition ***/
            
            if(!isLetter(tar))
            {
                if(tar == CH_LEFT_PARENTHESIS)
                {
                    if(gatheredNames > 0 || savedLength == 0)
                    {
                        /* 1. Argument name is being gathered (or is finished already)
                         * 2. Length of a function name is 0 */
                        error = FPError::INVALID_DECLARATION_SYNTAX;
                        break;
                    }
                    
                    /* Until now, the function name was being gathered. Save it and
                     * setup saved data for argument name gathering. */
                    funName         = defString.substr(savedPos, savedLength);
                    savedPos        = pos + 1;
                    savedLength     = 0;
                    gatheredNames++;
                    continue;
                }
                else if(tar == CH_RIGHT_PARENTHESIS)
                {
                    if(gatheredNames == 1 && savedLength > 0)
                    {
                        // This time, the argument name is already gathered.
                        argName = defString.substr(savedPos, savedLength);
                        gatheredNames++;
                        continue;
                    }
                    else
                    {
                        /* 1. Collection of argument name did not even start, cannot finish it
                         * 2. Collection of argument name is already finished */
                        error = FPError::INVALID_DECLARATION_SYNTAX;
                        break;
                    }
                }
                else if(tar == CH_EQUALS)
                {
                    if(gatheredNames == 2)
                    {
                        // Prepare saved data for expression processing and go on with it
                        savedPos        = pos + 1;
                        savedLength     = 0;
                        wasEqualSign    = true;
                        continue;
                    }
                    else
                    {
                        // Starting expression without function|argument name collected
                        error = FPError::INVALID_DECLARATION_SYNTAX;
                        break;
                    }
                }
                else
                {
                    /* Characters different than letters, parenthesses and equals are
                     * not allowed in function declaration */
                    error = FPError::ILLEGAL_DECLARATION_CHARACTER;
                    break;
                }
            }
            
            savedLength++;
        }
    }
    
    postfixize();
}

void FunctionParser::postfixize()
{
    // Rearange expression chunks in vector to postfix form, and convert numerics in
    // number typed ECs, so it is ready for getValue method to use for value calculation ...
}

FunctionParser::FunctionParser(std::wstring defString) :
                argName(L""),
                defChunks(),
                defString(defString),
                error(FPError::NONE),
                funName(L"")
{
    decode();
    postfixize();
}

FunctionParser::FunctionParser(const FunctionParser& other) :
                FunctionParser(other.getDefinitionString())
{
    
}

FunctionParser FunctionParser::operator=(const FunctionParser& other)
{
    defString = other.getDefinitionString();
    decode();
    postfixize();
    
    return *this;
}

std::wstring FunctionParser::getArgumentName() const
{
    return argName;
}

FPError FunctionParser::getError() const
{
    return error;
}

std::wstring FunctionParser::getDefinitionString() const
{
    return defString;
}

std::wstring FunctionParser::getFunctionName() const
{
    return funName;
}

float FunctionParser::getValue(float argument) const
{
    if(error != FPError::NONE) return 123.456f;
    
    // To implement ...
    return argument;
}
