#include "SimulatorRenderer.h"
#include "RayCastBuffer.h"
#include "ComputeRenderBrunch.h"

#include <Qt3DRender/QRenderSurfaceSelector>
#include <Qt3DRender/QRenderPassFilter>
#include <Qt3DRender/QRenderTargetSelector>
#include <Qt3DRender/QClearBuffers>
#include <Qt3DRender/QCameraSelector>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QBuffer>
#include <QWindow>
#include <QVector3D>
#include <QVector4D>

SimulatorRenderer::SimulatorRenderer(Qt3DCore::QNode* parent):
    Qt3DRender::QViewport(parent),
    m_surfaceSelector(new Qt3DRender::QRenderSurfaceSelector(this)),
    m_rayCastPassFilter(new Qt3DRender::QRenderPassFilter(m_surfaceSelector)),
    m_rayCastBufferTargetSelector(new Qt3DRender::QRenderTargetSelector(m_rayCastPassFilter)),
    m_clearRayCastBuffer(new Qt3DRender::QClearBuffers(m_rayCastBufferTargetSelector)),
    m_rayCastCameraSelector(new Qt3DRender::QCameraSelector(m_clearRayCastBuffer)),

    m_computeRenderBrunch(new ComputeRenderBrunch(m_surfaceSelector)),

    m_renderPassFilter(new Qt3DRender::QRenderPassFilter(m_surfaceSelector)),
    m_clearRender(new Qt3DRender::QClearBuffers(m_renderPassFilter)),
    m_renderCameraSelector(new Qt3DRender::QCameraSelector(m_clearRender)),

    m_rayCastBuffer(new RayCastBuffer(this)),
    m_window(nullptr),
    m_computeBuffer(new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, this))
{
    m_rayCastBufferTargetSelector->setTarget(m_rayCastBuffer);
    m_clearRayCastBuffer->setBuffers(Qt3DRender::QClearBuffers::ColorDepthBuffer);

    m_clearRender->setBuffers(Qt3DRender::QClearBuffers::ColorDepthBuffer);

    m_computeBuffer->setAccessType(Qt3DRender::QBuffer::ReadWrite);

    QByteArray bufferDataArray;
    bufferDataArray.resize(4 * sizeof(QVector4D));
    QVector4D *posData = reinterpret_cast<QVector4D *>(bufferDataArray.data());
    for (int j = 0; j < 4; ++j) {
        *posData = QVector4D(0,0,0,0);
        qDebug() << "X: " << (*posData).x() << " Y: " << (*posData).y()  << " Z: " << (*posData).z();
        ++posData;
    }
    m_computeBuffer->setData(bufferDataArray);

    m_computeRenderBrunch->addParameter(new Qt3DRender::QParameter(QStringLiteral("point0"), m_rayCastBuffer->getTexture(RayCastBuffer::Point0)));
    m_computeRenderBrunch->addParameter(new Qt3DRender::QParameter(QStringLiteral("point1"), m_rayCastBuffer->getTexture(RayCastBuffer::Point1)));
    m_computeRenderBrunch->addParameter(new Qt3DRender::QParameter(QStringLiteral("point2"), m_rayCastBuffer->getTexture(RayCastBuffer::Point2)));
    m_computeRenderBrunch->addParameter(new Qt3DRender::QParameter(QStringLiteral("intersection"), m_rayCastBuffer->getTexture(RayCastBuffer::IntersectionPoint)));
    m_computeRenderBrunch->addParameter(new Qt3DRender::QParameter(QStringLiteral("outBuffer"), QVariant::fromValue(m_computeBuffer)));

    m_renderPassFilter->addParameter(new Qt3DRender::QParameter(QStringLiteral("point0"), m_rayCastBuffer->getTexture(RayCastBuffer::Point0)));
    m_renderPassFilter->addParameter(new Qt3DRender::QParameter(QStringLiteral("point1"), m_rayCastBuffer->getTexture(RayCastBuffer::Point1)));
    m_renderPassFilter->addParameter(new Qt3DRender::QParameter(QStringLiteral("point2"), m_rayCastBuffer->getTexture(RayCastBuffer::Point2)));
    m_renderPassFilter->addParameter(new Qt3DRender::QParameter(QStringLiteral("intersection"), m_rayCastBuffer->getTexture(RayCastBuffer::IntersectionPoint)));
}

void SimulatorRenderer::setSceneCamera(Qt3DCore::QEntity* camera)
{
    m_renderCameraSelector->setCamera(camera);
}

void SimulatorRenderer::setRayCamera(Qt3DCore::QEntity* camera)
{
    m_rayCastCameraSelector->setCamera(camera);
}

void SimulatorRenderer::setSurface(QWindow* surface)
{
    if (surface != m_window)
    {
        m_window = surface;
        m_surfaceSelector->setSurface(surface);
    }
}

void SimulatorRenderer::setRayCastPassCriteria(QList<Qt3DRender::QFilterKey*> criteria)
{
    Q_FOREACH(Qt3DRender::QFilterKey* filterKey, criteria)
        m_rayCastPassFilter->addMatch(filterKey);
}

void SimulatorRenderer::setRenderPassCriteria(QList<Qt3DRender::QFilterKey*> criteria)
{
    Q_FOREACH(Qt3DRender::QFilterKey* filterKey, criteria)
        m_renderPassFilter->addMatch(filterKey);
}

void SimulatorRenderer::setComputePassCriteria(QList<Qt3DRender::QFilterKey*> criteria)
{
    Q_FOREACH(Qt3DRender::QFilterKey* filterKey, criteria)
        m_computeRenderBrunch->addMatch(filterKey);
}
