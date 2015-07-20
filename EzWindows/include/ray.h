#ifndef RAYSEGMENT_H
#define RAYSEGMENT_H

#include "wobject.h"

class RaySegment : public WindowObject {
   public:
      RaySegment(SimpleWindow &w, const Position &StartPoint,
       const Position &EndPoint, const color &c = Black,
       float Thickness = 0.1f, bool Arrowhead = false);
      RaySegment(SimpleWindow &w, float StartX, float StartY,
       float EndX, float EndY, const color &c = Black,
       float Thickness = 0.1f, bool Arrowhead = false);
      Position GetStartPoint() const;
      void GetStartPoint(float &x, float &y) const;
      Position GetEndPoint() const;
      void GetEndPoint(float &x, float &y) const;
      void GetPoints(Position &Start, Position &End) const;
      color GetColor() const;
      float GetThickness() const;
      float GetLength() const;
      bool HasArrow() const;
      void SetStartPoint(const Position &p);
      void SetStartPoint(float x, float y);
      void SetEndPoint(const Position &p);
      void SetEndPoint(float x, float y);
      void SetPoints(const Position &StartPoint,
       const Position &EndPoint);
      void SetColor(const color &c);
      void SetThickness(float t);
      void SetArrowhead();
      void ClearArrowhead();
      void Draw();
      void Erase();
   private:
      Position DrawArrow(const color &c);
      Position EndPoint;
      float Thickness;
      color Color;
      bool Arrow;
};

#endif
