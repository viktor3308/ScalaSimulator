#include "ScalaEntity.h"

#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DExtras/QCylinderGeometry>
#include <QColor>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QFilterKey>
#include <Qt3DExtras/QSphereGeometry>
#include <Qt3DExtras/QCuboidGeometry>
#include <QtMath>
#include <QQuaternion>

ScalaEntity::ScalaEntity(Qt3DCore::QNode* parent):
    Qt3DCore::QEntity(parent),
    m_rayCamera(new Qt3DRender::QCamera(this)),
    m_ray(new Qt3DCore::QEntity(this)),
    m_rayTransform(new Qt3DCore::QTransform(m_ray)),
    m_scalaBox(new Qt3DCore::QEntity(this)),
    m_scalaBoxTransform(new Qt3DCore::QTransform(m_scalaBox)),
    m_intersection(new Qt3DCore::QEntity(this)),
    m_intersectionTransform(new Qt3DCore::QTransform(m_intersection)),
    m_origin(0,0,3),
    m_forwardVector(0,0,-1),
    m_viewRelativePosition(0.0f, 2.0f, 5.0f)
{
    m_rayCamera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    m_rayCamera->setViewCenter(m_origin + m_forwardVector);
    m_rayCamera->setPosition(m_origin);
    m_rayCamera->setNearPlane(0.001f);
    m_rayCamera->setFarPlane(10000.0f);

    //ray
    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
    material->setAmbient(QColor(0,0,255));
    material->setDiffuse(QColor(0,0,255));

    Qt3DRender::QFilterKey* filterKey = new Qt3DRender::QFilterKey(this);
    filterKey->setName(QStringLiteral("pass"));
    filterKey->setValue(QStringLiteral("render"));

    Qt3DRender::QEffect* effect = material->effect();
    Q_FOREACH(Qt3DRender::QTechnique* technique, effect->techniques())
        Q_FOREACH(Qt3DRender::QRenderPass* renderPass, technique->renderPasses())
            renderPass->addFilterKey(filterKey);

    Qt3DRender::QGeometryRenderer *renderer = new Qt3DRender::QGeometryRenderer();
    Qt3DExtras::QCylinderGeometry *rayGeometry = new Qt3DExtras::QCylinderGeometry();
    rayGeometry->setRadius(0.01f);
    rayGeometry->setLength(1.0f);
    renderer->setGeometry(rayGeometry);

    m_ray->addComponent(renderer);
    m_ray->addComponent(m_rayTransform);
    m_ray->addComponent(material);

    //intersection
    {
        Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
        material->setAmbient(QColor(0,255,0));
        material->setDiffuse(QColor(0,255,0));

        Qt3DRender::QFilterKey* filterKey = new Qt3DRender::QFilterKey(this);
        filterKey->setName(QStringLiteral("pass"));
        filterKey->setValue(QStringLiteral("render"));

        Qt3DRender::QEffect* effect = material->effect();
        Q_FOREACH(Qt3DRender::QTechnique* technique, effect->techniques())
            Q_FOREACH(Qt3DRender::QRenderPass* renderPass, technique->renderPasses())
                renderPass->addFilterKey(filterKey);

        Qt3DRender::QGeometryRenderer *renderer = new Qt3DRender::QGeometryRenderer();
        Qt3DExtras::QSphereGeometry *intersectionGeometry = new Qt3DExtras::QSphereGeometry();
        intersectionGeometry->setRadius(0.02f);
        renderer->setGeometry(intersectionGeometry);
        m_intersection->addComponent(renderer);
        m_intersection->addComponent(m_intersectionTransform);
        m_intersection->addComponent(material);
    }

    //box
    {
        Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
        material->setAmbient(QColor(125,125,0));
        material->setDiffuse(QColor(125,125,0));

        Qt3DRender::QFilterKey* filterKey = new Qt3DRender::QFilterKey(this);
        filterKey->setName(QStringLiteral("pass"));
        filterKey->setValue(QStringLiteral("render"));

        Qt3DRender::QEffect* effect = material->effect();
        Q_FOREACH(Qt3DRender::QTechnique* technique, effect->techniques())
            Q_FOREACH(Qt3DRender::QRenderPass* renderPass, technique->renderPasses())
                renderPass->addFilterKey(filterKey);

        Qt3DRender::QGeometryRenderer *renderer = new Qt3DRender::QGeometryRenderer();
        Qt3DExtras::QCuboidGeometry *scalaBoxGeometry = new Qt3DExtras::QCuboidGeometry();
        scalaBoxGeometry->setXExtent(0.5f);
        scalaBoxGeometry->setYExtent(0.5f);
        scalaBoxGeometry->setZExtent(0.5f);
        renderer->setGeometry(scalaBoxGeometry);

        m_scalaBoxTransform->setTranslation(m_origin - (m_forwardVector * 0.25));

        m_scalaBox->addComponent(renderer);
        m_scalaBox->addComponent(m_scalaBoxTransform);
        m_scalaBox->addComponent(material);
    }
}

