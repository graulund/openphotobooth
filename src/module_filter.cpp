#include "module_filter.h"

#include <cmath>
#include <algorithm>
#include <iostream>

module_filter::module_filter(int size) : imageSize_(size)
{
	ptrArr_[0] = &module_filter::vibrance;
	ptrArr_[1] = &module_filter::saturation;
	ptrArr_[2] = &module_filter::greyscale;
	ptrArr_[3] = &module_filter::brightness;
}

/**
 * IMAGE ADJUSTMENT: BRIGHTNESS
 * Range of adjust is from -100 to 100.
 */
void module_filter::brightness(unsigned char * pxlPtr)
{
	int adjust = 20; //tmp
	int x = (int) floor(255.0F * (adjust / 100.0F));
	
	for (int i = 0; i < imageSize_; i++)
	{
		pxlPtr[i] = module_filter::unclip(pxlPtr[i] + x);
	}
}

/**
 * IMAGE ADJUSTMENT: SATURATION
 * Range of adjust is from -100 to 100.
 */
void module_filter::saturation(unsigned char * pxlPtr){
	int adjust = 80; //tmp
	float x = -0.01F * adjust;
	int channel;
	int r, g, b, maxval;
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			// Getting the maximum value of the 3 subpixels
			maxval = std::max(std::max(r, g), b);
			
			// Handling each subpixel individually
			if(r != maxval){
				r += ((maxval - r) * x);
			}
			if(g != maxval){
				g += ((maxval - g) * x);
			}
			if(b != maxval){
				b += ((maxval - b) * x);
			}
			
			// Saving the subpixels back
			pxlPtr[i-2] = module_filter::unclip(r);
			pxlPtr[i-1] = module_filter::unclip(g);
			pxlPtr[i]   = module_filter::unclip(b);
		}
	}
}

/**
 * IMAGE ADJUSTMENT: VIBRANCE
 * Similar to saturation, but slightly smarter, more subtle.
 * Attempts to boost colors that are less saturated more and boost already saturated colors less.
 * Range of adjust is from -100 to 100.
 */
void module_filter::vibrance(unsigned char * pxlPtr){
	int adjust = 80; //tmp
	adjust = -1 * adjust;
	int channel;
	int r, g, b, maxval;
	float avgval, amtval;
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			// Getting the maximum value of the 3 subpixels
			maxval = std::max(std::max(r, g), b);
			// Get the average value
			avgval = (r + g + b) / 3.0F;
			// Get adjusted average
			amtval = ((std::abs(maxval - avgval) * 2.0F / 255.0F) * adjust) / 100.0F;
			
			// Handling each subpixel individually
			if(r != maxval){
				r += ((maxval - r) * amtval);
			}
			if(g != maxval){
				g += ((maxval - g) * amtval);
			}
			if(b != maxval){
				b += ((maxval - b) * amtval);
			}
			
			// Saving the subpixels back
			pxlPtr[i-2] = module_filter::unclip(r);
			pxlPtr[i-1] = module_filter::unclip(g);
			pxlPtr[i]   = module_filter::unclip(b);
		}
	}
}

/**
 * IMAGE ADJUSTMENT: GREYSCALE
 * No adjust in this. Uses factors directly relating to how the human eye perceives color and values.
 * Derived from http://www.phpied.com/image-fun/
 */
void module_filter::greyscale(unsigned char * pxlPtr){
	int channel;
	unsigned char r, g, b, maxval;
	float avgval, amtval;
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			// Calculate the average value of the channels using the special factors
			avgval = module_filter::unclip((int)(0.3 * r + 0.59 * g + 0.11 * b));
			
			// Saving the subpixels back
			pxlPtr[i-2] = avgval;
			pxlPtr[i-1] = avgval;
			pxlPtr[i]   = avgval;
		}
	}
}

/**
 * IMAGE ADJUSTMENT: CONTRAST
 * Range of adjust is from -100 to 100.
 */
void module_filter::contrast(unsigned char * pxlPtr){
	int adjust = 50; //tmp
	float x = pow((float)(adjust + 100.0F) / 100.0F, 2.0F);
	float pixel;
	for (int i = 0; i < imageSize_; i++) {
		pixel  = pxlPtr[i] / 255.0F;
		pixel -= 0.5F;
		pixel *= x;
		pixel += 0.5F;
		pixel *= 255.0F;
		
		pxlPtr[i] = module_filter::unclip((int)pixel);
	}
}

/**
 * IMAGE ADJUSTMENT: HUE
 * Range is 0 to 100.
 */
void module_filter::hue(unsigned char * pxlPtr){
	int adjust = 50; //tmp
	int channel;
	unsigned char r, g, b;
	unsigned char *rgb;
	float h;
	float *hsv;
	
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			// Load HSV information
			hsv = module_filter::rgbToHSV(r, g, b);
			
			// Change hue
			h  = hsv[0] * 100.0F;
			h += std::abs((float)adjust);
			h  = ((int)h) % 100; // precision loss?
			h /= 100.0F;
			
			rgb = module_filter::hsvToRGB(h, hsv[1], hsv[2]);
			
			// Saving the subpixels back
			pxlPtr[i-2] = module_filter::unclip(rgb[0]);
			pxlPtr[i-1] = module_filter::unclip(rgb[1]);
			pxlPtr[i]   = module_filter::unclip(rgb[2]);
		}
	}
}

