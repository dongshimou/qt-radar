#include "qradar.h"

class QRadarImpl
{
private:
    struct angular
    {
        QString label;
        qreal value;
    };
    QVector<angular>m_Angulars;
    //chart
    QtCharts::QPolarChart m_chart;

    //series
    QtCharts::QLineSeries m_center;
    QtCharts::QLineSeries m_baseLine;
    QtCharts::QLineSeries m_drawLine;
    QtCharts::QAreaSeries m_baseArea;
    QtCharts::QAreaSeries m_drawArea;

    //axis
    QtCharts::QCategoryAxis m_angularAxis;
    QtCharts::QValueAxis m_radialAxis;

    qreal m_radialMin = 0;
    qreal m_radialMax = 100;

    QColor m_baseAreaColor = QColor(102, 204, 255, 102);
    QColor m_drawAreaColor = QColor(102, 204, 255, 153);

    QColor m_baseLineColor = Qt::transparent;
    QColor m_drawLineColor = Qt::transparent;

    QColor m_angularGridLineColor = Qt::transparent;
    QColor m_angularSideLineColor = Qt::transparent;

    QColor m_radialLineColor = Qt::transparent;
    QColor m_radiusLineColor = Qt::transparent;

    const qreal m_angularMin = 0;
    const qreal m_angularMax = 360;
public:
    QRadarImpl();
    QtCharts::QCategoryAxis& getAngularAxis();
    QtCharts::QValueAxis& getRadialAxis();
    QtCharts::QLineSeries& getCenterSeries();
    QtCharts::QLineSeries& getBaseLineSeries();
    QtCharts::QLineSeries& getDrawLineSeries();
    QtCharts::QAreaSeries& getBaseAreaSeries();
    QtCharts::QAreaSeries& getDrawAreaSeries();
    QtCharts::QPolarChart& getChart();
    void configAreaColor(
        QColor baseAreaColor,
        QColor drawAreaColor,
        QColor baseLineColor,
        QColor drawLineColor
    );
    void configAxisColor(
        QColor axisGridLineColor,
        QColor axisSideLineColor,
        QColor radialLineColor,
        QColor radiusLineColor
    );
    void initChart();
    void setRange(qreal t_min, qreal t_max);
    void addAngular(const QString&t_label, qreal t_value);
};

inline QtCharts::QCategoryAxis& QRadarImpl::getAngularAxis()
{
    return m_angularAxis;
}

inline QtCharts::QValueAxis& QRadarImpl::getRadialAxis()
{
    return m_radialAxis;
}

inline QtCharts::QLineSeries& QRadarImpl::getCenterSeries()
{
    return m_center;
}

inline QtCharts::QLineSeries& QRadarImpl::getBaseLineSeries()
{
    return m_baseLine;
}

inline QtCharts::QLineSeries& QRadarImpl::getDrawLineSeries()
{
    return m_drawLine;
}

inline QtCharts::QAreaSeries& QRadarImpl::getBaseAreaSeries()
{
    return m_baseArea;
}

inline QtCharts::QAreaSeries& QRadarImpl::getDrawAreaSeries()
{
    return m_drawArea;
}

inline QtCharts::QPolarChart& QRadarImpl::getChart()
{
    return m_chart;
}

inline void QRadarImpl::configAreaColor(
    QColor baseAreaColor,
    QColor drawAreaColor,
    QColor baseLineColor,
    QColor drawLineColor
)
{
    m_baseAreaColor = baseAreaColor;
    m_drawAreaColor = drawAreaColor;
    m_baseLineColor = baseLineColor;
    m_drawLineColor = drawLineColor;
}

inline void QRadarImpl::configAxisColor(
    QColor axisGridLineColor,
    QColor axisSideLineColor,
    QColor radialLineColor,
    QColor radiusLineColor
)
{
    m_angularGridLineColor = axisGridLineColor;
    m_angularSideLineColor = axisSideLineColor;
    m_radialLineColor = radialLineColor;
    m_radiusLineColor = radiusLineColor;
}

QRadarImpl::QRadarImpl()
{
    m_center.append(m_angularMin, m_radialMin);
    m_center.setBrush(Qt::NoBrush);
    m_center.setPen(Qt::NoPen);
    m_center.setPointLabelsVisible();
    m_center.setPointLabelsColor(Qt::red);
    QFont font { QLatin1String { "Microsoft YaHei" }, 32 };
    m_center.setPointLabelsFont(font);
    m_center.setPointLabelsFormat(QLatin1String { "@yPoint" });
    m_baseArea.setLowerSeries(&m_center);
    m_baseArea.setUpperSeries(&m_baseLine);
    m_drawArea.setLowerSeries(&m_center);
    m_drawArea.setUpperSeries(&m_drawLine);
}

