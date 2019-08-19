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

################################################################################################################################################################

build: build-images

build-images: build-development-images

build-development-images: build-debian-development-image

build-debian-development-image:

	docker build \
	--file="$(project_directory)/docker/development/debian/Dockerfile" \
	--tag=$(docker_image_repository)-development:$(docker_image_version)-debian \
	--tag=$(docker_image_repository)-development:latest-debian \
	--build-arg="VERSION=$(docker_image_version)" \
	"$(project_directory)"

build-cpp-release-debian-image: build-debian-development-image

	docker build \
	--file="$(project_directory)/docker/release/debian/Dockerfile" \
	--tag=$(docker_image_repository):$(docker_image_version)-debian \
	--tag=$(docker_image_repository):latest-debian \
	--build-arg="VERSION=$(docker_image_version)" \
	--target=cpp-release \
	"$(project_directory)"

build-python-release-debian-image: build-debian-development-image

	docker build \
	--file="$(project_directory)/docker/release/debian/Dockerfile" \
	--tag=$(docker_image_repository)-python:$(docker_image_version)-debian \
	--tag=$(docker_image_repository)-python:latest-debian \
	--build-arg="VERSION=$(docker_image_version)" \
	--target=python-release \
	"$(project_directory)"

################################################################################################################################################################

run-development: run-development-debian

run-development-debian: build-debian-development-image

	docker run \
	-it \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-debian \
	/bin/bash

run-python: run-python-debian

run-python-debian: build-python-release-debian-image

	docker run \
	-it \
	--rm \
	$(docker_image_repository)-python:$(docker_image_version)-debian

################################################################################################################################################################

test: test-debian

test-debian: test-cpp-debian test-python-debian

test-cpp-debian: build-debian-development-image

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_image_repository)-development:$(docker_image_version)-debian \
	/bin/bash -c "cmake -DBUILD_UNIT_TESTS=ON .. && make -j && make test"

test-coverage-cpp-debian: build-debian-development-image

	docker run \
	--rm \
	--volume="$(project_directory):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/sh \
	$(docker_image_repository)-development:$(docker_image_version)-debian \
	/bin/bash -c "cmake -DBUILD_CODE_COVERAGE=ON .. && make -j && make coverage"

test-python-debian: build-python-release-debian-image

	docker run \
	--rm \
	--workdir=/usr/local/lib/python3.7/site-packages \
	--entrypoint="" \
	$(docker_image_repository)-python:$(docker_image_version)-debian \
	/bin/bash -c "pip install pytest && pytest ./Library/Core"

################################################################################################################################################################

debug-development-debian: build-debian-development-image

	docker run \
	-it \
	--rm \
	$(docker_image_repository)-development:$(docker_image_version)-debian \
	/bin/bash

debug-cpp-release-debian: build-cpp-release-debian-image

	docker run \
	-it \
	--rm \
	--entrypoint=/bin/bash \
	$(docker_image_repository):$(docker_image_version)-debian

debug-python-release-debian: build-python-release-debian-image

	docker run \
	-it \
	--rm \
	--entrypoint=/bin/bash \
	$(docker_image_repository)-python:$(docker_image_version)-debian

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
