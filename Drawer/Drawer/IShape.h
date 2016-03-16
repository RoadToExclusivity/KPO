#pragma once
class IShape
{
public:
	virtual ~IShape();
	LPRECT GetBoundingBox() const;
	virtual void Draw(CDC*, LPRECT) const = 0;

protected:
	IShape(int x, int y, int width, int height);

private:
	LPRECT m_boundingBox;
};

