
/********** SIMPLE GUI FRAMEWORK RECTANGLE MODULE **********/

#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include "SFML/Graphics.hpp"
#include "SGF/Types.hpp"

namespace sgf
{

/* Literal SFML drawable rectangle wrapper, that introduces features of a primitive
 * interactive rectangular area. */
class Rectangle
{
    // Allow canvas to access `sfmlRect` in drawing purposes, we trust it on this
    friend class Canvas;

private:
	Color3D	           color;
    bool               containsText;
    int                id;
    KeyboardListener   keyboardListener;
    MouseListener      mouseListener;
    void*              meta;
    Vector2D 		   position;
	int 			   priority;
	TextProperties*    textProps;
    bool               requestedText;
	sf::RectangleShape sfmlRect;
    sf::Text*          sfmlTextPtr;
	Vector2D 		   size;
    bool               visible;

protected:
    Canvas* canvas;

public:
	Rectangle();
	virtual ~Rectangle();
    bool                    contains(Vector2D position) const;
    virtual void            copy(Rectangle* other);
	virtual Color3D	        getColor() const;
    bool                    getContainsText() const;
    float                   getHeight() const;
    int                     getID() const;
    KeyboardListener        getKeyboardListener() const;
    void*                   getMeta();
    MouseListener           getMouseListener() const;
	virtual Vector2D        getPosition() const;
	int 	 		        getPriority() const;
	virtual Vector2D        getSize() const;
    virtual TextProperties* getText();
    float                   getWidth() const;
    virtual bool            getVisible() const;
    float                   getX() const;
    float                   getY() const;
    
    // These two methods invoke keyboard and mouse listeners with given parameters 
    void                    onKeyboardInput(int data);
    void                    onMouseInput(MouseEvent event, Vector2D position);
    
    virtual void            onAdd();
    virtual void            onRemove();
    virtual void            onTick(int tickIndex);
	void 			        updateText();
    virtual void            setColor(Color3D color);
    
    // Rectangle can store only one callback method per device.
    void                    setKeyboardListener(KeyboardListener callback);
    void                    setMouseListener(MouseListener callback);
    
    void                    setMeta(void* meta);
    virtual void            setPosition(Vector2D position);
	virtual void            setPriority(int priority);
	virtual void            setSize(Vector2D size);
    
    /* This method provides a source of text data for this rectangle, which in return
     * later (on calling canvas `add` with this rectangle as parameter) receives
     * a dedicated SFML Text instance which can be customized through provided
     * TextProperties instance. */
    virtual void            setText(TextProperties* properties);
    
    virtual void            setVisible(bool visible);
};

}

#endif
