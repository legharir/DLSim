#pragma once

#include <QPoint>
#include <QLine>

namespace MathTools
{
	qreal avg(qreal p1, qreal p2);

	QPointF midpoint(const QLineF& line);
};