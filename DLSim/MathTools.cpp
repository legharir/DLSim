#include "MathTools.h"

namespace MathTools
{
	qreal avg(qreal p1, qreal p2)
	{
		return (p1 + p2) / 2;
	}

	QPointF midpoint(const QLineF& line)
	{
		return QPointF(avg(line.x1(), line.x2()), avg(line.y1(), line.y2()));
	}
};
