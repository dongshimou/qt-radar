#ifndef QRADAR_H
#define QRADAR_H

#include <QChartView>
#include <QPolarChart>
#include <QLineSeries>
#include <QCategoryAxis>
#include <QAreaSeries>
#include <QScatterSeries>
#include <QDebug>
#include <QGraphicsLayout>
class QRadarImpl;
class QRadarChart : public QtCharts::QChartView
{
Q_OBJECT
    Q_PROPERTY(QBrush backgroundBrush READ backgroundBrush WRITE setBackgroundBrush)
public:
    explicit QRadarChart(QWidget *parent = 0);
    virtual ~QRadarChart();
    void setRange(qreal t_min, qreal t_max) const;
    void addStat(const QString&t_label,qreal t_value) const;
    void drawChart();
    void configAreaColor(
        QColor drawAreaColor = Qt::yellow,
        QColor baseAreaColor = Qt::yellow,
        QColor drawLineColor = Qt::transparent,
        QColor baseLineColor = Qt::transparent
    );
    void configAxisColor(
        QColor axisGridLineColor = Qt::transparent,
        QColor axisSideLineColor = Qt::transparent,
        QColor radialLineColor = Qt::transparent,
        QColor radiusLineColor = Qt::transparent
    );
    QtCharts::QCategoryAxis* getAngularAxis()const;
    QtCharts::QValueAxis* getRadialAxis()const;
    QtCharts::QLineSeries* getBaseLineSeries()const;
    QtCharts::QLineSeries* getDrawLineSeries()const;
    QtCharts::QAreaSeries* getBaseAreaSeries()const;
    QtCharts::QAreaSeries* getDrawAreaSeries()const;
    QtCharts::QLineSeries* getCenterSeries()const;
//    QChart *chart() const;
protected:
    QRadarImpl *m_impl;
//    继承于QChartView的常用的重载函数,更多详情查看父类
//    void resizeEvent(QResizeEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // QRADAR_H
