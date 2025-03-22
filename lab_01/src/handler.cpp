#include "handler.h"
#include "wireframe.h"
#include "errors.h"

err_code_e handleAction(/* VAR */ plane_t &plane, const action_params_t &action)
{
    static wireframe_t wireframe = initWireframe();
    err_code_e rc = ERROR_SUCCESS;

    switch (action.action)
    {
        case LOAD:
            rc = handleRead(wireframe, action.io_params);
            break;
        case SAVE:
            rc = handleWrite(action.io_params, wireframe);
            break;
        case MOVE:
            rc = handleShiftWireframe(wireframe, action.shift_params);                    
            break;
        case SCALE:
            rc = handleScaleWireframe(wireframe, action.scale_params);
            break;
        case ROTATE:
            rc = handleRotateWireframe(wireframe, action.rotation_params);
            break;
        case DRAW:
            rc = handleDraw(plane, wireframe);
            break;
        case FREE:
            rc = freeWireframe(wireframe);
            break;
        default:
            rc = ERROR_INVALID_ACTION;
            break;
    }

    return rc;
}
