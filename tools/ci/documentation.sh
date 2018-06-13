#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/ci/documentation.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

# https://gist.github.com/vidavidorra/548ffbcdae99d752da02

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

project_directory="${script_directory}/../.."
docker_directory="${script_directory}/../docker"

source "${docker_directory}/.env"

docker run \
--rm \
--volume="${project_directory}:/app:rw" \
--volume="/app/build" \
--workdir="/app/build" \
${image_name} \
/bin/bash -c "cmake -DBUILD_DOCUMENTATION=ON .. && make docs"

mkdir -p /docs

pushd /docs

GH_REPO_NAME="library-core"
GH_REPO_TOKEN="${GITHUB_API_KEY}"
GH_REPO_REF="github.com/open-space-collective/library-core.git"

git clone -b gh-pages https://git@${GH_REPO_REF}

pushd ${GH_REPO_NAME}

# Set the push default to simple i.e. push only the current branch.

git config --global push.default simple

# Pretend to be an user called Travis CI.

git config user.name "Travis CI"
git config user.email "travis@travis-ci.org"

rm -rf *

cp -r "${project_directory}"/docs/* .

# Need to create a .nojekyll file to allow filenames starting with an underscore
# to be seen on the gh-pages site. Therefore creating an empty .nojekyll file.
# Presumably this is only needed when the SHORT_NAMES option in Doxygen is set
# to NO, which it is by default. So creating the file just in case.

echo "" > .nojekyll

# Only upload if Doxygen successfully created the documentation.
# Check this by verifying that the html directory and the file html/index.html
# both exist. This is a good indication that Doxygen did its work.

if [ -d "html" ] && [ -f "html/index.html" ]; then

    echo 'Uploading documentation to the gh-pages branch...'

    # Add everything in this directory (the Doxygen code documentation) to the gh-pages branch.
    # GitHub is smart enough to know which files have changed and which files have
    # stayed the same and will only update the changed files.
    
    git add --all

    # Commit the added files with a title and description containing the Travis CI
    # build number and the GitHub commit reference that issued this build.
    
    git commit -m "Deploy code docs to GitHub Pages Travis build: ${TRAVIS_BUILD_NUMBER}" -m "Commit: ${TRAVIS_COMMIT}"

    # Force push to the remote gh-pages branch.
    # The ouput is redirected to /dev/null to hide any sensitive credential data that might otherwise be exposed.

    git push --force "https://${GH_REPO_TOKEN}@${GH_REPO_REF}" > /dev/null 2>&1

else
    
    echo '' >&2
    echo 'Warning: No documentation (html) files have been found!' >&2
    echo 'Warning: Not going to push the documentation to GitHub!' >&2
    exit 1

fi

popd

################################################################################################################################################################