/**
 * IMAGE ADJUSTMENT: COLORIZE
 * Uniformly shifts the colors in an image towards the given color.
 * Adjust is from 0 to 100, the higher the closer.
 * Arguments are adjust and target r, g, b values.
 */
void module_filter::colorize(unsigned char * pxlPtr){
	int adjust = 20; //tmp
	unsigned char target_r = 0, target_g = 0, target_b = 255; //tmp
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
			pxlPtr[i-2] = module_filter::unclip(r);
			pxlPtr[i-1] = module_filter::unclip(g);
			pxlPtr[i]   = module_filter::unclip(b);
		}
	}
}

/**
 * IMAGE ADJUSTMENT: INVERT
 * Simply inverts the pixel values. No adjust.
 */
void module_filter::invert(unsigned char * pxlPtr){
	for (int i = 0; i < imageSize_; i++) {
		pxlPtr[i] = 255 - pxlPtr[i];
	}
}

/**
 * IMAGE ADJUSTMENT: SEPIA
 * Applies an adjustable sepia filter to the pixel array. Adjust is between 0 and 100.
 */
void module_filter::sepia(unsigned char * pxlPtr){
	int adjust = 50; //tmp
	unsigned char r, g, b;
	int channel;
	float x = adjust / 100.0F;
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			r = std::min(255.0F, (r * (1.0F-(0.607F*x))) + (g * (0.769F*x)) + (b * (0.189F*x)));
			g = std::min(255.0F, (r * (0.349F*x)) + (g * (1.0F-(0.314F*x))) + (b * (0.168F*x)));
			b = std::min(255.0F, (r * (0.272F*x)) + (g * (0.534F*x)) + (b * (1.0F-(0.869F*x))));
			
			// Saving the subpixels back
			pxlPtr[i-2] = module_filter::unclip(r);
			pxlPtr[i-1] = module_filter::unclip(g);
			pxlPtr[i]   = module_filter::unclip(b);
		}
	}
}

/**
 * IMAGE ADJUSTMENT: GAMMA
 * Adjusts the gamma of the image. Range is from 0 to infinity, but usually kept between 0 and 4-5.
 * Values between 0 and 1 will lessen the contrast, while values greater than 1 will increase it.
 */
void module_filter::gamma(unsigned char * pxlPtr){
	float adjust = 0.5F; //tmp
	for (int i = 0; i < imageSize_; i++) {
		pxlPtr[i] = module_filter::unclip(
						(int)(std::pow((float)(pxlPtr[i] / 255.0F), adjust) * 255.0F)
					);
	}
}

/**
 * IMAGE ADJUSTMENT: NOISE
 * Adds noise to the image from a scale between 1 and 100. (However, there's no actual upper limit
 * to the adjust.)
 */
void module_filter::noise(unsigned char * pxlPtr){
	int adjust = 50; //tmp
	unsigned char r, g, b;
	int noise, channel;
	
	for (int i = 0; i < imageSize_; i++) {
		channel = i % 3;
		// Separating the subpixels into channels
		if (channel == 0) {
			r = pxlPtr[i];
		} else if (channel == 1) {
			g = pxlPtr[i];
		} else {
			b = pxlPtr[i];
			
			noise = (std::rand() % adjust) - adjust/2.0F;
			
			// Making sure we add an equal amount of noise to all channels,
			// so the noise is not color-specific.
			
			pxlPtr[i-2] = module_filter::unclip((int)(r + noise));
			pxlPtr[i-1] = module_filter::unclip((int)(g + noise));
			pxlPtr[i]   = module_filter::unclip((int)(b + noise));
		}
	}
}

/**
 * IMAGE ADJUSTMENT: EXPOSURE
 * Adjusts the exposure of the image using the curves function.
 * Adjust is from -100 to 100. Values < 0 will decrease exposure, values > 0 will increase exposure.
 */
//TODO

// The parts remaining:
// MILESTONE 2:
// * All filters and mirror the preview image (Andy)
// * Facebook integration (Andy & Marcel)
// * Labels and word bubbles (Marcel)
// FINAL:
// * Blue screen filter (Marcel)
// * Filter editing (Andy)

/**
  * Makes sure color values do not exceed 255 or get lower than 0.
  */
int module_filter::unclip(int value)
{
	return std::min(255, std::max(0, value));
}

unsigned char module_filter::unclip(unsigned char value)
{
	return std::min((unsigned char)255, std::max((unsigned char)0, value));
}

/**
 * Converting RGB to HSV.
 * Assumes argument is an array with (at least) 3 elements and returns one with 3.
 * Conversion formulas adapted from http://en.wikipedia.org/wiki/HSV_color_space
 */
float * module_filter::rgbToHSV(unsigned char r, unsigned char g, unsigned char b){
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
unsigned char * module_filter::hsvToRGB(float h, float s, float v){
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

int module_filter::getFilterCount()
{
	return int(FILTER_CNT);
}

void module_filter::getFilters(unsigned char * pxlPtr, int fnctNr)
{
	(*this.*ptrArr_[fnctNr])(pxlPtr);
}
