#include "lellipse.h"

LabeledEllipseShape::LabeledEllipseShape(SimpleWindow &w,
 const Position &Center, const color c, string t, float l,
 float h) : EllipseShape(w, Center, c, l, h),
 Label(w, Center, t, c)  {
	// No code needed
}

void LabeledEllipseShape::Draw() {
	EllipseShape::Draw();
	Label::Draw();
}
