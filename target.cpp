#include <target.hpp>

target::target(target::type t): 
    m_type(t)
{

}

target::~target()
{
    
}

target::type target::get_type() const
{
    return m_type;
}
