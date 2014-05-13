#include "gradientbackground.h"

#include <QDebug>
#include <QRectF>

#include <cairo.h>
#include <lcpainter.h>

GradientBackground::GradientBackground(const QColor& topColor, const QColor& bottomColor) : LCVDrawItem(false), _topColor(topColor), _bottomColor(bottomColor) {
}

GradientBackground::~GradientBackground() {
    qDebug() << "GradientBackground destroyed";
}

void GradientBackground::draw(LcPainter* _painter, LcDrawOptions* options, const QRectF& rect) const {
    unsigned long patId = _painter->pattern_create_linear(0.0,  rect.topLeft().y(),  0.0, rect.bottomRight().y());
    _painter->pattern_add_color_stop_rgba(patId, 1., _bottomColor.redF(), _bottomColor.greenF(), _bottomColor.blueF(), _bottomColor.alphaF());
    _painter->pattern_add_color_stop_rgba(patId, 0., _topColor.redF(), _topColor.greenF(), _topColor.blueF(), _topColor.alphaF());
    _painter->rectangle(rect.topLeft().x(), rect.topLeft().y(), rect.bottomRight().x(), rect.bottomRight().y());
    _painter->set_source(patId);
    _painter->fill();
    _painter->pattern_destroy(patId);
}
