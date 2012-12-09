#include "ImageAdjustment.h"

using namespace std;

// Constructor for no-adjust adjustments
ImageAdjustment::ImageAdjustment(string name_){
	name = name_;
}

// Constructor for most adjustments
ImageAdjustment::ImageAdjustment(std::string name_, int adjust_){
	name   = name_;
	adjust = adjust_;
}

// Constructor for gamma adjustment
/*ImageAdjustment::ImageAdjustment(std::string name_, float fadjust_){
	name    = name_;
	fadjust = fadjust_;
}*/

// Constructor for colorize adjustment
ImageAdjustment::ImageAdjustment(std::string name_, int adjust_, unsigned char r_, unsigned char g_, unsigned char b_){
	name   = name_;
	adjust = adjust_;
	r      = r_;
	g      = g_;
	b      = b_;
}