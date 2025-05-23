# Apache License 2.0

project_name := core
project_name_camel_case := $(shell echo $(project_name) | sed -r 's/(^|-)([a-z])/\U\2/g')
project_version := $(shell git describe --tags --always)

docker_registry_path := openspacecollective
docker_image_repository := $(docker_registry_path)/open-space-toolkit-$(project_name)
docker_image_version := $(project_version)

docker_development_image_repository := $(docker_image_repository)-development
docker_release_image_cpp_repository := $(docker_image_repository)-cpp
docker_release_image_python_repository := $(docker_image_repository)-python
docker_release_image_jupyter_repository := $(docker_image_repository)-jupyter

test_python_version := 3.11
test_python_directory := /usr/local/lib/python${test_python_version}/dist-packages

jupyter_notebook_port := 9005
jupyter_python_version := 3.11
jupyter_python_version_without_dot := $(shell echo $(jupyter_python_version) | sed 's/\.//')
jupyter_notebook_image_repository := jupyter/scipy-notebook:x86_64-python-$(jupyter_python_version).3
extract_python_package_version := $(shell echo $(project_version) | sed 's/-/./' | sed 's/-.*//')

dev_username := developer


# Handle multi-platform builds locally (CI sets these env vars, but need defaults here)
TARGETPLATFORM ?= linux/amd64
$(info Target platform is $(TARGETPLATFORM))

# Debug symbols toggle (on for amd64, off for arm64 builds)
DEBUG_SYMBOLS_TOGGLE := $(shell if [ "$(TARGETPLATFORM)" = "linux/amd64" ]; then echo "ON"; else echo "OFF"; fi)
$(info Debug symbols $(DEBUG_SYMBOLS_TOGGLE))


pull: ## Pull all images

	@ echo "Pulling images..."

	@ $(MAKE) pull-development-image
	@ $(MAKE) pull-release-images

.PHONY: pull

pull-development-image: ## Pull development image

	@ echo "Pulling development image..."

	docker pull $(docker_development_image_repository):$(docker_image_version) || true
	docker pull $(docker_development_image_repository):latest || true

.PHONY: pull-development-image

pull-release-images: ## Pull release images

	@ echo "Pull release images..."

	@ $(MAKE) pull-release-image-cpp

	@ $(MAKE) pull-release-image-python

	@ $(MAKE) pull-release-image-jupyter

.PHONY: pull-release-images

pull-release-image-cpp: ## Pull release image cpp

	@ echo "Pull C++ release image..."

	docker pull $(docker_release_image_cpp_repository):$(docker_image_version) || true
	docker pull $(docker_release_image_cpp_repository):latest || true

.PHONY: pull-release-image-cpp

pull-release-image-python: ## Pull release image python

	@ echo "Pulling Python release image..."

	docker pull $(docker_release_image_python_repository):$(docker_image_version) || true
	docker pull $(docker_release_image_python_repository):latest || true

.PHONY: pull-release-image-python

pull-release-image-jupyter: ## Pull release image jupyter

	@ echo "Pulling Jupyter Notebook release image..."

	docker pull $(docker_release_image_jupyter_repository):$(docker_image_version) || true
	docker pull $(docker_release_image_jupyter_repository):latest || true

.PHONY: pull-release-image-jupyter

build: build-images ## Build all images

build-images: ## Build development and release images

	@ echo "Building images..."

	@ $(MAKE) build-development-image
	@ $(MAKE) build-release-images

.PHONY: build-images

build-development-image: pull-development-image ## Build development image

	@ echo "Building development image with root user..."

	docker build \
		--file="$(CURDIR)/docker/development/Dockerfile" \
		--tag=$(docker_development_image_repository):$(docker_image_version) \
		--tag=$(docker_development_image_repository):latest \
		--build-arg="VERSION=$(docker_image_version)" \
		--target=root-user \
		"$(CURDIR)"

.PHONY: build-development-image

build-development-image-non-root: pull-development-image ## Build development image for humans

	@ echo "Building development image for humans with non-root user..."

	docker build \
		--file="$(CURDIR)/docker/development/Dockerfile" \
		--tag=$(docker_development_image_repository)-non-root:$(docker_image_version) \
		--tag=$(docker_development_image_repository)-non-root:latest \
		--build-arg="VERSION=$(docker_image_version)" \
		--build-arg="USER_UID=$(shell id -u)" \
		--build-arg="USER_GID=$(shell id -g)" \
		--target=non-root-user \
		"$(CURDIR)"

.PHONY: build-development-image-non-root

