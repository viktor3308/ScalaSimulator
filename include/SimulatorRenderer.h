#ifndef SIMULATORRENDERER_H
#define SIMULATORRENDERER_H

#include <Qt3DRender/QViewport>

class RayCastBuffer;

class QWindow;

namespace Qt3DRender
{
    class QRenderSurfaceSelector;
    class QRenderPassFilter;
    class QFilterKey;
    class QRenderTargetSelector;
    class QClearBuffers;
    class QCameraSelector;
}

class SimulatorRenderer: public Qt3DRender::QViewport
{
public:
    explicit SimulatorRenderer(Qt3DCore::QNode *parent = 0);

    void setSceneCamera(Qt3DCore::QEntity *camera);
    void setSurface(QWindow* surface);
    void setRayCastPassCriteria(QList<Qt3DRender::QFilterKey*> criteria);
    void setRenderPassCriteria(QList<Qt3DRender::QFilterKey*> criteria);

private:
    Qt3DRender::QRenderSurfaceSelector *m_surfaceSelector;
    Qt3DRender::QRenderPassFilter *m_rayCastPassFilter;
    Qt3DRender::QRenderTargetSelector *m_rayCastBufferTargetSelector;
    Qt3DRender::QClearBuffers *m_clearRayCastBuffer;
    Qt3DRender::QCameraSelector *m_rayCastCameraSelector;

    Qt3DRender::QRenderPassFilter *m_renderPassFilter;
    Qt3DRender::QClearBuffers *m_clearRender;
    Qt3DRender::QCameraSelector *m_renderCameraSelector;

    RayCastBuffer *m_rayCastBuffer;
    QWindow *m_window;


//    QMetaObject::Connection m_widthChangedConnection;
    //    QMetaObject::Connection m_heightChangedConnection;
};

#endif // SIMULATORRENDERER_H
