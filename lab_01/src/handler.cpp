#include "handler.h"

err_code_e handleAction(const action_params_t &action)
{
    static wireframe_t wireframe = initWireframe();
    err_code_e rc = ERROR_SUCCESS;

    switch (action.action)
    {
        case LOAD:
            rc = handleReadFromFile(action.io_params, wireframe);
            break;
        case DRAW:
            rc = handleDraw(action.draw_params, wireframe);
        default:
            break;
    }
}