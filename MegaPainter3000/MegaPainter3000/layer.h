#ifndef LAYER_H
#define LAYER_H

#include <QImage>
#include <QColor>
#include <QRgb>
#include <QDataStream>
#include <QPainter>

class Layer : public QImage
{
public:
    Layer();
    Layer(const QSize &size, Format format);
    Layer(int width, int height, Format format);
  //  Layer(uchar *data, int width, int height, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR);
  //  Layer(const uchar *data, int width, int height, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR);
  //  Layer(uchar *data, int width, int height, int bytesPerLine, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR);
  //  Layer(const uchar *data, int width, int height, int bytesPerLine, Format format, QImageCleanupFunction cleanupFunction = Q_NULLPTR, void *cleanupInfo = Q_NULLPTR);
    //Layer(const char * const[] xpm);
    //Layer(const QString &fileName, const char *format = Q_NULLPTR);
    Layer(const QImage &image);
    //Layer(QImage &&other);

    //Layer operator+(Layer B);
    static QImage SubLayer(int w, int h);
    void setVisible(bool vis);
    void setBackground(QRgb pixel);
    bool getVisible();
    //QRgb getBackground();
    void setOpacity (double dOpacity);
    friend QDataStream &operator>>(QDataStream &in, Layer l);
    friend QDataStream &operator <<(QDataStream &out, Layer l);
    friend class plane;
    double dOpacity;
    void DrawOnLayer(Layer* layer);
    void claer();
private:
    bool visible;
    QRgb background;

};

#endif // LAYER_H
