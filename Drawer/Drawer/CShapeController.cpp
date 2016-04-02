#include "stdafx.h"
#include "CShapeController.h"

CShapeController::CShapeController(IShape* shape, IShapeDrawer* shapeDrawer)
	:m_shape(shape),
	m_shapeDrawer(shapeDrawer),
	m_selectionBox(new CSelectionBoxDrawer())
{
}

CShapeController::~CShapeController()
{
}

Gdiplus::Rect CShapeController::GetBoundingBox() const
{
	return m_shape->GetBoundingBox();
}

void CShapeController::Draw(const HDC hdc) const
{
	m_shapeDrawer->Draw(hdc, m_shape->GetBoundingBox());
}

void CShapeController::DrawSelectionBox(const HDC hdc) const
{
	m_selectionBox->DrawSelectionBorder(hdc, m_shape->GetBoundingBox());
}

Gdiplus::Point CShapeController::GetPosition() const
{
	return m_shape->GetPosition();
}

void CShapeController::SetPosition(const Gdiplus::Point &point)
{
	m_shape->SetPosition(point);
}

ShapeType CShapeController::GetShapeType() const
{
	return m_shape->GetShapeType();
}

bool CShapeController::IsShapePoint(const Gdiplus::Point& point) const
{
	return m_shape->IsShapePoint(point);
}

SelectionBoxMarkerState CShapeController::IsPointAtMarker(const Gdiplus::Point& point) const
{
	return m_selectionBox->IsPointAtMarker(point, m_shape->GetBoundingBox());
}

void CShapeController::ChangeShapeSize(SelectionBoxMarkerState state, const Gdiplus::Point& point)
{
	m_shape->ChangeShape(state, point);
}