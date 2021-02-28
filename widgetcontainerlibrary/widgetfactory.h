#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

#include <memory>
#include <stdexcept>
#include <map>

namespace utils {

template <typename key, typename base, typename... params>
class factory
{
public:
    using base_ptr = std::shared_ptr<base> ;

    template <typename derived>
    void reg( const key &name )
    {
        factories[ name ] = std::shared_ptr<base_type>( new derived_type<derived> );
    }

    base_ptr create( const key& name, params... p )
    {
        if( !factories.empty() && !factories.count( name ) )
            throw std::out_of_range( "factory: key not found" );
        return factories[ name ]->create( p... );
    }

private:

    class base_type
    {
    public:
        virtual ~base_type() {}
        virtual base_ptr create( params... ) const = 0;
    };

    template <class T>
    class derived_type : public base_type
    {
    public:
        virtual base_ptr create( params... p ) const
        {
            return base_ptr( new T( p... ) );
        }
    };

    std::map<key, std::shared_ptr<base_type>> factories;
};

}

#endif // WIDGETFACTORY_H
