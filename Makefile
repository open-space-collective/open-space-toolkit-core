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

export development_base_image_version := 0.1.8

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

test-coverage-cpp-debian: linux := debian
test-coverage-cpp-fedora: linux := fedora

test-coverage-cpp-debian test-coverage-cpp-fedora: _test-coverage-cpp

_test-coverage-cpp: _build-development-image

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/sh \
	$(docker_image_repository)-development:$(docker_image_version)-$(linux) \
	/bin/bash -c "cmake -DBUILD_CODE_COVERAGE=ON .. && make -j && make coverage"

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

# deploy: deploy-cpp deploy-python

# deploy-cpp: build-debian-development-image

# 	docker run \
# 	--rm \
# 	--volume="$(project_directory):/app:delegated" \
# 	--volume="/app/build" \
# 	--workdir=/app/build \
# 	$(docker_image_repository)-development:$(docker_image_version)-debian \
# 	/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF .. && make -j && make package"

# deploy-python: build-debian-development-image

# 	docker run \
# 	--rm \
# 	--volume="$(project_directory):/app:delegated" \
# 	--volume="/app/build" \
# 	--workdir=/app/build \
# 	$(docker_image_repository)-development:$(docker_image_version)-debian \
# 	/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF .. && make -j && make publish"

################################################################################################################################################################

clean:

	rm -r "$(project_directory)/build" || true
	rm -r "$(project_directory)/bin/"*.test* || true
	rm -r "$(project_directory)/lib/"*.so* || true

################################################################################################################################################################

.PHONY: build build-images build-development-images build-debian-development-image build-cpp-release-debian-image build-python-release-debian-image \
		run-development run-development-debian run-python run-python-debian \
		test test-debian test-cpp-debian test-coverage-cpp-debian test-python-debian \
		debug-development-debian debug-cpp-release-debian debug-python-release-debian \
		clean

################################################################################################################################################################
