#include "SimulatorSceneEntity.h"
#include "ScalaMoveController.h"
#include "SimulatorRenderer.h"
#include "RayCastEffect.h"
#include "ComputeEntity.h"
#include "ComputeEffect.h"
#include "ScalaEntity.h"

#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QRenderSettings>

int main(int ac, char **av)
{
    QGuiApplication app(ac, av);

    Qt3DExtras::Qt3DWindow view;

    Qt3DCore::QEntity *sceneRoot = new Qt3DCore::QEntity();

    Qt3DRender::QCamera *camera = view.camera();

    ScalaEntity *scalaEntity = new ScalaEntity(sceneRoot);

    ScalaMoveController *scalaController = new ScalaMoveController(scalaEntity, sceneRoot);
    scalaController->setCamera(camera);

    SimulatorSceneEntity *scene = new SimulatorSceneEntity(sceneRoot);
    RayCastEffect *rayCastEffect = scene->effect();

    ComputeEntity *computeEntity = new ComputeEntity(sceneRoot);
    ComputeEffect *computeEffect = computeEntity->effect();

    SimulatorRenderer *renderer = new SimulatorRenderer();
    renderer->setNormalizedRect(QRectF(0.0f, 0.0f, 1.0f, 1.0f));
    renderer->setRayCastPassCriteria(rayCastEffect->rayCastPassCriteria());
    renderer->setRenderPassCriteria(rayCastEffect->renderPassCriteria());
    renderer->setComputePassCriteria(computeEffect->computePassCriteria());
    renderer->setSceneCamera(camera);
    renderer->setRayCamera(scalaEntity->rayCamera());
    renderer->setSurface(&view);
    renderer->connectToComputeBufferChanged(scalaEntity, &ScalaEntity::onComputeBufferChanged);

    view.setActiveFrameGraph(renderer);
    //view.renderSettings()->setRenderPolicy(Qt3DRender::QRenderSettings::Always);

    view.setRootEntity(sceneRoot);
    view.show();

    return app.exec();
}
