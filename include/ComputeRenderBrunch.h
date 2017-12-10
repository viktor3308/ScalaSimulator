#ifndef COMPUTERENDERBRUNCH_H
#define COMPUTERENDERBRUNCH_H

#include <Qt3DRender/QRenderPassFilter>

namespace Qt3DRender
{
    class QDispatchCompute;
    class QBufferCapture;
}

/*!
 * \brief Ветвь визуализатора для запуска compute шейдера
 */
class ComputeRenderBrunch: public Qt3DRender::QRenderPassFilter
{
public:
    explicit ComputeRenderBrunch(Qt3DCore::QNode *parent = nullptr);

private:
    Qt3DRender::QDispatchCompute* m_dispatchCompute;
    Qt3DRender::QBufferCapture* m_bufferCapture;
};

#endif // COMPUTERENDERBRUNCH_H
