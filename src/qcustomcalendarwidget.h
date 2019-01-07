#ifndef QCUSTOMCALENDARWIDGET_H
#define QCUSTOMCALENDARWIDGET_H

#include <QCalendarWidget>
#include <QCalendarWidget>
#include <QDateTimeEdit>


class QPushButton;
class QLabel;
class QCustomCalendarWidget : public QCalendarWidget
{
    Q_OBJECT

public:
    QCustomCalendarWidget(QWidget *parent);
    ~QCustomCalendarWidget();
    QWidget* bottomWidget;
    QPushButton* m_ensureBtn;

private:
    void initControl();
    void initTopWidget();
    void initBottomWidget();
    void setDataLabelTimeText(int year, int month);

signals:
    void signalSetCalendarTime(const QDate& data);
    void timeChanged(QTime);
private slots:
    void onbtnClicked();
    void onTimeChange(const QTime &time);
    void m_ensureBtn_slot();
protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

private:
    QPushButton* m_leftYearBtn;
    QPushButton* m_leftMonthBtn;

    QPushButton* m_rightYearBtn;
    QPushButton* m_rightMonthBtn;


    QPushButton* m_toDayBtn;

    QDateTimeEdit * DateEdit2;

    QLabel* m_dataLabel;

};
#endif