build-release-images: ## Build release images

	@ echo "Building release images..."

	@ $(MAKE) build-release-image-cpp

	@ $(MAKE) build-release-image-python

	@ $(MAKE) build-release-image-jupyter

.PHONY: build-release-images

build-release-image-cpp: build-development-image pull-release-image-cpp ## Build release image cpp

	@ echo "Building C++ release image..."

	docker build \
		--file="$(CURDIR)/docker/release/Dockerfile" \
		--tag=$(docker_release_image_cpp_repository):$(docker_image_version) \
		--tag=$(docker_release_image_cpp_repository):latest \
		--build-arg="VERSION=$(docker_image_version)" \
		--target=cpp-release \
		"$(CURDIR)"

.PHONY: build-release-image-cpp

build-release-image-python: build-development-image pull-release-image-python ## Build release image python

	@ echo "Building Python release image..."

	docker build \
		--file="$(CURDIR)/docker/release/Dockerfile" \
		--tag=$(docker_release_image_python_repository):$(docker_image_version) \
		--tag=$(docker_release_image_python_repository):latest \
		--build-arg="VERSION=$(docker_image_version)" \
		--target=python-release \
		"$(CURDIR)"

.PHONY: build-release-image-python

build-release-image-jupyter: pull-release-image-jupyter ## Build release image jupyter

	@ echo "Building Jupyter Notebook release image..."

	docker build \
		--file="$(CURDIR)/docker/jupyter/Dockerfile" \
		--tag=$(docker_release_image_jupyter_repository):$(docker_image_version) \
		--tag=$(docker_release_image_jupyter_repository):latest \
		--build-arg="JUPYTER_NOTEBOOK_IMAGE_REPOSITORY=$(jupyter_notebook_image_repository)" \
		"$(CURDIR)/docker/jupyter"

.PHONY: build-release-image-jupyter

build-documentation: build-development-image ## Build documentation

	@ $(MAKE) build-documentation-standalone

.PHONY: build-documentation

build-documentation-standalone: ## Build documentation (standalone)

	@ echo "Building documentation..."

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF -DBUILD_PYTHON_BINDINGS=ON -DBUILD_SHARED_LIBRARY=ON -DBUILD_DOCUMENTATION=ON .. \
		&& ostk-build \
		&& ostk-install-python \
		&& ostk-build-docs"

.PHONY: build-documentation-standalone

build-packages: ## Build packages

	@ echo "Building packages..."

	@ $(MAKE) build-packages-cpp
	@ $(MAKE) build-packages-python

.PHONY: build-packages

build-packages-cpp: build-development-image ## Build C++ packages

	@ $(MAKE) build-packages-cpp-standalone

.PHONY: build-packages-cpp

