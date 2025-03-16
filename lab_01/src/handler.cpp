#include "handler.h"
#include "wireframe.h"
#include "errors.h"

// static err_code_e morphWireframe(/* VAR */ wireframe_t &wireframe, /* VAR */ projection_t &projection, const morph_params_t &morphParams)
// {
//     wireframe_t temp_wireframe;

//     err_code_e rc = deepCopyWireframe(temp_wireframe, wireframe);

//     if (rc == ERROR_SUCCESS)
//     {
//         switch (morphParams.type)
//         {
//             case MOVE:
//                 rc = handleShiftWireframe(temp_wireframe, morphParams.shift_params);                    
//                 break;
//             case SCALE:
//                 rc = handleScaleWireframe(temp_wireframe, morphParams.scale_params);
//                 break;
//             case ROTATE:
//                 rc = handleRotateWireframe(temp_wireframe, morphParams.rotation_params);
//                 break;
//         }
        
//         if (rc != ERROR_SUCCESS)
//             freeWireframe(temp_wireframe);
//         else
//         {
//             rc = updateProjection(projection, temp_wireframe);
//             if (rc != ERROR_SUCCESS)
//                 freeWireframe(temp_wireframe);
//             else
//                 moveWireframe(wireframe, temp_wireframe);
//         }
//     }

//     return rc;
// }

err_code_e handleAction(plane_t &plane, const action_params_t &action)
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
            freeWireframe(wireframe);
        default:
            break;
    }

    return rc;
}
