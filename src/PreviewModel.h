#ifndef __myOpenPhotoBooth__PreviewModel__
#define __myOpenPhotoBooth__PreviewModel__

#include "Model.h"
#include "module_wordBubble.h"

#define BTN_LABL_L "Save"
#define BTN_LABL_M "PRV"
#define BTN_LABL_R "Edit"
#define BTN_NAME_L "PREVLEFT"
#define BTN_NAME_M "PREVMIDDLE"
#define BTN_NAME_R "PREVRIGHT"

 class PreviewModel : public Model
 {
 private:
 	int wrdBblX_, wrdBblY_;
 	bool bFirst_, showBubble_;

 	std::string * wordBubbleStr_;
	module_wordBubble * wordBubble_;
 public:
 	PreviewModel(Model *);

 	void init();
	 
    ofTrueTypeFont * getWordBubble();
    std::string * getWordBubbleStr();
    bool isFirstLetter();

    void showWordBubble(bool);
    bool isBubbleVisible();
    void editBubbleString(int);
	void setWordBubblePos(int, int);
	void setFirstLetter(bool);

	int getWordBubbleX();
	int getWordBubbleY();
 };

#endif