#ifndef BASE_VISITOR_CREATOR
#define BASE_VISITOR_CREATOR

#include "../BaseVisitor.h"

#include <memory>

template <typename Visitor, typename... Args>
class BaseVisitorCreator
{
public:
    BaseVisitorCreator() = default;
    virtual ~BaseVisitorCreator() = default;

    virtual std::shared_ptr<Visitor> create(Args &&...args) = 0;

};

#endif
