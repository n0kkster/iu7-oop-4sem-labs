#include "handler.h"
#include "wireframe.h"
#include "errors.h"

static err_code_e morphWireframe(/* VAR */ wireframe_t &wireframe, /* VAR */ projection_t &projection, const morph_params_t &morphParams)
{
    err_code_e rc = ERROR_SUCCESS;
    switch (morphParams.type)
    {
        case MOVE:
            rc = handleShiftWireframe(wireframe, morphParams);
            break;
        case SCALE:
            rc = handleScaleWireframe(wireframe, morphParams);
            break;
        case ROTATE:
            rc = handleRotateWireframe(wireframe, morphParams);
            break;
    }
    
    if (rc == ERROR_SUCCESS)
        updateProjection(projection, wireframe);

    return rc;
}

err_code_e handleAction(/* VAR */ projection_t &projection, const action_params_t &action)
{
    static wireframe_t wireframe = initWireframe();
    err_code_e rc = ERROR_SUCCESS;

    switch (action.action)
    {
        case INIT:
            rc = initProjection(projection);
            break;
        case LOAD:
            rc = handleRead(wireframe, action.io_params);
            if (rc == ERROR_SUCCESS)
                rc = createProjection(projection, wireframe);
            break;
        case SAVE:
            rc = handleWrite(action.io_params, wireframe);
            break;
        case MORPH:
            rc = morphWireframe(wireframe, projection, action.morph_params);
            break;
        case FREE:
            freeWireframe(wireframe);
            freeProjection(projection);
        default:
            break;
    }

    return rc;
}
