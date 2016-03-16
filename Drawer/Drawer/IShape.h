#pragma once
class IShape
{
public:
	virtual ~IShape();
	const Gdiplus::Rect* GetBoundingBox() const;
	virtual void Draw(const HDC, const Gdiplus::Rect*) const = 0;

protected:
	IShape(int x, int y, int width, int height);

private:
	Gdiplus::Rect* m_boundingBox;
};

