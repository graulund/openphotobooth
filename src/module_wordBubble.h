#ifndef __myOpenPhotoBooth__Module_Wordbubble_
#define __myOpenPhotoBooth__Module_Wordbubble_

#include <ofMain.h>
#include <string>

class module_wordBubble
{
private:
	bool bFirst;
    std::string typeStr;

	ofTrueTypeFont * typeFont_;
public:
	module_wordBubble();

	ofTrueTypeFont * getString();
};

#endif
