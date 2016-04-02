#pragma once
class IShape
{
public:
	virtual ~IShape();
	Gdiplus::Rect GetBoundingBox() const;
	virtual bool IsShapePoint(const Gdiplus::Point&) const = 0;
	Gdiplus::Point GetPosition() const;
	void SetPosition(const Gdiplus::Point&);
	void ChangeShape(SelectionBoxMarkerState, const Gdiplus::Point&);
	virtual bool IsCorrectWidth(int newWidth) const = 0;
	virtual bool IsCorrectHeight(int newHeight) const = 0;
	virtual ShapeType GetShapeType() const = 0;

protected:
	IShape(Gdiplus::Rect &&rect);
	Gdiplus::Point GetBoundingBoxCenter() const;

private:
	Gdiplus::Rect m_boundingBox;
};

