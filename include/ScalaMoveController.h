#ifndef SCALAMOVECONTROLLER_H
#define SCALAMOVECONTROLLER_H

#include <Qt3DExtras/qt3dextras_global.h>
#include <Qt3DCore/QEntity>

namespace Qt3DRender
{
    class QCamera;
}

namespace Qt3DLogic
{
    class QFrameAction;
}

namespace Qt3DInput
{
    class QKeyboardDevice;
    class QMouseDevice;
    class QLogicalDevice;
    class QAction;
    class QActionInput;
    class QAxis;
    class QAnalogAxisInput;
    class QButtonAxisInput;
    class QAxisActionHandler;
}

class ScalaEntity;

/*!
 * \brief Контроллер управления scala объектом сцены и камерой
 */
class ScalaMoveController: public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    ScalaMoveController(ScalaEntity* scala, Qt3DCore::QNode *parent = nullptr);

public slots:
    void onTriggered(float dt);
    void setCamera(Qt3DRender::QCamera *camera);

private:
    ScalaEntity *m_scala;
    Qt3DRender::QCamera *m_camera;

    Qt3DInput::QAxis *m_viewXAxis;
    Qt3DInput::QAxis *m_viewYAxis;
    Qt3DInput::QAxis *m_linearMoveAxis;
    Qt3DInput::QAxis *m_rotateAxis;

    Qt3DInput::QAnalogAxisInput *m_mouseXInput;
    Qt3DInput::QAnalogAxisInput *m_mouseYInput;
    Qt3DInput::QButtonAxisInput *m_keyboardForwardInput;
    Qt3DInput::QButtonAxisInput *m_keyboardBackwardInput;
    Qt3DInput::QButtonAxisInput *m_keyboardLeftInput;
    Qt3DInput::QButtonAxisInput *m_keyboardRightInput;

    Qt3DInput::QMouseDevice *m_mouseDevice;
    Qt3DInput::QKeyboardDevice *m_keyboardDevice;

    Qt3DInput::QLogicalDevice *m_logicalDevice;
    Qt3DLogic::QFrameAction *m_frameAction;

    float m_linearSpeed;
    float m_rotationSpeed;
    float m_lookSpeed;
};

#endif // SCALAMOVECONTROLLER_H
