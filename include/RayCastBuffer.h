#ifndef RAYCASTBUFFER_H
#define RAYCASTBUFFER_H

#include <Qt3DRender/QRenderTarget>

namespace Qt3DRender
{
    class QAbstractTexture;
}

class RayCastBuffer: public Qt3DRender::QRenderTarget
{
public:
    explicit RayCastBuffer(Qt3DCore::QNode *parent = 0);

    enum Attachments
    {
        Point0 = 0,
        Point1,
        Point2,
        IntersectionPoint,
        RayOriginPoint,
        Depth,
        AttachmentsCount
    };

    Qt3DRender::QAbstractTexture* getTexture(Attachments attachment);

private:
    Qt3DRender::QAbstractTexture *m_textures[AttachmentsCount];
};

#endif // RAYCASTBUFFER_H
