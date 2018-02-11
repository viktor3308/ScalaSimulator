#include "ComputeRenderBrunch.h"

#include <Qt3DRender/QDispatchCompute>
#include <Qt3DRender/QBufferCapture>
#include <Qt3DRender/QMemoryBarrier>

#include <Qt3DRender/QNoDraw>

ComputeRenderBrunch::ComputeRenderBrunch(Qt3DCore::QNode* parent):
    Qt3DRender::QRenderPassFilter(parent),
    m_dispatchCompute(new Qt3DRender::QDispatchCompute(this)),
    m_bufferCapture(new Qt3DRender::QBufferCapture(m_dispatchCompute))
{
    //Qt3DRender::QMemoryBarrier *barrier = new Qt3DRender::QMemoryBarrier(m_dispatchCompute);
    //barrier->setWaitOperations(Qt3DRender::QMemoryBarrier::All);
    m_dispatchCompute->setWorkGroupX(1);
    m_dispatchCompute->setWorkGroupX(1);
    m_dispatchCompute->setWorkGroupX(1);

    //m_bufferCapture = new Qt3DRender::QBufferCapture(barrier);

    //Qt3DRender::QNoDraw *noDraw = new Qt3DRender::QNoDraw(m_bufferCapture);
}
