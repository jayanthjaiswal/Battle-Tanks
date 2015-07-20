#include <math.h>
#include <assert.h>
#include "ray.h"

RaySegment::RaySegment(SimpleWindow &w,
 const Position &Start, const Position &End,
 const color &c, float t, bool a) :
 WindowObject(w, Start), EndPoint(End), Color(c),
 Thickness(t), Arrow(a)  {
   // No body needed
}

RaySegment::RaySegment(SimpleWindow &w,
 float StartX, float StartY, float EndX, float EndY,
 const color &c, float t, bool a) :
 WindowObject(w, Position(StartX, StartY)),
 EndPoint(Position(EndX, EndY)), Color(c),
 Thickness(t), Arrow(a) {
   // No body needed
}

Position RaySegment::GetStartPoint() const {
   return (GetPosition());
}

void RaySegment::GetStartPoint(float &x, float &y) const {
   GetPosition(x, y);
   return;
}

Position RaySegment::GetEndPoint() const {
   return EndPoint;
}

void RaySegment::GetEndPoint(float &x, float &y) const {
   x = EndPoint.GetXDistance();
   y = EndPoint.GetYDistance();
   return;
}

void RaySegment::GetPoints(Position &Start,
 Position &End) const {
   Start = GetPosition();
   End = EndPoint;
}

color RaySegment::GetColor() const {
   return Color;
}

float RaySegment::GetThickness() const {
   return Thickness;
}

float RaySegment::GetLength() const {
   float x, y;
   GetPosition(x, y);
   x -= EndPoint.GetXDistance();
   y -= EndPoint.GetYDistance();
   return sqrt(x*x + y*y);
}

bool RaySegment::HasArrow() const {
   return Arrow;
}

void RaySegment::SetStartPoint(const Position &p) {
   SetPosition(p);
   return;
}

void RaySegment::SetStartPoint(float x, float y) {
   SetPosition(x, y);
   return;
}

void RaySegment::SetEndPoint(const Position &p) {
   EndPoint = p;
   return;
}

void RaySegment::SetEndPoint(float x, float y) {
   EndPoint = Position(x, y);
   return;
}

void RaySegment::SetPoints(const Position &Start,
 const Position &End) {
   SetPosition(Start);
   EndPoint = End;
   return;
}

void RaySegment::SetColor(const color &c) {
   assert(c >= 0 && c < MaxColors);
   Color = c;
   return;
}

void RaySegment::SetThickness(float t) {
   Thickness = t;
   return;
}

void RaySegment::SetArrowhead() {
   Arrow = true;
   return;
}

void RaySegment::ClearArrowhead() {
   Arrow = false;
   return;
}

void RaySegment::Draw() {
   Position NewStartVector, NewStartPoint;
   Position NewEndVector, NewEndPoint;
   Position Start = GetPosition();
   Position End = GetEndPoint();
   const float t = GetThickness();
   const float length = GetLength();
   Position RayVector = EndPoint - Start;
   bool TooShortToDraw;
   bool TooShortForArrow = false;

   if (length == 0)
       return;

   // Line cannot be drawn properly if its length
   // is less than its width
   TooShortToDraw = length < t;

   // Line should not be drawn with arrow if it is
   // shorter than the arrow
   if (length < (4 * t)) TooShortForArrow = true;

   // Compute new start point (to offset the extra bit that LineTo includes)
   float CutOff = Thickness / 2.0;

   if (TooShortToDraw) {
      NewStartVector = Position(RayVector.GetXDistance() / 2.0,
      RayVector.GetYDistance() / 2.0);
      NewStartPoint = Start + NewStartVector;
   }
   else {
      // If not too short, then move the start point such that the line
      //  will appear to begin at the proper point.
      NewStartVector = Position(RayVector.GetXDistance() * CutOff / length,
       RayVector.GetYDistance() * CutOff / length);
      NewStartPoint = Start + NewStartVector;
   }

   if (Arrow)
      End = DrawArrow(Color);
   else if (!TooShortToDraw) {
      // If we don't have an arrow and the line length isn't too short,
      // then move the end point such that the line will appear to end
      // at the proper position.
      float NewLength = length - Thickness / 2.0;
      Position NewEndVector(RayVector.GetXDistance() * NewLength / length,
       RayVector.GetYDistance() * NewLength / length);
      Position NewEndPoint = GetPosition() + NewEndVector;
      End = NewEndPoint;
   }
   else {
      End = NewStartPoint;
   }

   Start = NewStartPoint;

   // Don't want to draw anything if the line
   // is too short and there is an arrow
   if (!Arrow || !TooShortForArrow)
      GetWindow().RenderLine(Start, End, GetColor(), t);

   return;
}

