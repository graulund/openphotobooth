#include "adjustment_interface.h"
#include <cmath>
#include <map>

// IAdjustment::IAdjustment()
// {

// }

IAdjustment::IAdjustment(int newSize, int newAdjust)
{
    imageSize_ = newSize;
	adjust_    = newAdjust;
	options_   = NULL;
}

void IAdjustment::setAdjust(int newAdjust)
{
	adjust_ = newAdjust;
}

int IAdjustment::getAdjust()
{
	return adjust_;
}

void IAdjustment::setOptions(int * newOptions)
{
	options_ = newOptions;
}

int * IAdjustment::getOptions()
{
	return options_;
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
 * CURVES
 * Curves implementation using bezier curves.
 * Nine values given. x2 and y2 can be omitted using -1 for the coordinates.
 * Selected channel to modify with the curves is either:
 *   0 => r,
 *   1 => g,
 *   2 => b,
 *   3 => rgb (all channels)
 */
void IAdjustment::curves(unsigned char * pxlPtr, int selectedChannel, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3){
	int channel, r, g, b;
	std::map<int,int> bezier;
	
	// Optional ctrl-point x2,y2
	if (x2 < 0 || y2 < 0) {
		x2 = x1; y2 = y1;
	}
	// Calculate the bezier!
	bezier = IAdjustment::bezier(x0, y0, x1, y1, x2, y2, x3, y3, 0, 255);
	// If the curve starts after x = 0, initialize it with a flat line
	if (x0 > 0) {
		for (int i = 0; i < x0; i++) {
			bezier[i] = x0;
		}
	}
	// And the same with the end point.
	if (x3 < 255) {
		for (int i = x3 + 1; i <= 255; i++) {
			bezier[i] = x3;
		}
	}
	
	// Alright, we've got the curve! Time to manipulate the pixels!
	for (int i = 0; i < imageSize_; i++)
	{
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0)
		{
			r = pxlPtr[i];
		}
		else if (channel == 1)
		{
			g = pxlPtr[i];
		}
		else
		{
			b = pxlPtr[i];
			
			// Handling the subpixels
			// --> RED CHANNEL
			if (selectedChannel == 0 || selectedChannel == 3) {
				r = bezier[r];
			}
			// --> GREEN CHANNEL
			if (selectedChannel == 1 || selectedChannel == 3) {
				g = bezier[g];
			}
			// --> RED CHANNEL
			if (selectedChannel == 2 || selectedChannel == 3) {
				b = bezier[b];
			}
			
			// Saving the subpixels back
			pxlPtr[i-2] = IAdjustment::unclip(r);
			pxlPtr[i-1] = IAdjustment::unclip(g);
			pxlPtr[i]   = IAdjustment::unclip(b);
			// DONE!!!
		}
	}
	
	bezier.clear();
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

/**
 * Calculate a bezier curve.
 * Start (0) and end (3) point, with two points in between.
 * Ported from the good folks at CamanJS https://github.com/meltingice/CamanJS/blob/master/src/core/calculate.coffee
 */
std::map<int,int> IAdjustment::bezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int lowBound, int highBound){
	std::map<int,int> bezier;
	
	int Cx, Bx, Ax, Cy, By, Ay, curveX, curveY;
	float t;
	
	Cx = 3 * (x1 - x0);
    Bx = 3 * (x2 - x1) - Cx;
    Ax = x3 - x0 - Cx - Bx;
	
    Cy = 3 * (y1 - y0);
    By = 3 * (y2 - y1) - Cy;
    Ay = y3 - y0 - Cy - By;
	
	for (int i; i < 1000; i++) {
		t = i / 1000.0F;
		
		curveX = (int)std::floor((Ax * std::pow(t, 3.0F)) + (Bx * std::pow(t, 2.0F)) + (Cx * t) + x0);
		curveY = (int)std::floor((Ay * std::pow(t, 3.0F)) + (By * std::pow(t, 2.0F)) + (Cy * t) + y0);
		
		if (lowBound && curveY < lowBound) {
			curveY = lowBound;
		} else if (highBound && curveY > highBound) {
			curveY = highBound;
		}
		bezier[curveX] = curveY;
	}
	
	// Search for missing values and use linear interpolation to approximate
	if (bezier.size() < (x3 + 1)) {
		for (int i = 0; i <= x3; i++) {
			if (bezier.count(i) <= 0) {
				int leftX, leftY, rightX, rightY;
				leftX = i-1;
				leftY = bezier[i-1];
				
				for (int j = i; j <= x3; j++) {
					if (bezier.count(j) > 0) {
						rightX = j;
						rightY = bezier[j];
						break;
					}
				}
				
				bezier[i] = leftY + ((rightY - leftY) / (rightX - leftX)) * (i - leftX);
			}
		}
	}
	
	// Edge case
	if (bezier.count(x3) <= 0) {
		bezier[x3] = bezier[x3-1];
	}
	
	return bezier;
}