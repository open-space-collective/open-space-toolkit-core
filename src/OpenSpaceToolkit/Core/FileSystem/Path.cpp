/// Apache License 2.0

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

namespace ostk
{
namespace core
{
namespace filesystem
{

class Path::Impl
{
   public:
    boost::filesystem::path path_;

    Impl(const boost::filesystem::path& aPath);
};

Path::Impl::Impl(const boost::filesystem::path& aPath)
    : path_(aPath)
{
}

Path::Path(const Path& aPath)
    : implUPtr_(std::make_unique<Path::Impl>(*aPath.implUPtr_))
{
}

Path::~Path() {}

Path& Path::operator=(const Path& aPath)
{
    if (this != &aPath)
    {
        implUPtr_ = std::make_unique<Path::Impl>(*aPath.implUPtr_);
    }

    return *this;
}

bool Path::operator==(const Path& aPath) const
{
    return implUPtr_->path_ == aPath.implUPtr_->path_;
}

bool Path::operator!=(const Path& aPath) const
{
    return !((*this) == aPath);
}

Path Path::operator+(const Path& aPath) const
{
    Path path = {*this};

    path += aPath;

    return path;
}

Path& Path::operator+=(const Path& aPath)
{
    try
    {
        implUPtr_->path_ /= aPath.implUPtr_->path_;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }

    return *this;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Path& aPath)
{
    ostk::core::utils::Print::Header(anOutputStream, "Path");

    ostk::core::utils::Print::Line(anOutputStream) << aPath.toString();

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Path::isAbsolute() const
{
    return implUPtr_->path_.is_absolute();
}

bool Path::isRelative() const
{
    return implUPtr_->path_.is_relative();
}

Path Path::getParentPath() const
{
    try
    {
        return Path(std::make_unique<Path::Impl>(implUPtr_->path_.parent_path()));
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }
}

String Path::getLastElement() const
{
    try
    {
        return implUPtr_->path_.filename().string();
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }

    return String::Empty();
}

Path Path::getNormalizedPath() const
{
    try
    {
        return Path(std::make_unique<Path::Impl>(boost::filesystem::weakly_canonical(implUPtr_->path_)));
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }
}

Path Path::getAbsolutePath(const Path& aBasePath) const
{
    try
    {
        return Path(
            std::make_unique<Path::Impl>(boost::filesystem::absolute(implUPtr_->path_, aBasePath.implUPtr_->path_))
        );
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }
}

// Path                            Path::getRelativePathTo                     (   const   Path& aReferencePath ) const
// {

// }

String Path::toString() const
{
    try
    {
        return implUPtr_->path_.string();
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }

    return String::Empty();
}

Path Path::Root()
{
    return Path(std::make_unique<Path::Impl>("/"));
}

Path Path::Current()
{
    try
    {
        return Path(std::make_unique<Path::Impl>(boost::filesystem::current_path()));
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }
}

Path Path::Parse(const String& aString)
{
    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    return Path(std::make_unique<Path::Impl>(aString));
}

// Path                            Path::Strings                               (   const
// std::initializer_list<type::String> aStringList                        )
// {

// }

Path::Path(Unique<Path::Impl> anImplUPtr)
    : implUPtr_(std::move(anImplUPtr))
{
}

}  // namespace filesystem
}  // namespace core
}  // namespace ostk
