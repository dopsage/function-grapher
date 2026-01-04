
/********** SIMPLE GUI FRAMEWORK TYPES HEADER **********/

#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace sgf
{
    typedef uint8_t                 Byte;
    typedef std::uintptr_t          ExplicitPointer;    // For getMetaPtr reinterpretation
    typedef uint32_t                Milliseconds;
    
    /* NOTICE:  On Windows wchar_t stores half of unicode character (2 bytes)!
     *          this requires some exclusive support to include in the future ... */
    typedef const std::vector<
    std::pair<wchar_t, wchar_t>>    UnicodeRangeVector;
    
    class   Button;
    class   Canvas;
    class   InputParser;
    class   Rectangle;
    class   ScrollView;
    class   TextInput;
    struct  TextProperties;
    class   VList;
    class   VSlider;
    
    // All of unicode
    const UnicodeRangeVector IF_ALL =
    {
        {0x00000000, 0x0010FFFF}
    };
    
    // Visible ASCII
    const UnicodeRangeVector IF_ASCII =
    {
        {0x00000020, 0x0000007E}
    };
    
    // Math expression
    const UnicodeRangeVector IF_MATH =
    {
        {0x00000028, 0x0000002B},   // ( ) * +
        {0x00000030, 0x00000039},   // 0-9
        {0x0000002D, 0x0000002F},   // - . /
        {0x0000003D, 0x0000003D},   // =
        {0x00000041, 0x0000005A},   // A-Z
        {0x0000005E, 0x0000005E},   // ^
        {0x00000061, 0x0000007A}    // a-z
    };
    
    enum class  MouseEvent  { DOWN, MOVE, UP };
    struct      Vector2D    { float x, y; };
    struct      Color3D     { Byte r, g, b; };
    
    typedef void (*ButtonListener)      (int rectangleId, Canvas* canvasPtr);
    typedef void (*KeyboardListener)    (int keycode, wchar_t unicode, int rectangleId, Canvas* canvasPtr);
    typedef void (*MouseListener)       (MouseEvent event, Vector2D position, int rectangleId, Canvas* canvasPtr);
    typedef void (*VSliderListener)     (float value, int rectangleId, Canvas* canvasPtr);
    typedef void (*TextInputListener)   (std::wstring content, int rectangleId, sgf::Canvas* canvasPtr);
}

#endif
