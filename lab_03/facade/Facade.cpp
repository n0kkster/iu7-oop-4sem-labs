#include "Facade.h"

void Facade::execute(const std::shared_ptr<BaseCommand> &command)
{
    command->execute();
}
