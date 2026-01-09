
/********** SIMPLE GUI FRAMEWORK FUNCTION PARSER MODULE **********/

#ifndef _FUNCTIONPARSER_HPP
#define _FUNCTIONPARSER_HPP

#include <iostream>  // Debug only
#include <cstdint>
#include <vector>

namespace sgf
{
    
enum class  FPError
{
    NONE                            = 0,
    ILLEGAL_DECLARATION_CHARACTER   = 1,
    INVALID_DECLARATION_SYNTAX      = 2
};

/* DESC */
class FunctionParser
{
private:
    struct ExpressionChunk
    {
        uint16_t        index;  // Position in definition string at which the chunk starts
        union
        {
            uint32_t    length; // Indicates a chunk length to right from position `index`
            float       number; // If chunk is of number type, in the end this gets its numeric value
        }               data;
        uint8_t         type;   // Type of the chunk, can tell what can be done with it
    };

    static const wchar_t    CH_EQUALS;
    static const wchar_t    CH_LEFT_PARENTHESIS;
    static const wchar_t    CH_RIGHT_PARENTHESIS;
    static const uint8_t    ECT_OPERATOR;
    static const uint8_t    ECT_NUMBER;
    static const uint8_t    ECT_SYMBOL;
    static const wchar_t    OP_ADD;
    static const wchar_t    OP_DIV;
    static const wchar_t    OP_MUL;
    static const wchar_t    OP_POW;
    static const wchar_t    OP_SUB;
    
    std::wstring                    argName;
    void                            decode();
    std::vector<ExpressionChunk>    defChunks;
    std::wstring                    defString;
    FPError                         error;
    std::wstring                    funName;
    static bool                     isLetter(wchar_t ch);
    void                            postfixize();

public:
    FunctionParser(std::wstring defString);
    FunctionParser(const FunctionParser& other);
    FunctionParser operator=(const FunctionParser& other);
    std::wstring    getArgumentName()           const;
    std::wstring    getDefinitionString()       const;
    FPError         getError()                  const;
    std::wstring    getFunctionName()           const;
    float           getValue(float argument)    const;
};

}
    
#endif
