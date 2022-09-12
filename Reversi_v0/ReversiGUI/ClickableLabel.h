#pragma once
#include <qlabel.h>
#include <qwidget.h>
#include <Qt>
#include <QMouseEvent>
#include "ReversiCore/Size.h"

/// @brief class for a label that can utilize clicks
class ClickableLabel : public QLabel
{
	Q_OBJECT

public:
	/// @brief constructor for clickable label
	ClickableLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

	/// @brief overrides mousePressEvent function
	void mousePressEvent(QMouseEvent* event);

signals:
	/// @brief is emitted when the left side of the mouse is clicked
	void clickedLeft();
};
