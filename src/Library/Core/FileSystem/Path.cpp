////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/FileSystem/Path.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace fs
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Path::Impl
{

    public:

                                Impl                                        (   const   boost::filesystem::path&    aPath                                       ) ;

        boost::filesystem::path path_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Path::Impl::Impl                            (   const   boost::filesystem::path&    aPath                                       )
                                :   path_(aPath)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Path::Path                                  (   const   Path&                       aPath                                       )
                                :   impl_((aPath.impl_ != nullptr) ? std::make_unique<Path::Impl>(*aPath.impl_) : nullptr)
{
    
}

                                Path::~Path                                 ( )
{

}

Path&                           Path::operator =                            (   const   Path&                       aPath                                       )
{

    if (this != &aPath)
    {
        impl_.reset((aPath.impl_ != nullptr) ? new Path::Impl(*aPath.impl_) : nullptr) ;   
    }

    return *this ;

}

bool                            Path::operator ==                           (   const   Path&                       aPath                                       ) const
{

    if ((!this->isDefined()) || (!aPath.isDefined()))
    {
        return false ;
    }

    return impl_->path_ == aPath.impl_->path_ ;

}

bool                            Path::operator !=                           (   const   Path&                       aPath                                       ) const
{
    return !((*this) == aPath) ;
}

// Path                            Path::operator +                            (   const   Path&                       aPath                                       ) const
// {

// }

// Path&                           Path::operator +=                           (   const   Path&                       aPath                                       )
// {

// }

std::ostream&                   operator <<                                 (            std::ostream&              anOutputStream,
                                                                                const    Path&                      aPath                                       )
{

    library::core::utils::Print::Header(anOutputStream, "Path") ;

    library::core::utils::Print::Line(anOutputStream) << (aPath.isDefined() ? aPath.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Path::isDefined                             ( ) const
{
    return impl_ != nullptr ;
}

// bool                            Path::isAbsolute                            ( ) const
// {

// }

// bool                            Path::isRelative                            ( ) const
// {

// }

// String                          Path::getFirstElement                       ( ) const
// {

// }

// String                          Path::getLastElement                        ( ) const
// {

// }

// Path                            Path::getNormalizedPath                     ( ) const
// {

// }

// Path                            Path::getAbsolutePath                       ( ) const
// {

// }

// Path                            Path::getRelativePathTo                     (   const   Path&                       aReferencePath                              ) const
// {

// }

String                          Path::toString                              ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }
    
    return impl_->path_.string() ;

}

Path                            Path::Undefined                             ( )
{
    return Path() ;
}

Path                            Path::Root                                  ( )
{
    
    Path path ;

    path.impl_ = std::make_unique<Path::Impl>("/") ;

    return path ;

}

Path                            Path::Parse                                 (   const   String&                     aString                                     )
{

    if (aString.isEmpty())
    {
        throw library::core::error::runtime::Undefined("String") ;
    }

    Path path ;

    path.impl_ = std::make_unique<Path::Impl>(aString) ;

    return path ;

}

// Path                            Path::Strings                               (   const   std::initializer_list<types::String> aStringList                        )
// {

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Path::Path                                  ( )
                                :   impl_(nullptr)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////