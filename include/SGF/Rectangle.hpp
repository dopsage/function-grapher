
/********** SIMPLE GUI FRAMEWORK RECTANGLE MODULE **********/

#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include "SFML/Graphics.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Literal SFML drawable rectangle (sf::RectangleShape) wrapper, that introduces features
 * of a primitive interactive rectangular area. Rectangle may declare use of text,
 * in such case canvas associates SFML drawable text (sf::Text) with the rectangle.
 * The text is controlled by playing with text properties instance that every rectangle
 * instance contains and allows to alter (see Types module). */
class Rectangle
{
    // Allow canvas to access `sfmlRect` in drawing purposes, this is just a simple trust
    friend class Canvas;

private:
    Canvas*             canvasPtr;
	Color3D	            color;
    int                 id;
    KeyboardListener    keyboardListener;
    MouseListener       mouseListener;
    void*               metaPtr;
    Vector2D 		    position;
	int 			    priority;
	sf::RectangleShape  sfmlRect;
	Vector2D 		    size;
	TextProperties*     textPtr;
    bool                usingText;
    bool                visible;

public:
	Rectangle();
	virtual ~Rectangle();
    bool                    contains(Vector2D position) const;
    virtual void            copy(Rectangle* other);
    Canvas*                 getCanvasPtr();
	Color3D	                getColor()                  const;
    float                   getHeight()                 const;
    int                     getId()                     const;
    KeyboardListener        getKeyboardListener()       const;
    void*                   getMetaPtr();
    MouseListener           getMouseListener()          const;
    Vector2D                getPosition()               const;
	int 	 		        getPriority()               const;
	Vector2D                getSize()                   const;
    TextProperties*         getText();
    float                   getWidth()                  const;
    float                   getX()                      const;
    float                   getY()                      const;
    bool                    isUsingText()               const;
    bool                    isVisible()                 const;
    
    // These two methods invoke keyboard and mouse listeners with given parameters
    void                    onKeyboardInput(int data);
    void                    onMouseInput(MouseEvent event, Vector2D position);
    
    virtual void            onAdd();
    virtual void            onRemove();
    virtual void            onTick(int tickCount);
    virtual void            setColor(Color3D color);
    
    // Rectangle can store only one callback method per device, did not see reason for not doing so
    void                    setKeyboardListener(KeyboardListener callback);
    void                    setMouseListener(MouseListener callback);
    
    void                    setMetaPtr(void* ptr);
    virtual void            setPosition(Vector2D position);
	virtual void            setPriority(int priority);
	virtual void            setSize(Vector2D size);
    virtual void            setText(TextProperties* properties);
    virtual void            setVisible(bool visible);
};

}

#endif