void ScalaEntity::setViewCamera(Qt3DRender::QCamera* camera)
{
    m_viewCamera = camera;
    m_viewCamera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    m_viewCamera->setViewCenter(m_origin + m_forwardVector);
    m_viewCamera->setPosition(m_origin + m_viewRelativePosition);
    m_viewCamera->setNearPlane(0.001f);
    m_viewCamera->setFarPlane(10000.0f);
}

Qt3DRender::QCamera*ScalaEntity::rayCamera() const
{
    return m_rayCamera;
}

void ScalaEntity::move(float distance)
{
    m_origin = m_origin + m_forwardVector * distance;
    m_rayCamera->translateWorld(m_forwardVector * distance);
    m_rayCamera->setViewCenter(m_origin + m_forwardVector);
    m_viewCamera->translateWorld(m_forwardVector * distance);

    updateGeometry();
}

void ScalaEntity::rotate(float angle)
{
    m_forwardVector = QQuaternion::fromAxisAndAngle(0, -1, 0, angle).rotatedVector(m_forwardVector).normalized();
    m_rayCamera->setViewCenter(m_origin + m_forwardVector);

    QVector3D rayVector = m_rayCamera->viewVector().normalized();
    QQuaternion viewRotation = QQuaternion::rotationTo(QVector3D(0, 0, -1), QVector3D(rayVector.x(), 0, rayVector.z()));
    m_viewCamera->setPosition(m_origin + viewRotation.rotatedVector(m_viewRelativePosition));
    m_viewCamera->setUpVector(QVector3D(0, 1, 0));

    updateGeometry();
}

void ScalaEntity::onComputeBufferChanged(const QByteArray& bytes)
{
    qDebug() << "Data received";
    const QVector4D *posData = reinterpret_cast<const QVector4D *>(bytes.data());
    for (int j = 0; j < 4; ++j)
        qDebug() << "X: " << posData[j].x() << " Y: " << posData[j].y()  << " Z: " << posData[j].z();

    m_lastIntersection = posData[3].toVector3D();

    updateGeometry();
}

void ScalaEntity::updateGeometry()
{
    QVector3D intersection = m_lastIntersection;
    if(intersection.isNull())
        intersection = m_origin + m_forwardVector * 100.0f;

    m_intersection->setEnabled(false);
    m_ray->setEnabled(false);

    m_intersectionTransform->setTranslation(intersection);

    QVector3D rayVector = m_rayCamera->viewVector().normalized();
    m_rayTransform->setRotation(QQuaternion::rotationTo(QVector3D(0, 1, 0), rayVector));
    m_rayTransform->setScale3D(QVector3D(1, m_rayCamera->position().distanceToPoint(intersection), 1));
    m_rayTransform->setTranslation((intersection - m_rayCamera->position()) * 0.5f + m_rayCamera->position());

    m_scalaBoxTransform->setRotation(QQuaternion::fromDirection(rayVector, m_rayCamera->upVector()));
    m_scalaBoxTransform->setTranslation(m_origin - (m_forwardVector * 0.25));

    m_intersection->setEnabled(true);
    m_ray->setEnabled(true);
}
