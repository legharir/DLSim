#include "Terminal.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

#include "MathTools.h"

Terminal::Terminal(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem* parent)
    : QGraphicsLineItem(x1, y1, x2, y2, parent)
{
    QGraphicsLineItem::setAcceptHoverEvents(true);
    QGraphicsLineItem::setAcceptDrops(true);
}

void Terminal::setHighlighted(bool highlight)
{
	m_highlighted = highlight;
}

void Terminal::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_highlighted || option->state & QStyle::State_MouseOver)
	{
		painter->setPen(Qt::cyan);
	}
	painter->drawLine(line());
}

QPainterPath Terminal::shape() const
{
	QPainterPath path;
	QRectF rect(line().p1(), line().p2());
	path.addRect(rect.marginsAdded(QMarginsF(2, 2, 2, 2)));
	return path;
}

QRectF Terminal::boundingRect() const
{
	return QGraphicsLineItem::boundingRect();
}

void Terminal::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	const auto midpoint = MathTools::midpoint(line());
	emit mousePressed(QGraphicsLineItem::mapToScene(midpoint));
}

void Terminal::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	emit mouseMoved(event->scenePos());
}

void Terminal::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	emit mouseReleased(event->scenePos());
}
