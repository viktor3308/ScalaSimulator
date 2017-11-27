#ifndef SCALAENTITY_H
#define SCALAENTITY_H

#include <Qt3DCore/QEntity>
#include <QVector3D>

namespace Qt3DCore
{
    class QTransform;
}

namespace Qt3DRender
{
    class QCamera;
}

class ScalaEntity: public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    explicit ScalaEntity(QNode* parent = nullptr);

    void setViewCamera(Qt3DRender::QCamera* camera);
    Qt3DRender::QCamera* rayCamera() const;
    void move(float distance);
    void rotate(float angle);

public slots:
    void onComputeBufferChanged(const QByteArray &bytes);

private:
    void updateGeometry();

    Qt3DRender::QCamera* m_viewCamera;
    Qt3DRender::QCamera* m_rayCamera;
    Qt3DCore::QEntity* m_scalaBox;
    Qt3DCore::QTransform* m_scalaBoxTransform;

    QVector3D m_origin;
    QVector3D m_forwardVector;
    QVector3D m_lastIntersection;
    QVector3D m_viewRelativePosition;
};

#endif // SCALAENTITY_H
