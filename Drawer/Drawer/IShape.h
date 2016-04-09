#pragma once
class IShape
{
public:
	virtual ~IShape();

	Gdiplus::Rect GetBoundingBox() const;
	void SetBoundingBox(const Gdiplus::Rect& rect);
	
	virtual bool IsShapePoint(const Gdiplus::Point& shapePoint) const = 0;
	
	Gdiplus::Point GetPosition() const;
	void SetPosition(const Gdiplus::Point& diffPoint);
	void ChangeShape(SelectionBoxMarkerState marker, const Gdiplus::Point& newPoint);
	
	virtual bool IsCorrectWidth(int newWidth) const = 0;
	virtual bool IsCorrectHeight(int newHeight) const = 0;
	virtual ShapeType GetShapeType() const = 0;

protected:
	IShape(const Gdiplus::Rect &rect);
	Gdiplus::Point GetBoundingBoxCenter() const;

private:
	Gdiplus::Rect m_boundingBox;
};

