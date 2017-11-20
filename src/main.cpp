#include "simulatorsceneentity.h"
#include "scalamovecontroller.h"
#include "SimulatorRenderer.h"
#include "RayCastEffect.h"

#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>

int main(int ac, char **av)
{
    QGuiApplication app(ac, av);

    Qt3DExtras::Qt3DWindow view;

    Qt3DCore::QEntity *sceneRoot = new Qt3DCore::QEntity();

    Qt3DRender::QCamera *camera = view.camera();
    camera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));
    camera->setPosition(QVector3D(0.0f, 0.0f, 5.0f));
    camera->setNearPlane(0.001f);
    camera->setFarPlane(10000.0f);

    ScalaMoveController *camController = new ScalaMoveController(sceneRoot);
    camController->setCamera(camera);

    SimulatorSceneEntity *scene = new SimulatorSceneEntity(sceneRoot);
    RayCastEffect *rayCastEffect = scene->effect();

    SimulatorRenderer *renderer = new SimulatorRenderer();
    renderer->setNormalizedRect(QRectF(0.0f, 0.0f, 1.0f, 1.0f));
    renderer->setRayCastPassCriteria(rayCastEffect->rayCastPassCriteria());
    renderer->setRenderPassCriteria(rayCastEffect->renderPassCriteria());
    renderer->setSceneCamera(camera);
    renderer->setSurface(&view);

    view.setActiveFrameGraph(renderer);

    view.setRootEntity(sceneRoot);
    view.show();

    return app.exec();
}