void QRadarImpl::initChart()
{
    const auto count = m_Angulars.length();
    const auto offset = ( m_angularMax - m_angularMin ) / count;
    for (auto i = 0; i <= count; i++)
    {
        m_baseLine.append(m_angularMin + offset * i, m_radialMax);
    }
    for (auto i = 0; i < count; i++)
    {
        m_drawLine.append(
            m_angularMin + offset * i,
            m_radialMin + m_Angulars[i].value
        );
    }
    if (m_Angulars.size())
    {
        m_drawLine.append(
            m_angularMin + offset * count,
            m_radialMin + m_Angulars[0].value
        );
    }
    m_chart.addSeries(&m_center);
    m_chart.addSeries(&m_baseLine);
    m_chart.addSeries(&m_drawLine);
    m_chart.addSeries(&m_baseArea);
    m_chart.addSeries(&m_drawArea);
    //绘图区颜色
    m_baseArea.setColor(m_baseAreaColor);
    //表述区颜色
    m_drawArea.setColor(m_drawAreaColor);
    //内层线的颜色
    m_drawLine.setBrush(Qt::NoBrush);
    m_drawLine.setPen(Qt::NoPen);
    m_drawArea.setBorderColor(m_drawLineColor);
    //外层线的颜色
    m_baseLine.setBrush(Qt::NoBrush);
    m_baseLine.setPen(Qt::NoPen);
    m_baseArea.setBorderColor(m_baseLineColor);
    // 中心到各点的直线的颜色
    m_angularAxis.setGridLineColor(m_angularGridLineColor);
    // 外层圆弧不可见(设置为透明)
    m_angularAxis.setLinePenColor(m_angularSideLineColor);
    // 外层圆弧不可见(隐藏)
    //    m_angularAxis.setLineVisible(false);
    //    m_angularAxis.setShadesVisible(false);
    m_angularAxis.setRange(m_angularMin, m_angularMax);
    m_angularAxis.setStartValue(m_angularMin);
    m_angularAxis.setLabelsPosition(
        QtCharts::QCategoryAxis::AxisLabelsPositionOnValue);
    for (auto i = 0; i < count; i++)
    {
        m_angularAxis.append(m_Angulars[i].label, m_angularMin + offset * i);
    }
    m_chart.addAxis(&m_angularAxis, QtCharts::QPolarChart::PolarOrientationAngular);
    // 放射圈的颜色
    m_radialAxis.setGridLineColor(m_radialLineColor);
    // 半径轴的颜色
    m_radialAxis.setLinePenColor(m_radiusLineColor);
    m_radialAxis.setRange(m_radialMin, m_radialMax);
    m_chart.addAxis(&m_radialAxis, QtCharts::QPolarChart::PolarOrientationRadial);
    m_center.attachAxis(&m_radialAxis);
    m_center.attachAxis(&m_angularAxis);
    m_baseLine.attachAxis(&m_radialAxis);
    m_baseLine.attachAxis(&m_angularAxis);
    m_baseArea.attachAxis(&m_radialAxis);
    m_baseArea.attachAxis(&m_angularAxis);
    m_drawLine.attachAxis(&m_radialAxis);
    m_drawLine.attachAxis(&m_angularAxis);
    m_drawArea.attachAxis(&m_radialAxis);
    m_drawArea.attachAxis(&m_angularAxis);
}

inline void QRadarImpl::setRange(qreal t_min, qreal t_max)
{
    m_radialMin = t_min;
    m_radialMax = t_max;
}

inline void QRadarImpl::addAngular(const QString& t_label, qreal t_value)
{
    m_Angulars.append({ t_label, t_value });
}

void QRadarChart::setRange(qreal t_min, qreal t_max) const
{
    m_impl->setRange(t_min, t_max);
}

void QRadarChart::addStat(const QString& t_label, qreal t_value) const
{
    m_impl->addAngular(
        t_label,
        t_value
    );
}

void QRadarChart::drawChart()
{
    m_impl->initChart();
    auto old = this->chart();
    this->setChart(&m_impl->getChart());
    delete old;
    this->chart()->legend()->hide();
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void QRadarChart::configAreaColor(
    QColor drawAreaColor,
    QColor baseAreaColor,
    QColor drawLineColor,
    QColor baseLineColor
)
{
    m_impl->configAreaColor(
        drawAreaColor,
        baseAreaColor,
        drawLineColor,
        baseLineColor
    );
}

void QRadarChart::configAxisColor(
    QColor axisGridLineColor,
    QColor axisSideLineColor,
    QColor radialLineColor,
    QColor radiusLineColor
)
{
    m_impl->configAxisColor(
        axisGridLineColor,
        axisSideLineColor,
        radialLineColor,
        radiusLineColor
    );
}

QtCharts::QCategoryAxis* QRadarChart::getAngularAxis() const
{
    return &m_impl->getAngularAxis();
}

QtCharts::QValueAxis* QRadarChart::getRadialAxis() const
{
    return  &m_impl->getRadialAxis();
}

QtCharts::QLineSeries* QRadarChart::getBaseLineSeries() const
{
    return &m_impl->getBaseLineSeries();
}

QtCharts::QLineSeries* QRadarChart::getDrawLineSeries() const
{
    return &m_impl->getDrawLineSeries();
}

QtCharts::QAreaSeries* QRadarChart::getBaseAreaSeries() const
{
    return &m_impl->getBaseAreaSeries();
}

QtCharts::QAreaSeries* QRadarChart::getDrawAreaSeries() const
{
    return &m_impl->getDrawAreaSeries();
}

QtCharts::QLineSeries* QRadarChart::getCenterSeries() const
{
    return &m_impl->getCenterSeries();
}

QRadarChart::QRadarChart(QWidget *parent)
    : QChartView(parent)
{
    m_impl = new QRadarImpl;
}
QRadarChart::~QRadarChart()
{
    delete m_impl;
}

