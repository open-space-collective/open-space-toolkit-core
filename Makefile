################################################################################################################################################################

# @project        Library ▸ Core
# @file           Makefile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

export project_name := library-core
export project_version := $(shell git describe --tags --always)
export project_directory := $(shell git rev-parse --show-toplevel)

export docker_registry_path := openspacecollective
export docker_image_repository := $(docker_registry_path)/$(project_name)
export docker_image_version := $(project_version)

export development_base_image_version := 0.1.10

export ci_build_number := $(TRAVIS_BUILD_NUMBER)
export ci_commit := $(TRAVIS_COMMIT)
export ci_doc_repo_name := $(project_name)
export ci_doc_repo_token := $(GITHUB_API_KEY)
export ci_doc_repo_ref := github.com/open-space-collective/$(ci_doc_repo_name).git
export ci_doc_repo_user_name := "Travis CI"
export ci_doc_repo_user_email := "travis@travis-ci.org"
export ci_codecov_token := $(CODECOV_TOKEN)

################################################################################################################################################################

build: build-images

build-images:

	@ echo "Building images..."

	@ make build-development-images
	@ make build-release-images

build-development-images:

	@ echo "Building development images..."

	@ make build-development-image-debian
	@ make build-development-image-fedora

build-development-image-debian: target := debian
build-development-image-fedora: target := fedora

build-development-image-debian build-development-image-fedora: _build-development-image

_build-development-image:

	@ echo "Building [$(target)] development image..."

	docker build \
	--file="$(project_directory)/docker/development/$(target)/Dockerfile" \
	--tag=$(docker_image_repository)-development:$(docker_image_version)-$(target) \
	--tag=$(docker_image_repository)-development:latest-$(target) \
	--build-arg="BASE_IMAGE_VERSION=$(development_base_image_version)" \
	--build-arg="VERSION=$(docker_image_version)" \
	"$(project_directory)"

build-release-images:

	@ echo "Building release images..."

	@ make build-release-image-cpp-debian
	@ make build-release-image-cpp-fedora

	@ make build-release-image-python-debian
	@ make build-release-image-python-fedora

build-release-image-cpp-debian: target := debian
build-release-image-cpp-fedora: target := fedora

build-release-image-cpp-debian build-release-image-cpp-fedora: _build-release-image-cpp

_build-release-image-cpp:

	@ echo "Building [$(target)] C++ release image..."

	docker build \
	--file="$(project_directory)/docker/release/$(target)/Dockerfile" \
	--tag=$(docker_image_repository):$(docker_image_version)-$(target) \
	--tag=$(docker_image_repository):latest-$(target) \
	--build-arg="VERSION=$(docker_image_version)" \
	--target=cpp-release \
	"$(project_directory)"

build-release-image-python-debian: target := debian
build-release-image-python-fedora: target := fedora

build-release-image-python-debian build-release-image-python-fedora: _build-release-image-python

_build-release-image-python:

	@ echo "Building [$(target)] Python release image..."

	docker build \
	--file="$(project_directory)/docker/release/$(target)/Dockerfile" \
	--tag=$(docker_image_repository)-python:$(docker_image_version)-$(target) \
	--tag=$(docker_image_repository)-python:latest-$(target) \
	--build-arg="VERSION=$(docker_image_version)" \
	--target=python-release \
	"$(project_directory)"

build-documentation: target := debian

build-documentation: _build-development-image

	@ echo "Building [$(target)] documentation..."

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(target) \
	/bin/bash -c "cmake -DBUILD_DOCUMENTATION=ON .. && make docs"

build-packages:

	@ echo "Building packages..."

	@ make build-packages-cpp
	@ make build-packages-python

build-packages-cpp:

	@ echo "Building C++ packages..."

	@ make build-packages-cpp-debian
	@ make build-packages-cpp-fedora

build-packages-cpp-debian: target := debian
build-packages-cpp-fedora: target := fedora

build-packages-cpp-debian: package_generator := DEB
build-packages-cpp-fedora: package_generator := RPM

build-packages-cpp-debian: package_extension := deb
build-packages-cpp-fedora: package_extension := rpm

build-packages-cpp-debian build-packages-cpp-fedora: _build-packages-cpp

