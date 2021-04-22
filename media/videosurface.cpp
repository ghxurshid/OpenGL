#include "videosurface.h"
#include <QDebug>

VideoSurface::VideoSurface()
{
    qDebug() << Q_FUNC_INFO;
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    qDebug() << Q_FUNC_INFO;
    return true;
}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{
    qDebug() << Q_FUNC_INFO;
    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_YUYV;
}