Position RaySegment::DrawArrow(const color &ArrowColor) {
   const float length = GetLength();
   const float ArrowWidth = 2.0 * Thickness;
   const float ArrowLength = 2.0 * ArrowWidth;
   Position FirstVertex, SecondVertex, ThirdVertex;
   
   // In the following code, *Vector refer to vector objects that have
   // an endpoint at the origin (like most vectors).

   const Position StartPoint = GetPosition();

   // Find new endpoint of line by finding the vector from
   // the start point to the endpoint, rescaling the vector,
   // and then adding it to the start point
   Position RayVector = EndPoint - StartPoint;
   float NewLength = length - ArrowLength;
   float scalefactor = NewLength / length;
   Position NewRayVector(RayVector.GetXDistance() * scalefactor,
    RayVector.GetYDistance() * scalefactor);
   Position NewEndPoint = StartPoint + NewRayVector;
   FirstVertex = EndPoint;

   // Find other vertices.
   if (EndPoint.GetXDistance() == StartPoint.GetXDistance()) {
      SecondVertex = NewEndPoint + Position(ArrowWidth, 0);
      ThirdVertex = NewEndPoint - Position(ArrowWidth, 0);
   }
   else {
      float Slope = (EndPoint.GetYDistance() -
       StartPoint.GetYDistance()) / (EndPoint.GetXDistance() -
       StartPoint.GetXDistance());

      if (Slope == 0) {
         SecondVertex = NewEndPoint + Position(0, ArrowWidth);
         ThirdVertex = NewEndPoint - Position(0, ArrowWidth);
      }
      else {
         float PerpSlope = - 1 / Slope;
         Position TempPosition(1.0, PerpSlope);
         float TempLength = sqrt(1 + PerpSlope * PerpSlope);
         SecondVertex = NewEndPoint + Position(
          TempPosition.GetXDistance() * ArrowWidth / TempLength,
          TempPosition.GetYDistance() * ArrowWidth / TempLength);
         ThirdVertex = NewEndPoint - Position(
          TempPosition.GetXDistance() * ArrowWidth / TempLength,
          TempPosition.GetYDistance() * ArrowWidth / TempLength);
      }
   }

   // Create an array containing the positions of the
   // vertices of the triangle
   vector<Position> TrianglePoints(3);
   TrianglePoints[0] = FirstVertex;
   TrianglePoints[1] = SecondVertex;
   TrianglePoints[2] = ThirdVertex;

   // Draw the triangle
   GetWindow().RenderPolygon(TrianglePoints, 3, ArrowColor, false);

   return NewEndPoint;
}

void RaySegment::Erase() {
   Position Start = GetPosition();
   Position End = GetEndPoint();
   const float t = GetThickness();
   const float length = GetLength();

   Position RayVector = EndPoint - Start;
   float NewLength = Thickness / 2.0;
   Position NewStartVector(RayVector.GetXDistance() * NewLength / length,
    RayVector.GetYDistance() * NewLength / length);
   Position NewStartPoint = Start + NewStartVector;
   Start = NewStartPoint;

   if (Arrow)
      End = DrawArrow(White);
   else {
      NewLength = length - Thickness / 2.0;
      Position NewEndVector(RayVector.GetXDistance() * NewLength / length,
       RayVector.GetYDistance() * NewLength / length);
      Position NewEndPoint = GetPosition() + NewEndVector;
      End = NewEndPoint;
   }
   GetWindow().RenderLine(Start, End, White, t);
   return;
}

