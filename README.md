# qt-radar
a small and simple qt radar chart

```
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
// drawChart之后设置 chart() 的background
w.chart()->setBackgroundBrush(Qt::transparent);
// 隐藏中心数字
w.getCenterSeries()->hide();
w.show();
```

on windows

![demo](https://cloud.githubusercontent.com/assets/9100799/26811316/9d2b80c6-4aa3-11e7-8326-fc36c02706da.jpg)