_build-packages-cpp: _build-development-image

	@ echo "Building [$(target)] C++ packages..."

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(target) \
	/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF -DBUILD_PYTHON_BINDINGS=OFF -DCPACK_GENERATOR=$(package_generator) .. && make package && mkdir -p /app/packages/cpp && mv /app/build/*.$(package_extension) /app/packages/cpp"

build-packages-python:

	@ echo "Building Python packages..."

	@ make build-packages-python-debian

build-packages-python-debian: target := debian
build-packages-python-fedora: target := fedora

build-packages-python-debian build-packages-python-fedora: _build-packages-python

_build-packages-python: _build-development-image

	@ echo "Building [$(target)] Python packages..."

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(target) \
	/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF -DBUILD_PYTHON_BINDINGS=ON .. && make -j && mkdir -p /app/packages/python && mv /app/build/bindings/python/dist/*.whl /app/packages/python"

################################################################################################################################################################

run-development:

	@ echo "Running development environment..."

	make run-development-debian

run-development-debian: target := debian
run-development-fedora: target := fedora

run-development-debian run-development-fedora: _run-development

_run-development: _build-development-image

	@ echo "Running [$(target)] development environment..."

	docker run \
	-it \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="${project_directory}/tools/development/helpers:/app/build/helpers:ro,delegated" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(target) \
	/bin/bash

run-python: run-python-debian

run-python-debian: target := debian
run-python-fedora: target := fedora

run-python-debian run-python-fedora: _run-python

_run-python: _build-release-image-python

	@ echo "Running [$(target)] Python runtime environment..."

	docker run \
	-it \
	--rm \
	$(docker_image_repository)-python:$(docker_image_version)-$(target)

################################################################################################################################################################

debug-development:

	@ echo "Debugging development environment..."

	make debug-development-debian

debug-development-debian: target := debian
debug-development-fedora: target := fedora

debug-development-debian debug-development-fedora: _debug-development

_debug-development: _build-development-image

	@ echo "Debugging [$(target)] development environment..."

	docker run \
	-it \
	--rm \
	$(docker_image_repository)-development:$(docker_image_version)-$(target) \
	/bin/bash

debug-cpp-release-debian: target := debian
debug-cpp-release-fedora: target := fedora

debug-cpp-release-debian debug-cpp-release-fedora: _debug-cpp-release

_debug-cpp-release: _build-release-image-cpp

	@ echo "Debugging [$(target)] C++ release environment..."

	docker run \
	-it \
	--rm \
	--entrypoint=/bin/bash \
	$(docker_image_repository):$(docker_image_version)-$(target)

debug-python-release-debian: target := debian
debug-python-release-fedora: target := fedora

debug-python-release-debian debug-python-release-fedora: _debug-python-release

_debug-python-release: _build-release-image-python

	@ echo "Debugging [$(target)] Python release environment..."

	docker run \
	-it \
	--rm \
	--entrypoint=/bin/bash \
	$(docker_image_repository)-python:$(docker_image_version)-$(target)

################################################################################################################################################################

test:

	@ echo "Running tests..."

	@ make test-unit
	@ make test-coverage

test-unit:

	@ echo "Running unit tests..."

	@ make test-unit-debian

test-unit-debian:

	@ echo "Running [debian] unit tests..."

	@ make test-unit-cpp-debian
	@ make test-unit-python-debian

test-unit-fedora:

	@ echo "Running [fedora] unit tests..."

	@ make test-unit-cpp-fedora
	@ make test-unit-python-fedora

test-unit-cpp-debian: target := debian
test-unit-cpp-fedora: target := fedora

test-unit-cpp-debian test-unit-cpp-fedora: _test-unit-cpp

_test-unit-cpp: _build-development-image

	@ echo "Running [$(target)] C++ unit tests..."

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(target) \
	/bin/bash -c "cmake -DBUILD_UNIT_TESTS=ON .. && make -j && make test"

test-unit-python-debian: target := debian
test-unit-python-fedora: target := fedora

test-unit-python-debian test-unit-python-fedora: _test-unit-python

_test-unit-python: _build-release-image-python

	@ echo "Running [$(target)] Python unit tests..."

	docker run \
	--rm \
	--workdir=/usr/local/lib/python3.7/site-packages/Library/Core \
	--entrypoint="" \
	$(docker_image_repository)-python:$(docker_image_version)-$(target) \
	/bin/bash -c "pip install pytest && pytest ."

test-coverage:

	@ echo "Running coverage tests..."

	@ make test-coverage-cpp

test-coverage-cpp:

	@ echo "Running C++ coverage tests..."

	@ make test-coverage-cpp-debian

test-coverage-cpp-debian: target := debian
test-coverage-cpp-fedora: target := fedora

test-coverage-cpp-debian test-coverage-cpp-fedora: _test-coverage-cpp

_test-coverage-cpp: _build-development-image

	@ echo "Running [$(target)] C++ coverage tests..."

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(target) \
	/bin/bash -c "cmake -DBUILD_CODE_COVERAGE=ON .. && make -j && make coverage && mkdir -p /app/coverage && mv /app/build/coverage* /app/coverage"

################################################################################################################################################################

deploy:

	@ echo "Deploying..."

	@ make deploy-coverage-cpp-results
	@ make deploy-packages
	@ make deploy-documentation

deploy-packages:

	@ echo "Deploying packages..."

	@ make deploy-packages-debian
	@ make deploy-packages-fedora

deploy-packages-debian: target := debian
deploy-packages-fedora: target := fedora

deploy-packages-debian deploy-packages-fedora: _deploy_packages

_deploy_packages:

	@ echo "Deploying [$(target)] packages..."

	@ make _deploy-packages-cpp target=$(target)
	@ make _deploy-packages-python target=$(target)

deploy-packages-cpp:

	@ echo "Deploying C++ packages..."

	@ make _deploy-packages-cpp target=debian
	@ make _deploy-packages-cpp target=fedora

_deploy-packages-cpp: _build-packages-cpp

	@ echo "Deploying [$(target)] C++ packages..."

	@ echo "TBI"

deploy-packages-python:

	@ echo "Deploying Python packages..."

	@ make deploy-packages-python-debian

_deploy-packages-python: _build-packages-python

	@ echo "Deploying [$(target)] Python packages..."

	docker run \
	--rm \
	--volume="$(project_directory)/packages/python:/packages:ro" \
	--env="TWINE_USERNAME=${PYPI_USERNAME}" \
	--env="TWINE_PASSWORD=${PYPI_PASSWORD}" \
	python:3.7-slim \
	/bin/bash -c "pip install twine && python3 -m twine upload /packages"

deploy-coverage-cpp-results: target := debian

deploy-coverage-cpp-results: _test-coverage-cpp

	@ echo "Deploying C++ coverage results..."

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--workdir=/app \
	$(docker_image_repository)-development:$(docker_image_version)-$(target) \
	/bin/bash -c "bash <(curl -s https://codecov.io/bash) -X gcov -y .codecov.yml -t ${ci_codecov_token}"

deploy-documentation: build-documentation

	@ echo "Deploying documentation..."

	$(shell \
		project_directory=$(project_directory) \
		ci_doc_repo_ref=$(ci_doc_repo_ref) \
		ci_doc_repo_name=$(ci_doc_repo_name) \
		ci_doc_repo_user_name=$(ci_doc_repo_user_name) \
		ci_doc_repo_user_email=$(ci_doc_repo_user_email) \
		ci_doc_repo_token=$(ci_doc_repo_token) \
		ci_build_number=$(ci_build_number) \
		ci_commit=$(ci_commit) \
		./tools/ci/deploy-documentation.sh)

################################################################################################################################################################

clean:

	@ echo "Cleaning up..."

	rm -r "$(project_directory)/build" || true
	rm -r "$(project_directory)/bin/"*.test* || true
	rm -r "$(project_directory)/docs/html" || true
	rm -r "$(project_directory)/docs/latex" || true
	rm -r "$(project_directory)/lib/"*.so* || true
	rm -r "$(project_directory)/coverage" || true
	rm -r "$(project_directory)/packages" || true

################################################################################################################################################################

.PHONY: build build-images \
		build-development-images build-development-image-debian build-development-image-fedora \
		build-release-image-cpp-debian build-release-image-python-debian build-release-image-python-fedora \
		build-documentation \
		build-packages-cpp build-packages-cpp-debian build-packages-cpp-fedora \
		run-development run-development-debian run-development-fedora \
		run-python run-python-debian run-python-fedora \
		debug-development-debian debug-cpp-release-debian debug-python-release-debian \
		debug-development-fedora debug-cpp-release-fedora debug-python-release-fedora \
		test \
		test-unit test-unit-debian test-unit-fedora \
		test-unit-cpp-debian test-unit-cpp-fedora \
		test-unit-python-debian test-unit-python-fedora \
		test-coverage \
		test-coverage-cpp \
		test-coverage-cpp-debian test-coverage-cpp-fedora \
		deploy deploy-packages deploy-coverage-cpp-results deploy-documentation \
		deploy-packages-cpp deploy-packages-python \
		clean

################################################################################################################################################################
