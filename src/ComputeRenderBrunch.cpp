#include "ComputeRenderBrunch.h"

#include <Qt3DRender/QDispatchCompute>
#include <Qt3DRender/QBufferCapture>

ComputeRenderBrunch::ComputeRenderBrunch(Qt3DCore::QNode* parent):
    Qt3DRender::QRenderPassFilter(parent),
    m_dispatchCompute(new Qt3DRender::QDispatchCompute(this)),
    m_bufferCapture(new Qt3DRender::QBufferCapture(m_dispatchCompute))
{
    m_dispatchCompute->setWorkGroupX(1);
    m_dispatchCompute->setWorkGroupX(1);
    m_dispatchCompute->setWorkGroupX(1);
}
