//
// Labeled Ellipse
//

#ifndef LABELEDELLIPSE_H
#define LABELEDELLIPSE_H
#include "label.h"
#include "ellipse.h"

class LabeledEllipseShape : public Label,
 public EllipseShape {
	public:
		LabeledEllipseShape(SimpleWindow &w,
		 const Position &Center, const color c = Red,
		 string Text = "R", float Length = 1,
		 float Height = 2);
		void Draw();
};
#endif
