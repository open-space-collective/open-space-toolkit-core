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

build-images: build-development-images

build-development-images:

	make build-debian-development-image
	make build-fedora-development-image

build-debian-development-image: linux := debian
build-fedora-development-image: linux := fedora

build-debian-development-image build-fedora-development-image: _build-development-image

_build-development-image:

	docker build \
	--file="$(project_directory)/docker/development/$(linux)/Dockerfile" \
	--tag=$(docker_image_repository)-development:$(docker_image_version)-$(linux) \
	--tag=$(docker_image_repository)-development:latest-$(linux) \
	--build-arg="BASE_IMAGE_VERSION=$(development_base_image_version)" \
	--build-arg="VERSION=$(docker_image_version)" \
	"$(project_directory)"

build-cpp-release-debian-image: linux := debian
build-cpp-release-fedora-image: linux := fedora

build-cpp-release-debian-image build-cpp-release-fedora-image: _build-cpp-release-image

_build-cpp-release-image: _build-development-image

	docker build \
	--file="$(project_directory)/docker/release/$(linux)/Dockerfile" \
	--tag=$(docker_image_repository):$(docker_image_version)-$(linux) \
	--tag=$(docker_image_repository):latest-$(linux) \
	--build-arg="VERSION=$(docker_image_version)" \
	--target=cpp-release \
	"$(project_directory)"

build-python-release-debian-image: linux := debian
build-python-release-fedora-image: linux := fedora

build-python-release-debian-image build-python-release-fedora-image: _build-python-release-image

_build-python-release-image: _build-development-image

	docker build \
	--file="$(project_directory)/docker/release/$(linux)/Dockerfile" \
	--tag=$(docker_image_repository)-python:$(docker_image_version)-$(linux) \
	--tag=$(docker_image_repository)-python:latest-$(linux) \
	--build-arg="VERSION=$(docker_image_version)" \
	--target=python-release \
	"$(project_directory)"

build-documentation: linux := debian

build-documentation: _build-development-image

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(linux) \
	/bin/bash -c "cmake -DBUILD_DOCUMENTATION=ON .. && make docs"

build-packages:

	make build-debian-package
	make build-fedora-package

build-debian-package: linux := debian
build-fedora-package: linux := fedora

build-debian-package: package_generator := DEB
build-fedora-package: package_generator := RPM

build-debian-package: package_extension := deb
build-fedora-package: package_extension := rpm

build-debian-package build-fedora-package: _build-package

_build-package:

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(linux) \
	/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF -DCPACK_GENERATOR=$(package_generator) .. && make package && mkdir -p /app/package && mv /app/build/*.$(package_extension) /app/package"

################################################################################################################################################################

run-development: run-development-debian

run-development-debian: linux := debian
run-development-fedora: linux := fedora

run-development-debian run-development-fedora: _run-development

_run-development: _build-development-image

	docker run \
	-it \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="${project_directory}/tools/development/helpers:/app/build/helpers:ro,delegated" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(linux) \
	/bin/bash

run-python: run-python-debian

run-python-debian: linux := debian
run-python-fedora: linux := fedora

run-python-debian run-python-fedora: _run-python

_run-python: _build-python-release-image

	docker run \
	-it \
	--rm \
	$(docker_image_repository)-python:$(docker_image_version)-$(linux)

################################################################################################################################################################

test:

	make test-debian
	make test-fedora

test-debian:

	make test-cpp-debian
	make test-python-debian

test-fedora:

	make test-cpp-fedora
	make test-python-fedora

test-cpp-debian: linux := debian
test-cpp-fedora: linux := fedora

test-cpp-debian test-cpp-fedora: _test-cpp

_test-cpp: _build-development-image

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(linux) \
	/bin/bash -c "cmake -DBUILD_UNIT_TESTS=ON .. && make -j && make test"

test-python-debian: linux := debian
test-python-fedora: linux := fedora

test-python-debian test-python-fedora: _test-python

_test-python: _build-python-release-image

	docker run \
	--rm \
	--workdir=/usr/local/lib/python3.7/site-packages/Library/Core \
	--entrypoint="" \
	$(docker_image_repository)-python:$(docker_image_version)-$(linux) \
	/bin/bash -c "pip install pytest && pytest ."

coverage:

	make coverage-cpp

coverage-cpp:

	make coverage-cpp-debian

coverage-cpp-debian: linux := debian
coverage-cpp-fedora: linux := fedora

coverage-cpp-debian coverage-cpp-fedora: _coverage-cpp

_coverage-cpp: _build-development-image

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(linux) \
	/bin/bash -c "cmake -DBUILD_CODE_COVERAGE=ON .. && make -j && make coverage"

################################################################################################################################################################

debug-development-debian: linux := debian
debug-development-fedora: linux := fedora

debug-development-debian debug-development-fedora: _debug-development

_debug-development: _build-development-image

	docker run \
	-it \
	--rm \
	$(docker_image_repository)-development:$(docker_image_version)-$(linux) \
	/bin/bash

debug-cpp-release-debian: linux := debian
debug-cpp-release-debian: linux := fedora

debug-cpp-release-debian debug-cpp-release-debian: _debug-cpp-release

_debug-cpp-release: _build-cpp-release-image

	docker run \
	-it \
	--rm \
	--entrypoint=/bin/bash \
	$(docker_image_repository):$(docker_image_version)-$(linux)

debug-python-release-debian: linux := debian
debug-python-release-fedora: linux := fedora

debug-python-release-debian debug-python-release-fedora: _debug-python-release

_debug-python-release: _build-python-release-image

	docker run \
	-it \
	--rm \
	--entrypoint=/bin/bash \
	$(docker_image_repository)-python:$(docker_image_version)-$(linux)

################################################################################################################################################################

deploy-python: build-debian-development-image

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-debian \
	/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF .. && make -j && make publish"

deploy-coverage: linux := debian

deploy-coverage: _coverage-cpp

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-$(linux) \
	/bin/bash -c "bash <(curl -s https://codecov.io/bash) -X gcov -y /app/.codecov.yml -t ${ci_codecov_token} || echo 'Codecov did not collect coverage reports'"

deploy-documentation: build-documentation

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

	rm -r "$(project_directory)/build" || true
	rm -r "$(project_directory)/bin/"*.test* || true
	rm -r "$(project_directory)/lib/"*.so* || true

################################################################################################################################################################

.PHONY: build build-images \
		build-development-images build-debian-development-image build-fedora-development-image \
		build-cpp-release-debian-image build-python-release-debian-image build-python-release-fedora-image \
		build-documentation \
		build-packages build-debian-package build-fedora-package \
		run-development run-development-debian run-development-fedora \
		run-python run-python-debian run-python-fedora \
		test test-debian test-fedora \
		test-cpp-debian test-cpp-fedora \
		coverage-cpp-debian coverage-cpp-fedora \
		test-python-debian test-python-fedora \
		debug-development-debian debug-cpp-release-debian debug-python-release-debian \
		debug-development-fedora debug-cpp-release-fedora debug-python-release-fedora \
		deploy-python deploy-coverage deploy-documentation \
		clean

################################################################################################################################################################
