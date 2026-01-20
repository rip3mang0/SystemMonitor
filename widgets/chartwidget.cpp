#include "chartwidget.h"
#include <QPainter>

ChartWidget::ChartWidget(const QString &title, QWidget *parent)
    : QWidget{parent}
    , m_title(title)
    , m_maxDataPoints(60)
    , m_minY(0.0)
    , m_maxY(100.0)
    , m_lineColor(QColor("#2196F3"))
{
    m_dataPoints.fill(0.0, m_maxDataPoints);
    m_fillColor = m_lineColor;
    m_fillColor.setAlpha(80);
    setMinimumHeight(250);
}

void ChartWidget::addDataPoint(double value)
{
    for (int i = 0; i < m_dataPoints.size() - 1; ++i) {
        m_dataPoints[i] = m_dataPoints[i + 1];
    }
    if (!m_dataPoints.isEmpty()) {
        m_dataPoints.last() = value;
    }
    update();
}

void ChartWidget::setColor(const QColor &color)
{
    m_lineColor = color;
    m_fillColor = color;
    m_fillColor.setAlpha(80);
    update();
}

void ChartWidget::setYAxisRange(double min, double max)
{
    m_minY = min;
    m_maxY = max;
    update();
}

void ChartWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // Calculate drawing area
    const int chartWidth = width() - MARGIN_LEFT - MARGIN_RIGHT;
    const int chartHeight = height() - MARGIN_TOP - MARGIN_BOTTOM;
    if (chartWidth <= 0 || chartHeight <= 0) {
        return; // Widget too small
    }
    const QRect chartRect(MARGIN_LEFT, MARGIN_TOP, chartWidth, chartHeight);
    // Setup theme colors
    QPalette pal = palette();
    const bool isDark = (pal.color(QPalette::Window).lightness() < 128);
    const QColor bgColor = isDark ? QColor("#2C2C2C") : Qt::white;
    const QColor chartBgColor = isDark ? QColor("#1E1E1E") : QColor("#FAFAFA");
    const QColor gridColor = isDark ? QColor("#404040") : QColor("#D0D0D0");
    const QColor textColor = isDark ? QColor("#E0E0E0") : QColor("#424242");
    const QColor labelColor = isDark ? QColor("#B0B0B0") : QColor("#757575");
    const QColor borderColor = isDark ? QColor("#606060") : QColor("#BDBDBD");
    // Draw background
    painter.fillRect(rect(), bgColor);
}

void ChartWidget::clear()
{
    m_dataPoints.fill(0.0, m_maxDataPoints);
    update();
}

QSize ChartWidget::sizeHint() const
{
    return QSize(600, 300);
}

QSize ChartWidget::minimumSizeHint() const
{
    return QSize(300, 200);
}

