////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           Library/Core/FileSystem/Path.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

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

        boost::filesystem::path path_ ;

                                Impl                                        (   const   boost::filesystem::path&    aPath                                       ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Path::Impl::Impl                            (   const   boost::filesystem::path&    aPath                                       )
                                :   path_(aPath)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Path::Path                                  (   const   Path&                       aPath                                       )
                                :   implUPtr_((aPath.implUPtr_ != nullptr) ? std::make_unique<Path::Impl>(*aPath.implUPtr_) : nullptr)
{

}

                                Path::~Path                                 ( )
{

}

Path&                           Path::operator =                            (   const   Path&                       aPath                                       )
{

    if (this != &aPath)
    {
        implUPtr_.reset((aPath.implUPtr_ != nullptr) ? new Path::Impl(*aPath.implUPtr_) : nullptr) ;
    }

    return *this ;

}

bool                            Path::operator ==                           (   const   Path&                       aPath                                       ) const
{

    if ((!this->isDefined()) || (!aPath.isDefined()))
    {
        return false ;
    }

    return implUPtr_->path_ == aPath.implUPtr_->path_ ;

}

bool                            Path::operator !=                           (   const   Path&                       aPath                                       ) const
{
    return !((*this) == aPath) ;
}

Path                            Path::operator +                            (   const   Path&                       aPath                                       ) const
{

    Path path = { *this } ;

    path += aPath ;

    return path ;

}

Path&                           Path::operator +=                           (   const   Path&                       aPath                                       )
{

    if (!aPath.isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }

    try
    {
        implUPtr_->path_ /= aPath.implUPtr_->path_ ;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw library::core::error::RuntimeError(e.what()) ;
    }

    return *this ;

}

std::ostream&                   operator <<                                 (            std::ostream&              anOutputStream,
                                                                                const    Path&                      aPath                                       )
{

    library::core::utils::Print::Header(anOutputStream, "Path") ;

    library::core::utils::Print::Line(anOutputStream)                           << (aPath.isDefined() ? aPath.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Path::isDefined                             ( ) const
{
    return implUPtr_ != nullptr ;
}

bool                            Path::isAbsolute                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }

    return implUPtr_->path_.is_absolute() ;

}

bool                            Path::isRelative                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }

    return implUPtr_->path_.is_relative() ;

}

Path                            Path::getParentPath                         ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }

    Path path ;

    try
    {
        path.implUPtr_ = std::make_unique<Path::Impl>(implUPtr_->path_.parent_path()) ;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw library::core::error::RuntimeError(e.what()) ;
    }

    return path ;

}

String                          Path::getLastElement                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }

    try
    {
        return implUPtr_->path_.filename().string() ;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw library::core::error::RuntimeError(e.what()) ;
    }

    return String::Empty() ;

}

Path                            Path::getNormalizedPath                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }

    Path path ;

    try
    {
        path.implUPtr_ = std::make_unique<Path::Impl>(boost::filesystem::weakly_canonical(implUPtr_->path_)) ;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw library::core::error::RuntimeError(e.what()) ;
    }

    return path ;

}

Path                            Path::getAbsolutePath                       (   const   Path&                       aBasePath                                   ) const
{

    if (!aBasePath.isDefined())
    {
        throw library::core::error::runtime::Undefined("Base path") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }

    Path path ;

    try
    {
        path.implUPtr_ = std::make_unique<Path::Impl>(boost::filesystem::absolute(implUPtr_->path_, aBasePath.implUPtr_->path_)) ;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw library::core::error::RuntimeError(e.what()) ;
    }

    return path ;

}

// Path                            Path::getRelativePathTo                     (   const   Path&                       aReferencePath                              ) const
// {

// }

String                          Path::toString                              ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }

    try
    {
        return implUPtr_->path_.string() ;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw library::core::error::RuntimeError(e.what()) ;
    }

    return String::Empty() ;

}

Path                            Path::Undefined                             ( )
{
    return {} ;
}

Path                            Path::Root                                  ( )
{

    Path path ;

    path.implUPtr_ = std::make_unique<Path::Impl>("/") ;

    return path ;

}

Path                            Path::Current                               ( )
{

    Path path ;

    try
    {
        path.implUPtr_ = std::make_unique<Path::Impl>(boost::filesystem::current_path()) ;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw library::core::error::RuntimeError(e.what()) ;
    }

    return path ;

}

Path                            Path::Parse                                 (   const   String&                     aString                                     )
{

    if (aString.isEmpty())
    {
        throw library::core::error::runtime::Undefined("String") ;
    }

    Path path ;

    path.implUPtr_ = std::make_unique<Path::Impl>(aString) ;

    return path ;

}

// Path                            Path::Strings                               (   const   std::initializer_list<types::String> aStringList                        )
// {

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Path::Path                                  ( )
                                :   implUPtr_(nullptr)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
