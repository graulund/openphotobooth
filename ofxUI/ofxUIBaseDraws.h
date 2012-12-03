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

#pragma once

#include "ofxUIWidgetWithLabel.h"

class ofxUIBaseDraws : public ofxUIWidgetWithLabel
{
public:
    ofxUIBaseDraws(float x, float y, float w, float h, ofBaseDraws* _image, string _name)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, _image, _name); 
    }
    
    ofxUIBaseDraws(float x, float y, float w, float h, ofBaseDraws* _image, string _name, bool _showLabel)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, _image, _name); 
        showLabel = _showLabel; 
    }
    
    ofxUIBaseDraws(float w, float h, ofBaseDraws* _image, string _name)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h, _image, _name); 
    }    

    ofxUIBaseDraws(float w, float h, ofBaseDraws* _image, string _name, bool _showLabel)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h, _image, _name); 
        showLabel = _showLabel; 
    }    
    
    void init(float w, float h, ofBaseDraws* _image, string _name)
    {
		name = _name; 				
		kind = OFX_UI_WIDGET_BASE_DRAWS;
        showLabel = true; 
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect); 
        
        draw_back = false; 
        draw_fill = true; 
        
		image = _image; 
        
		label = new ofxUILabel(0,h+padding,(name+" LABEL"),name, OFX_UI_FONT_SMALL); 		
		label->setParent(label); 
		label->setRectParent(rect);    
        label->setEmbedded(true);        
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
    
    virtual void drawFill()
    {
        if(draw_fill)
        {			
			if(image != NULL)
			{			   
				ofFill(); 
				ofSetColor(255); 		
				image->draw(rect->getX(), rect->getY(), rect->width, rect->height); 
			}
        }
    }        

    virtual void setVisible(bool _visible)
    {
        visible = _visible; 
        label->setVisible(showLabel);             
    }    
				
	ofxUILabel *getLabel()
	{
		return label; 
	}
    
    void set(ofBaseDraws *_image)
    {
        image = _image; 
    }
	
	virtual void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
        if(showLabel)
        {
            paddedRect->height += label->getPaddingRect()->height; 		
        }    
        else
        {
            paddedRect->height += padding;
        }
        label->setVisible(showLabel);             
	}	

    virtual bool isDraggable()
    {
        return false; 
    }
    
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	ofBaseDraws *image; 
    bool showLabel; 
}; 
