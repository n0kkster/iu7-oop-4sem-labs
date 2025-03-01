#include "handler.h"
#include "wireframe.h"
#include "errors.h"

err_code_e handleAction(const action_params_t &action)
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
        case DRAW:
            handleDraw(action.draw_params, wireframe);
            break;
        case SHIFT:
            handleShiftWireframe(wireframe, action.morph_params);
            break;
        case SCALE:
            handleScaleWireframe(wireframe, action.morph_params);
            break;
        case ROTATE:
            handleRotateWireframe(wireframe, action.morph_params);
            break;
        case FREE:
            freeWireframe(wireframe);
        default:
            break;
    }

    return rc;
}