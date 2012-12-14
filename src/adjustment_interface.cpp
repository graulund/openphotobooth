#include "adjustment_interface.h"
#include <cmath>

// IAdjustment::IAdjustment()
// {

// }

IAdjustment::IAdjustment(int newSize, int newAdjust)
{
    imageSize_ = newSize;
	adjust_ = newAdjust;
}

void IAdjustment::setAdjust(int newAdjust)
{
	adjust_ = newAdjust;
}

int IAdjustment::getAdjust()
{
	return adjust_;
}

std::string IAdjustment::getName()
{
	return name_;
}

int IAdjustment::unclip(int value)
{
	return std::min(255, std::max(0, value));
}

unsigned char IAdjustment::unclip(unsigned char value)
{
	return std::min((unsigned char)255, std::max((unsigned char)0, value));
}

/**
 * COLORIZE
 * Uniformly shifts the colors in an image towards the given color.
 * Adjust is from 0 to 100, the higher the closer.
 * Arguments are adjust and target r, g, b values.
 */
void IAdjustment::colorize(unsigned char * pxlPtr, int adjust, unsigned char target_r, unsigned char target_g, unsigned char target_b){
	unsigned char r, g, b;
	int channel;
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			r -= (unsigned char)((r - target_r) * (float)(adjust / 100.0F));
			g -= (unsigned char)((g - target_g) * (float)(adjust / 100.0F));
			b -= (unsigned char)((b - target_b) * (float)(adjust / 100.0F));
			
			// Saving the subpixels back
			pxlPtr[i-2] = IAdjustment::unclip(r);
			pxlPtr[i-1] = IAdjustment::unclip(g);
			pxlPtr[i]   = IAdjustment::unclip(b);
		}
	}
}

/**
 * Converting RGB to HSV.
 * Assumes argument is an array with (at least) 3 elements and returns one with 3.
 * Conversion formulas adapted from http://en.wikipedia.org/wiki/HSV_color_space
 */
float * IAdjustment::rgbToHSV(unsigned char r, unsigned char g, unsigned char b){
	float rr, gg, bb, h, s, v, d, maxval, minval;
	float *hsv = new float[3];
	
	rr = r / 255.0F;
	gg = g / 255.0F;
	bb = b / 255.0F;
	
	maxval = std::max(std::max(rr, gg), bb);
	minval = std::min(std::min(rr, gg), bb);
	
	v = maxval;
	d = maxval - minval;
	
	if (maxval == 0) {
		s = 0;
	} else {
		s = d / maxval;
	}
	
	if (maxval == minval) {
		h = 0;
	} else {
		if (maxval == rr) {
			h = (gg - bb) / d + ((gg < bb) ? 6.0F : 0.0F);
		} else if (maxval == gg) {
			h = (bb - rr) / d + 2.0F;
		} else if (maxval == bb) {
			h = (rr - gg) / d + 4.0F;
		}
		
		h = h / 6.0F;
	}
	
	hsv[0] = h; hsv[1] = s; hsv[2] = v;
	return hsv;
}

/**
 * Converting HSV to RGB.
 * Again, assumes argument is an array with (at least) 3 elements and returns one with 3.
 */
unsigned char * IAdjustment::hsvToRGB(float h, float s, float v){
	float f, p, q, t, r, g, b;
	unsigned char *rgb = new unsigned char[3];
	int i;
	
	i = (int)std::floor(h * 6.0F);
	f = h * 6.0F - i;
	p = v * (1.0F - s);
	q = v * (1.0F - f * s);
	t = v * (1.0F - (1.0F - f) * s);
	/*
	 p = v * (1 - s)
	 q = v * (1 - f * s)
	 t = v * (1 - (1 - f) * s)
	 */
	
	switch (i % 6) {
		case 0:
			r = v; g = t; b = p;
			break;
		case 1:
			r = q; g = v; b = p;
			break;
		case 2:
			r = p; g = v; b = t;
			break;
		case 3:
			r = p; g = q; b = v;
			break;
		case 4:
			r = t; g = p; b = v;
			break;
		case 5:
			r = v; g = p; b = q;
			break;
	}
	
	rgb[0] = (unsigned char)(r * 255.0F);
	rgb[1] = (unsigned char)(g * 255.0F);
	rgb[2] = (unsigned char)(b * 255.0F);
	return rgb;
}