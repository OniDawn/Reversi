#include "ClickableLabel.h"
#include <Qt>
#include <QDialog>
#include <QDebug>

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f) :
	QLabel(parent)
{
	
}


void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit clickedLeft();
		event->accept();
	}
}