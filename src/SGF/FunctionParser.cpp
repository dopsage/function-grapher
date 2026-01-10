
#include "SGF/FunctionParser.hpp"

using namespace sgf;

const wchar_t   FunctionParser::CH_POINT                = L'.';
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

const std::unordered_map<wchar_t, int> FunctionParser::OP_SCORES = 
{
    { OP_ADD, 0 },
    { OP_SUB, 0 },
    { OP_MUL, 1 },
    { OP_DIV, 2 },
    { OP_POW, 3 }
};

bool FunctionParser::isLetter(wchar_t ch)
{
// NOTICE: Only ASCII letters are considered, but unicode ones may be implemented too
    return (ch > 0x40 && ch < 0x5b) || (ch > 0x60 && ch < 0x7b);
}

void FunctionParser::chunkize()
{
    int         gatheredNames   = 0;
    int         openParentheses = 0;
    uint32_t    savedLength     = 0;
    uint16_t    savedPos        = 0;
    bool        wasEqualSign    = false;
    bool        wasPoint        = false;
    uint16_t    defLength       = defString.length();
    for(uint16_t pos = 0; pos <= defLength; pos++)
    {
        // Dollar symbol is used to let all checks run, and optionally unload during last iteration
        wchar_t tar = (pos == defLength ? L'$' : defString[pos]);
        
        if(wasEqualSign)
        {
            /*** Process function expression ***/

            bool        isCharacterIllegal  = true;
            uint32_t    newGN               = gatheredNames;

            // @@@ 1. Check for symbol
            if(isLetter(tar))
            {
                if(gatheredNames == 2)
                {
                    // Symbol just after the numeric? there must be some operator
                    error = FPError::INVALID_EXPRESSION_SYNTAX;
                    break;
                }
                
                if(gatheredNames == 0)
                {
                    // Started reading some symbol
                    savedPos    = pos;
                    savedLength = 0;
                    newGN       = 1;
                }
                
                isCharacterIllegal = false;
            }
            else if(gatheredNames == 1)
            {
                /* Until now, some symbol was being gathered. Validate it and in
                 * positive scenario save it. */
                
                std::wstring symbol = defString.substr(savedPos, savedLength);
                if(symbol != argName)
                {
                    /* For now only argument is considered the right symbol, but in
                     * the future custom symbols like pi or e can be introduced somehow. */
                    error = FPError::UNDEFINED_EXPRESSION_SYMBOL;
                    break;
                }
                
                defChunks.push_back({ savedPos, savedLength, 0.0f, ECT_SYMBOL });
            }
            
            // @@@ 2. Check for numeric
            bool isPoint = (tar == CH_POINT);
            if(isPoint || (tar > 0x2f && tar < 0x3a))
            {
                if(isPoint)
                {
                    if(wasPoint)
                    {
                        // Two points in one numeric? impossibe
                        error = FPError::INVALID_EXPRESSION_SYNTAX;
                        break;
                    }
                    else
                        wasPoint = true;
                }
                    
                
                if(gatheredNames == 1)
                {
                    // Numeric just after the symbol? there must be some operator
                    error = FPError::INVALID_EXPRESSION_SYNTAX;
                    break;
                }
                
                if(gatheredNames == 0)
                {
                    // Started reading some numeric
                    savedPos    = pos;
                    savedLength = 0;
                    newGN       = 2;
                }
                
                isCharacterIllegal = false;
            }
            else if(gatheredNames == 2)
            {
                if(wasPoint && savedLength == 1)
                {
                    // Point does not mean anything alone
                    error = FPError::INVALID_EXPRESSION_SYNTAX;
                    break; 
                }
                
                // Until now, some numeric was being gathered, save it.
                std::wstring number = defString.substr(savedPos, savedLength);
                defChunks.push_back({ savedPos, savedLength, std::stof(number), ECT_NUMBER });
                wasPoint            = false;
            }
            
            // @@@ 3. Check for operator
            bool isLeftPar  = (tar == CH_LEFT_PARENTHESIS);
            bool isRightPar = (tar == CH_RIGHT_PARENTHESIS);
            if( isLeftPar       ||
                isRightPar      ||
                tar == OP_ADD   ||
                tar == OP_DIV   ||
                tar == OP_MUL   ||
                tar == OP_POW   ||
                tar == OP_SUB)
            {
                if(!isLeftPar && !isRightPar && gatheredNames == 0)
                {
                    // Operator just after operator? no way
                    error = FPError::INVALID_EXPRESSION_SYNTAX;
                    break;
                }
                
                // Processed character is an operator
                defChunks.push_back({ pos, 1, 0.0f, ECT_OPERATOR });
                
                /* After closing parenthessis, there must be an operator. For this
                 * purpose, completely unique flag value is used (3) to not trigger above ones. */
                newGN               = isRightPar ? 3 : 0;
                
                isCharacterIllegal  = false;
                openParentheses    += isLeftPar ? +1 : (isRightPar ? -1 : 0);
            }
            
            if( (isCharacterIllegal && pos != defLength) ||
                (openParentheses != 0 && pos == defLength))
            {
                /* 1. Illegal character, unless it is last (unloading) iteration.
                 * 2. Parentheses were not paired properly. */
                error = FPError::ILLEGAL_EXPRESSION_CHARACTER;
                break;
            }
            else if(defChunks.size() == 0 && pos == defLength)
            {
                // Empty expression is not allowed
                error = FPError::INVALID_EXPRESSION_SYNTAX;
                break;
            }
            else
            {
                gatheredNames = newGN;
                savedLength++;
            }
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
                    gatheredNames++;
                    funName         = defString.substr(savedPos, savedLength);
                    savedLength     = 0;
                    savedPos        = pos + 1;
                    continue;
                }
                else if(tar == CH_RIGHT_PARENTHESIS)
                {
                    if(gatheredNames == 1 && savedLength > 0)
                    {
                        // This time, the argument name is already gathered.
                        gatheredNames++;
                        argName = defString.substr(savedPos, savedLength);
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
                        gatheredNames   = 0;
                        savedLength     = 0;
                        savedPos        = pos + 1;
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
            else if(gatheredNames == 2)
            {
                // Name continuation after closing parenthesis? what
                error = FPError::INVALID_DECLARATION_SYNTAX;
                break;
            }
            
            savedLength++;
        }
    }
}

void FunctionParser::postfixize()
{
    // Rearange expression chunks in vector to postfix form, and convert numerics in
    // number typed ECs, so it is ready for getValue method to use for value calculation ...
    
    std::vector<ExpressionChunk> postfix;
    std::stack<ExpressionChunk> operators;
    std::stack<int> operatorContext;
    operatorContext.push(0);
    
    for(int eci = 0; eci < defChunks.size(); eci++)
    {
        ExpressionChunk ec = defChunks[eci];
        
        if(ec.type == ECT_OPERATOR)
        {
            wchar_t currOperChar    = defString[ec.index];
            bool    unloadContext   = false;
            
            if(currOperChar == CH_LEFT_PARENTHESIS)
            {
                // Open new stack context by creating new record of its length on context stack
                operatorContext.push(0);
                continue;
            }
            else if(currOperChar == CH_RIGHT_PARENTHESIS)
            {
                // Mark the current operator stack context for unloading and update context stack
                unloadContext = true;
            }
            
            // notice: it is like this: currOperChar < lastOperChar(never parenthesiss)
            if(unloadContext || (!operators.empty() && OP_SCORES.at(currOperChar) < OP_SCORES.at(defString[operators.top().index])))
            {
                int ocLength = operatorContext.top();
                
                // Encountered lower-ranked operator, thus unload the current operator stack context
                while(ocLength--)
                {
                    postfix.push_back(operators.top());
                    operators.pop();
                }
                
                if(unloadContext && operatorContext.size() != 1)
                    operatorContext.pop();  // unloading non-root context needs stack erasal 
                else
                    operatorContext.top() = 0; 
            }
            
            // Put the current operator onto stack, but beaware that right parenthesis is not an operator
            // and it must be taken into account by checking unload flag.
            if(!unloadContext)
            {
                operators.push(ec);
                operatorContext.top()++;
            }
        }
        else
        {
            postfix.push_back(ec);
        }
    }
    // Unload operators stack to output form in the end
    while(!operators.empty())
    {
        postfix.push_back(operators.top());
        operators.pop();
    }
    
    // Print expression chunks
    for(int eci = 0; eci < postfix.size(); eci++)
    {
        ExpressionChunk ec = postfix[eci];
        std::wcout << defString.substr(ec.index, ec.length) << L" ";
    }
    std::wcout << std::endl;
    
    defChunks = postfix;
}

FunctionParser::FunctionParser(std::wstring defString) :
                argName(L""),
                defChunks(),
                defString(defString),
                error(FPError::NONE),
                funName(L"")
{
    chunkize();
    postfixize();
}

FunctionParser::FunctionParser(const FunctionParser& other) :
                FunctionParser(other.getDefinitionString())
{
    
}

FunctionParser FunctionParser::operator=(const FunctionParser& other)
{
    defString = other.getDefinitionString();
    chunkize();
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
    
    // Single chunk case
    if(defChunks.size() == 1)
        return defChunks[0].type == ECT_SYMBOL ? argument : defChunks[0].number;
    
    std::vector<ExpressionChunk> defChunksCopy = defChunks;
    int offset = 0;
    
    while(defChunksCopy.size() != 1)
    {
        ExpressionChunk* triplet[3] =
        {
            &defChunksCopy[offset],
            &defChunksCopy[offset + 1],
            &defChunksCopy[offset + 2]
        };
        
        if(triplet[0]->type != ECT_OPERATOR && triplet[1]->type != ECT_OPERATOR && triplet[2]->type == ECT_OPERATOR)
        {
            float leftNumber    = triplet[0]->type == ECT_SYMBOL ? argument : triplet[0]->number;
            float rightNumber   = triplet[1]->type == ECT_SYMBOL ? argument : triplet[1]->number;
            float answer        = 0.0f;
            
            switch(defString[triplet[2]->index])
            {
                case OP_ADD:
                    answer = leftNumber+rightNumber;
                    break;
                case OP_DIV:
                    answer = leftNumber/rightNumber;
                    break;
                case OP_MUL:
                    answer = leftNumber*rightNumber;
                    break;
                case OP_POW:
                    answer = std::pow(leftNumber, rightNumber);
                    break;
                case OP_SUB:
                    answer = leftNumber-rightNumber;
                    break;
            }
            
            // Exchange calculation with answer, then start whole processing again by resetting the offset
            defChunksCopy.erase(defChunksCopy.begin() + offset, defChunksCopy.begin() + offset + 3);
            defChunksCopy.insert(defChunksCopy.begin() + offset, { 0, 0, answer, ECT_NUMBER });
            offset = 0;
        }
        else
            offset++;
    }
    
    return defChunksCopy[0].number;
}
