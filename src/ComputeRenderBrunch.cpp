#include "ComputeRenderBrunch.h"

#include <Qt3DRender/QDispatchCompute>
#include <Qt3DRender/QBufferCapture>
//#include <Qt3DRender/QMemoryBarrier>

ComputeRenderBrunch::ComputeRenderBrunch(Qt3DCore::QNode* parent):
    Qt3DRender::QRenderPassFilter(parent),
    m_dispatchCompute(new Qt3DRender::QDispatchCompute(this)),
    m_bufferCapture(new Qt3DRender::QBufferCapture(m_dispatchCompute))
{
//    Qt3DRender::QMemoryBarrier *barrier = new Qt3DRender::QMemoryBarrier(m_bufferCapture);
//    barrier->setWaitOperations(Qt3DRender::QMemoryBarrier::All);
    m_dispatchCompute->setWorkGroupX(1);
    m_dispatchCompute->setWorkGroupX(1);
    m_dispatchCompute->setWorkGroupX(1);
}
