#pragma once
class IShape
{
public:
	virtual ~IShape();
	const Gdiplus::Rect* GetBoundingBox() const;
	virtual void Draw(const HDC, const Gdiplus::Rect*) const = 0;
	virtual void DrawSelectionBox(const HDC, const Gdiplus::Rect*) const = 0;
	virtual bool IsShapePoint(const Gdiplus::Point&) const = 0;
	Gdiplus::Point GetPosition() const;
	void SetPosition(const Gdiplus::Point&);
	SelectionBoxMarkerState IsPointAtMarker(Gdiplus::Point &point, const Gdiplus::Rect* rect) const;
	void ChangeShape(SelectionBoxMarkerState state, Gdiplus::Point &newPoint);
	virtual bool IsCorrectSize(int newWidth, int newHeight) const = 0;
	virtual ShapeType GetShapeType() const = 0;

protected:
	IShape(int x, int y, int width, int height);
	Gdiplus::Point GetBoundingBoxCenter() const;

private:
	Gdiplus::Rect* m_boundingBox;
};