build-packages-cpp-standalone: ## Build C++ packages (standalone)

	@ echo "Building C++ packages..."

	docker run \
		--platform $(TARGETPLATFORM) \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF -DBUILD_PYTHON_BINDINGS=OFF -DCPACK_GENERATOR=DEB -DBUILD_WITH_DEBUG_SYMBOLS=$(DEBUG_SYMBOLS_TOGGLE) .. \
		&& $(MAKE) package \
		&& mkdir -p /app/packages/cpp \
		&& mv /app/build/*.deb /app/packages/cpp"

.PHONY: build-packages-cpp-standalone

build-packages-python: build-development-image ## Build Python packages

	@ $(MAKE) build-packages-python-standalone

.PHONY: build-packages-python

build-packages-python-standalone: ## Build Python packages (standalone)

	@ echo "Building Python packages..."

	docker run \
		--platform $(TARGETPLATFORM) \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF -DBUILD_PYTHON_BINDINGS=ON -DBUILD_WITH_DEBUG_SYMBOLS=$(DEBUG_SYMBOLS_TOGGLE) .. \
		&& $(MAKE) -j 4 \
		&& mkdir -p /app/packages/python \
		&& mv /app/build/bindings/python/dist/*.whl /app/packages/python"

.PHONY: build-packages-python-standalone

start-development dev: build-development-image-non-root ## Start development environment

	@ echo "Starting development environment..."
	@ mkdir -p "$(CURDIR)/build"

	docker run \
		--name=open-space-toolkit-$(project_name)-dev-non-root \
		-it \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="$(HOME)/.ssh:/home/$(dev_username)/.ssh:ro" \
		--volume="$(HOME)/.gitconfig:/home/$(dev_username)/.gitconfig:ro" \
		--workdir=/app/build \
		$(docker_development_image_repository)-non-root:$(docker_image_version) \
		/bin/zsh

.PHONY: start-development dev

start-python: build-release-image-python ## Start Python runtime environment

	@ echo "Starting Python runtime environment..."

	docker run \
		-it \
		--rm \
		$(docker_release_image_python_repository):$(docker_image_version)

.PHONY: start-python

start-jupyter: build-release-image-jupyter ## Start Jupyter Notebook environment

	@ echo "Starting Jupyter Notebook environment..."

	docker run \
		-it \
		--rm \
		--publish="$(jupyter_notebook_port):8888" \
		--volume="$(CURDIR)/bindings/python/docs:/home/jovyan/docs" \
		--volume="$(CURDIR)/tutorials/python/notebooks:/home/jovyan/tutorials" \
		--workdir="/home/jovyan" \
		$(docker_release_image_jupyter_repository):$(docker_image_version) \
		/bin/bash -c "start-notebook.sh --ServerApp.token=''"

.PHONY: start-jupyter-notebook

debug-jupyter-rebuild: build-development-image ## Debug jupyter notebook using the ostk-astro package built from current source code

	@ echo "Building Python$(jupyter_python_version) packages..."

	docker run \
		-it \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF -DBUILD_BENCHMARK=OFF -DBUILD_PYTHON_BINDINGS=ON -DPYTHON_SEARCH_VERSIONS="$(jupyter_python_version)" .. \
		&& $(MAKE) -j $(shell nproc)"

	@ $(MAKE) debug-jupyter

.PHONY: debug-jupyter-rebuild

debug-jupyter: build-release-image-jupyter ## Debug jupyter notebook using the ostk-astro package from pre-built wheels

	@ echo "Debugging Jupyter Notebook environment..."

	docker run \
		-it \
		--rm \
		--user=root \
		--publish="$(jupyter_notebook_port):8888" \
		--volume="$(CURDIR)/bindings/python/docs:/home/jovyan/docs:delegated" \
		--volume="$(CURDIR)/tutorials/python/notebooks:/home/jovyan/tutorials:delegated" \
		--volume="$(CURDIR)/build/bindings/python/OpenSpaceToolkit${project_name_camel_case}Py-python-package-$(jupyter_python_version):/opt/conda/lib/python$(jupyter_python_version)/site-packages/ostk/$(project_name)" \
		--workdir="/home/jovyan" \
		$(docker_release_image_jupyter_repository):$(docker_image_version) \
		/bin/bash -c "chown -R jovyan:users /home/jovyan ; python$(jupyter_python_version) -m pip install /opt/conda/lib/python$(jupyter_python_version)/site-packages/ostk/$(project_name)/ --force-reinstall ; start-notebook.sh --ServerApp.token=''"

	@ sudo chown -R $(shell id -u):$(shell id -g) $(CURDIR)

.PHONY: debug-jupyter

debug-development: build-development-image ## Debug development environment

	@ echo "Debugging development environment..."

	docker run \
		-it \
		--rm \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash

.PHONY: debug-development

debug-cpp-release: build-release-image-cpp ## Debug C++ release environment

	@ echo "Debugging C++ release environment..."

	docker run \
		-it \
		--rm \
		--entrypoint=/bin/bash \
		$(docker_release_image_cpp_repository):$(docker_image_version)

.PHONY: debug-cpp-release

debug-python-release: build-release-image-python ## Debug Python release environment

	@ echo "Debugging Python release environment..."

	docker run \
		-it \
		--rm \
		--entrypoint=/bin/bash \
		$(docker_release_image_python_repository):$(docker_image_version)

.PHONY: debug-python-release

format: ## Run formatting

	@ echo "Formatting..."

	@ $(MAKE) format-cpp
	@ $(MAKE) format-python

.PHONY: format

format-cpp: build-development-image ## Format all of the source code with the rules in .clang-format

	docker run \
		--rm \
		--volume="$(CURDIR):/app" \
		--workdir=/app \
		$(docker_development_image_repository):$(docker_image_version) \
		ostk-format-cpp

.PHONY: format-cpp

format-python: build-development-image ## Run the black format tool against python code

	docker run \
		--rm \
		--volume="$(CURDIR):/app" \
		--workdir=/app \
		$(docker_development_image_repository):$(docker_image_version) \
		ostk-format-python

.PHONY: format-python

format-check: ## Run format checking

	@ echo "Checking format..."

	@ $(MAKE) format-check-cpp
	@ $(MAKE) format-check-python

.PHONY: format-check

format-check-cpp: build-development-image ## Run the clang-format tool to check the code against rules and formatting

	@ $(MAKE) format-check-cpp-standalone

.PHONY: format-check-cpp

format-check-cpp-standalone:

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--workdir=/app \
		$(docker_development_image_repository):$(docker_image_version) \
		ostk-check-format-cpp

.PHONY: format-check-cpp-standalone

format-check-python: build-development-image ## Run the black format tool against python code

	@ $(MAKE) format-check-python-standalone

.PHONY: format-check-python

format-check-python-standalone:

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--workdir=/app \
		$(docker_development_image_repository):$(docker_image_version) \
		ostk-check-format-python

.PHONY: format-check-python-standalone

test: ## Run tests

	@ echo "Running tests..."

	@ $(MAKE) test-unit
	@ $(MAKE) test-coverage

.PHONY: test

test-unit: ## Run unit tests

	@ echo "Running unit tests..."

	@ $(MAKE) test-unit-cpp
	@ $(MAKE) test-unit-python

.PHONY: test-unit

test-unit-cpp: build-development-image ## Run C++ unit tests

	@ $(MAKE) test-unit-cpp-standalone

.PHONY: test-unit-cpp

test-unit-cpp-standalone: ## Run C++ unit tests (standalone)

	@ echo "Running C++ unit tests..."

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_PYTHON_BINDINGS=OFF -DBUILD_UNIT_TESTS=ON .. \
		&& $(MAKE) -j 4 \
		&& $(MAKE) test"

.PHONY: test-unit-cpp-standalone

test-unit-python: build-development-image ## Run Python unit tests

	@ $(MAKE) test-unit-python-standalone

.PHONY: test-unit-python

test-unit-python-standalone: ## Run Python unit tests (standalone)

	@ echo "Running Python unit tests..."

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_PYTHON_BINDINGS=ON -DBUILD_UNIT_TESTS=OFF .. \
		&& $(MAKE) -j 4 \
		&& python${test_python_version} -m pip install --root-user-action=ignore --target=${test_python_directory} bindings/python/OpenSpaceToolkit*Py-python-package-${test_python_version} \
		&& python${test_python_version} -m pip install --root-user-action=ignore --target=${test_python_directory} plotly pandas \
		&& cd ${test_python_directory}/ostk/$(project_name)/ \
		&& python${test_python_version} -m pytest -sv ."

.PHONY: test-unit-python-standalone

ci-test-python: ## Run Python unit tests. Assumes the dev image has already been built, AND that bindings have been built and are available at `packages/python`

	@ echo "Running Python unit tests..."

	docker run \
	--rm \
	--volume="$(CURDIR):/app:delegated" \
	--volume="/app/build" \
	--workdir=/app/build \
	$(docker_development_image_repository):$(docker_image_version) \
	/bin/bash -c "python${test_python_version} -m pip install --root-user-action=ignore --target=${test_python_directory} --find-links /app/packages/python open_space_toolkit_${project_name} \
	&& python${test_python_version} -m pip install --root-user-action=ignore --target=${test_python_directory} plotly pandas \
	&& cd ${test_python_directory}/ostk/$(project_name)/ \
	&& python${test_python_version} -m pytest -sv ."

.PHONY: ci-test-python

test-coverage: ## Run test coverage cpp

	@ echo "Running coverage tests..."

	@ $(MAKE) test-coverage-cpp

.PHONY: test-coverage

test-coverage-cpp: build-development-image ## Run C++ tests with coverage

	@ $(MAKE) test-coverage-cpp-standalone

.PHONY: test-coverage-cpp

test-coverage-cpp-standalone: ## Run C++ tests with coverage (standalone)

	@ echo "Running C++ coverage tests..."

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_UNIT_TESTS=ON -DBUILD_PYTHON_BINDINGS=OFF -DBUILD_CODE_COVERAGE=ON .. \
		&& $(MAKE) -j 4 \
		&& $(MAKE) coverage \
		&& (rm -rf /app/coverage || true) \
		&& mkdir /app/coverage \
		&& mv /app/build/coverage* /app/coverage"

.PHONY: test-coverage-cpp-standalone

clean: ## Clean

	@ echo "Cleaning up..."

	rm -rf "$(CURDIR)/build"
	rm -rf "$(CURDIR)/bin"
	rm -rf "$(CURDIR)/docs/html"
	rm -rf "$(CURDIR)/docs/latex"
	rm -rf "$(CURDIR)/lib"
	rm -rf "$(CURDIR)/coverage"
	rm -rf "$(CURDIR)/packages"
	rm -rf "$(CURDIR)/.open-space-toolkit"

.PHONY: clean

help:

	@grep -E '^[0-9a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

export DOCKER_BUILDKIT = 1

.DEFAULT_GOAL := help
