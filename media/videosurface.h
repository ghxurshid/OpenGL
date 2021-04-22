#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>

class VideoSurface : public QAbstractVideoSurface
{
public:
    VideoSurface();

    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const;

    virtual bool present(const QVideoFrame &frame);
};

#endif // VIDEOSURFACE_H
