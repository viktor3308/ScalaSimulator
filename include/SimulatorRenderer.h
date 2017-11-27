#ifndef SIMULATORRENDERER_H
#define SIMULATORRENDERER_H

#include <Qt3DRender/QViewport>
#include <Qt3DRender/QBuffer>

class RayCastBuffer;
class ComputeRenderBrunch;

class QWindow;

namespace Qt3DRender
{
    class QRenderSurfaceSelector;
    class QRenderPassFilter;
    class QFilterKey;
    class QRenderTargetSelector;
    class QClearBuffers;
    class QCameraSelector;
    class QNoDraw;
}

class SimulatorRenderer: public Qt3DRender::QViewport
{
    Q_OBJECT
public:
    explicit SimulatorRenderer(Qt3DCore::QNode *parent = 0);

    void setSceneCamera(Qt3DCore::QEntity *camera);
    void setRayCamera(Qt3DCore::QEntity *camera);
    void setSurface(QWindow* surface);
    void setRayCastPassCriteria(QList<Qt3DRender::QFilterKey*> criteria);
    void setRenderPassCriteria(QList<Qt3DRender::QFilterKey*> criteria);
    void setComputePassCriteria(QList<Qt3DRender::QFilterKey*> criteria);

    template<typename PointerToMemberFunction>
    void connectToComputeBufferChanged(const typename QtPrivate::FunctionPointer<PointerToMemberFunction>::Object* receiver, PointerToMemberFunction method)
    {
        connect(m_computeBuffer, &Qt3DRender::QBuffer::dataChanged, receiver, method);
    }

private:
    Qt3DRender::QRenderSurfaceSelector *m_surfaceSelector;
    Qt3DRender::QCameraSelector *m_rayCastCameraSelector;
    Qt3DRender::QRenderPassFilter *m_rayCastPassFilter;
    Qt3DRender::QRenderTargetSelector *m_rayCastBufferTargetSelector;
    Qt3DRender::QClearBuffers *m_clearRayCastBuffer;

    ComputeRenderBrunch *m_computeRenderBrunch;

    Qt3DRender::QRenderPassFilter *m_renderPassFilter;
    Qt3DRender::QClearBuffers *m_clearRender;
    Qt3DRender::QCameraSelector *m_renderCameraSelector;

    RayCastBuffer *m_rayCastBuffer;
    QWindow *m_window;
    Qt3DRender::QBuffer *m_computeBuffer;
};

#endif // SIMULATORRENDERER_H
