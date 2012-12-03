/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFXUI_BUTTON
#define OFXUI_BUTTON

#include "ofxUIWidgetWithLabel.h"

class ofxUIButton : public ofxUIWidgetWithLabel
{
public:    
    ofxUIButton() {}
    
    ofxUIButton(string _name, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = false; 
        init(_name, &_value, w, h, x, y, _size);
    }

    ofxUIButton(string _name, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = true;         
        init(_name, _value, w, h, x, y, _size);
    }

    // DON'T USE THE NEXT CONSTRUCTORS
    // This is maintained for backward compatibility and will be removed on future releases
    
    ofxUIButton(float x, float y, float w, float h, bool _value, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = false; 
        init(_name, &_value, w, h, x, y, _size);
        ofLogWarning("OFXUIBUTTON: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUIButton(float w, float h, bool _value, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = false;         
        init(_name, &_value, w, h, 0, 0, _size);        
        ofLogWarning("OFXUIBUTTON: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }    
    
    ofxUIButton(float x, float y, float w, float h, bool *_value, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = true;         
        init(_name, _value, w, h, x, y, _size);
        ofLogWarning("OFXUIBUTTON: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUIButton(float w, float h, bool *_value, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = true;         
        init(_name, _value, w, h, 0, 0, _size);
        ofLogWarning("OFXUIBUTTON: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }    
    
    ~ofxUIButton()
    {
        if(!useReference)
        {
            delete value; 
        }
    }
    
    virtual void init(string _name, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    //init(string _name, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM)    
    {
        rect = new ofxUIRectangle(x,y,w,h); 
		name = _name; 		
		kind = OFX_UI_WIDGET_BUTTON; 		
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect); 
        
		label = new ofxUILabel(w+padding*2.0,0, (name+" LABEL"), name, _size); 
		label->setParent(label); 
		label->setRectParent(rect); 
        label->setEmbedded(true);		
        drawLabel = true;
        label->setVisible(drawLabel);      
        
        if(useReference)
        {
            value = _value; 
        }
        else
        {
            value = new bool(); 
            *value = *_value; 
        }
        
        setValue(*_value);         
    }
        
    virtual void draw() 
    {
        ofPushStyle(); 
        
        ofEnableBlendMode(OF_BLENDMODE_ALPHA); 
        
        drawPadded();
        drawPaddedOutline();        
        
        drawBack();
        
        drawOutline();
        drawOutlineHighlight();
        
        drawFill();
        drawFillHighlight();
        
        ofPopStyle();
    }
    
    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
        label->setDrawPadding(false);
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
        label->setDrawPaddingOutline(false);
	}  

    virtual void mouseMoved(int x, int y) 
    {
        if(rect->inside(x, y))
        {
            state = OFX_UI_STATE_OVER;         
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
        }
        stateChange();         
    }
    
    virtual void mouseDragged(int x, int y, int button) 
    {
        if(hit)
        {
            if(rect->inside(x, y))
            {                
                state = OFX_UI_STATE_DOWN;         
            }    
            else                
            {
                hit = false;
                state = OFX_UI_STATE_NORMAL;        
                setValue(false); 
                triggerEvent(this);
            }
            stateChange();     
        }
    }
    
    virtual void mousePressed(int x, int y, int button) 
    {
        if(rect->inside(x, y))
        {
            hit = true;
            state = OFX_UI_STATE_DOWN;         
            setValue(true); 
			triggerEvent(this); 			
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
        }
        stateChange();         
    }
    
    virtual void mouseReleased(int x, int y, int button) 
    {
        if(hit)
        {
#ifdef TARGET_OPENGLES
            state = OFX_UI_STATE_NORMAL;        
#else            
            if(rect->inside(x, y))
            {
                state = OFX_UI_STATE_OVER; 
            }
            else
            {
                state = OFX_UI_STATE_NORMAL;                         
            }
#endif 
            setValue(false); 
			triggerEvent(this); 
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;         
        }
        stateChange();         
        hit = false; 
    }
    
    virtual void stateChange()
    {                
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {            
                draw_fill_highlight = false;             
                draw_outline_highlight = false;  
				label->unfocus(); 								
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = true;  
				label->focus(); 								
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_fill_highlight = true;            
                draw_outline_highlight = false;             
				label->focus(); 					
            }
                break;
            case OFX_UI_STATE_SUSTAINED:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = false;                         
				label->unfocus(); 								
            }
                break;            
                
            default:
                break;
        }        
    }
	
    virtual void setVisible(bool _visible)
    {
        visible = _visible; 
        label->setVisible(visible); 
    }
    
	ofxUILabel *getLabel()
	{
		return label; 
	}
	
	virtual void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
		ofxUIRectangle *labelrect = label->getRect(); 
		float h = labelrect->getHeight(); 
		float ph = rect->getHeight(); 
		
		labelrect->y = ph/2.0 - h/2.0; 
        
        if(!drawLabel)
        {
            paddedRect->width = rect->width+padding*2.0; 
        }
        else
        {            
            paddedRect->width += label->getPaddingRect()->width+padding; 	
        }
	}	
	
	bool getValue()
	{
		return *value; 
	}
    
    void setLabelVisible(bool _visible)
    {
        drawLabel = _visible; 
        label->setVisible(drawLabel); 
    }
	
    virtual void setValue(bool _value)
	{
		*value = _value;         
        draw_fill = *value; 
        label->setDrawBack((*value));         
	}
	
	void toggleValue() {
        setValue(!(*value));
	}
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    bool *value; 
    bool useReference; 
    bool drawLabel; 
}; 

#endif
