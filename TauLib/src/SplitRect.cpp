///
/// @file
/// @brief CPP file for SplitRect routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include "SplitRect.h"
#include <assert.h>

using namespace std;

///
/// @brief SplitRectIntoLineRects For drawing lines of text in a rectangle area this routine return a vector of rects where
/// each rect is the height needed to draw a line of text.  This is particularly useful for a menu or a screen of text.
///
vector<Tau_Rect> SplitRectIntoLineRects(const Tau_Rect& rect, int heightOfEachLine) {
    vector<Tau_Rect> subRects;
    assert(heightOfEachLine > 0);

    if (heightOfEachLine > 0) {
        int top = rect.y;
        while (top + heightOfEachLine < rect.h) {
            subRects.emplace_back(rect.x, top, rect.w, heightOfEachLine);
            top += heightOfEachLine;
        }
    }

    return subRects;
}

///
/// @brief GetRectOfTextLine For drawing lines of text in a rectangle area this routine return a rect of a line index
/// to draw a line of text.  index 0 is the top line, 1 is the next tline.  index -1 is the bottom line.  -2 is the line above that.
///
Tau_Rect GetRectOfTextLine(const Tau_Rect& outerRect, int heightOfEachLine, int lineIndex) {
    Tau_Rect ret_rect { 0,0,0,0 };

    vector<Tau_Rect> rects = SplitRectIntoLineRects(outerRect, heightOfEachLine);
    if (lineIndex < 0)
        lineIndex += (int) rects.size();  // index -1 is the last line.  -2 is the line above that.

    if ((lineIndex >= 0) && (lineIndex < rects.size()))
        ret_rect = rects[lineIndex];

    return ret_rect;
}

///
/// @brief GetRectOfTextLine For drawing lines of text in a rectangle area this routine return a rect of a line index
/// to draw a line of text.  index 0 is the top line, 1 is the next tline.  index -1 is the bottom line.  -2 is the line above that.
///
Tau_Rect GetRectOfTextLine(const Tau_Rect& outerRect, TTF_Font_Shared font, int lineIndex) {
    assert(font != nullptr);

    int height = TTF_FontHeight(font);
    return GetRectOfTextLine(outerRect, height, lineIndex);
}
