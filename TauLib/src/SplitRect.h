#pragma once

///
/// @file
/// @brief Header file for SplitRect routines.
/// @author Steve Simpson, steve@iterator.com, a.k.a. Axanar (AutoBleem project)
/// 

#include "Tau_Rect.h"
#include "TTF_Font_Shared.h"
#include <vector>

///
/// @brief SplitRectIntoLineRects For drawing lines of text in a rectangle area this routine return a vector of rects where
/// each rect is the height needed to draw a line of text.  This is particularly useful for a menu or a screen of text.
///
std::vector<Tau_Rect> SplitRectIntoLineRects(const Tau_Rect& rect, int heightOfEachLine);

///
/// @brief GetRectOfTextLine For drawing lines of text in a rectangle area this routine return a rect of a line index
/// to draw a line of text.  index 0 is the top line, 1 is the next tline.  index -1 is the bottom line.  -2 is the line above that.
///
Tau_Rect GetRectOfTextLine(const Tau_Rect& outerRect, int heightOfEachLine, int lineIndex);
Tau_Rect GetRectOfTextLine(const Tau_Rect& outerRect, TTF_Font_Shared font, int lineIndex);
