#include "RayCastBuffer.h"

#include <Qt3DRender/QAbstractTexture>
#include <Qt3DRender/QRenderTargetOutput>
#include <Qt3DRender/qtexture.h>

RayCastBuffer::RayCastBuffer(Qt3DCore::QNode* parent):
    Qt3DRender::QRenderTarget(parent)
{
    const Qt3DRender::QAbstractTexture::TextureFormat formats[AttachmentsCount] =
    {
        Qt3DRender::QAbstractTexture::RGB32F,
        Qt3DRender::QAbstractTexture::RGB32F,
        Qt3DRender::QAbstractTexture::RGB32F,
        Qt3DRender::QAbstractTexture::RGB32F,
        Qt3DRender::QAbstractTexture::D32F
    };

    const Qt3DRender::QRenderTargetOutput::AttachmentPoint attachmentPoints[AttachmentsCount] =
    {
        Qt3DRender::QRenderTargetOutput::Color0,
        Qt3DRender::QRenderTargetOutput::Color1,
        Qt3DRender::QRenderTargetOutput::Color2,
        Qt3DRender::QRenderTargetOutput::Color3,
        Qt3DRender::QRenderTargetOutput::Depth
    };

    for (int i = 0; i < AttachmentsCount; ++i)
    {
        Qt3DRender::QRenderTargetOutput *output = new Qt3DRender::QRenderTargetOutput(this);

        m_textures[i] = new Qt3DRender::QTexture2D();
        m_textures[i]->setFormat(formats[i]);
        m_textures[i]->setWidth(1);
        m_textures[i]->setHeight(1);
        m_textures[i]->setGenerateMipMaps(false);
        m_textures[i]->setWrapMode(Qt3DRender::QTextureWrapMode(Qt3DRender::QTextureWrapMode::ClampToEdge));
        m_textures[i]->setMinificationFilter(Qt3DRender::QAbstractTexture::Nearest);
        m_textures[i]->setMagnificationFilter(Qt3DRender::QAbstractTexture::Nearest);

        output->setTexture(m_textures[i]);
        output->setAttachmentPoint(attachmentPoints[i]);
        addOutput(output);
    }
}

Qt3DRender::QAbstractTexture* RayCastBuffer::getTexture(Attachments attachment)
{
    Q_ASSERT(attachment < AttachmentsCount);

    return m_textures[static_cast<size_t>(attachment)];
}
