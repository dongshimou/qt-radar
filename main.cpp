#include "qradar.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRadarChart w;

    w.addStat("one",90);
    w.addStat("two", 70);
    w.addStat("three", 50);
    w.addStat("four", 80);
    w.addStat("five", 45);
    w.configAxisColor(Qt::red);
    auto blue = QColor(66, 66, 255, 128);
    auto yellow = QColor(255, 255, 0, 128);
    w.configAreaColor(blue, yellow, Qt::red, Qt::red);
    w.getRadialAxis()->hide();
    w.drawChart();
    w.chart()->setBackgroundBrush(Qt::transparent);
    w.getCenterSeries()->hide();
    w.show();

    return a.exec();
}
