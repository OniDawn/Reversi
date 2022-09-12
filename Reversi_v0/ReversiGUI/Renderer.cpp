#include "Renderer.h"
#include <QPainter>

Renderer::Renderer(Array2D board, Size size) :
	m_array(board), m_size(size), m_fieldSystem(FieldSystem(board, size))
{

}

QImage Renderer::calculateBoardImage()
{
	QImage image = QImage(m_size.width, m_size.height, QImage::Format_RGB32);
	image.fill("lightGray");
	QPainter painter(&image);
	QPen pen(Qt::white);
	pen.setWidth(2);
	painter.setPen(pen);

	for (int i = 0; i < m_array.getSize().height; i++)
	{
		for (int j = 0; j < m_array.getSize().width; j++)
		{
			QRectF rectangle(2 + (j * 100), 2 + (i * 100), 96, 96);
			painter.drawRect(rectangle);
		}
	}
	return image;
}

QImage Renderer::updateBoard(Array2D board, QImage image)
{
	m_array = board;
	QPainter painter(&image);
	QPen pen(Qt::white);
	pen.setWidth(2);
	painter.setPen(pen);

	for (int i = 0; i < board.getSize().height; i++)
	{
		for (int j = 0; j < m_array.getSize().width; j++)
		{
			if (board.getValue(Field(j, i)) == 1)
			{
				painter.setBrush(QColor(255, 0, 0, 127));
				QRectF rectangle(10 + (j * 100), 10 + (i * 100), 80, 80);
				painter.drawEllipse(rectangle);
			}
			else if (board.getValue(Field(j, i)) == 2)
			{
				painter.setBrush(QColor(0, 255, 0, 127));
				QRectF rectangle(10 + (j * 100), 10 + (i * 100), 80, 80);
				painter.drawEllipse(rectangle);
			}
		}
	}
	return image;
}

QImage Renderer::updateLabelWhosNext(int player)
{
	QImage littleImage = QImage(50, 50, QImage::Format_RGB32);
	littleImage.fill("lightGray");
	QPainter painter(&littleImage);
	QPen pen(Qt::white);
	pen.setWidth(2);
	painter.setPen(pen);

	if (player == 2)
	{
		painter.setBrush(QColor(255, 0, 0, 127));
	}
	else if (player == 1)
	{
		painter.setBrush(QColor(0, 255, 0, 127));
	}
	
	QRectF rectangle(10, 10, 30, 30);
	painter.drawEllipse(rectangle);

	return littleImage;
}

QImage Renderer::calculateScoreLabel(int player)
{
	QImage littleImage = QImage(25, 25, QImage::Format_RGB32);
	littleImage.fill("lightGray");
	QPainter painter(&littleImage);
	QPen pen(Qt::white);
	pen.setWidth(2);
	painter.setPen(pen);

	if (player == 1)
	{
		painter.setBrush(QColor(255, 0, 0, 127));
	}
	else if (player == 2)
	{
		painter.setBrush(QColor(0, 255, 0, 127));
	}

	QRectF rectangle(5, 5, 15, 15);
	painter.drawEllipse(rectangle);

	return littleImage;
}
