BUILD_TYPE ?= Release
BUILD_DIR ?= build/$(BUILD_TYPE)
NPROC ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)
CONAN_BUILD_ARGS ?= --build=missing
INSTALL_PREFIX ?=
INSTALL_PREFIX_ARG = $(if $(INSTALL_PREFIX),--prefix $(INSTALL_PREFIX),)
CPP_FILES = $(shell find include src tests examples -type f \( -name '*.h' -o -name '*.cpp' \) ! -name '*.inc.h' | sort)
PYTHON_FILES = conanfile.py api_codegen
DOCKER_IMAGE ?= reo7sp/tgbot-cpp
DOCKER_TEST_IMAGE ?= reo7sp/tgbot-cpp-test
DOCKER_PLATFORM ?= linux/amd64
EXAMPLE ?= echobot
EXAMPLE_IMAGE ?= tgbot-cpp-example-$(EXAMPLE)
EXAMPLE_CMAKE_ARGS = $(if $(filter echobot-submodule,$(EXAMPLE)),-DTGBOT_CPP_SOURCE_DIR=$(CURDIR),) \
	$(if $(INSTALL_PREFIX),-DCMAKE_PREFIX_PATH=$(INSTALL_PREFIX),)
PORT ?= 8080
DOCS_WORKTREE := $(abspath build/gh-pages)

.PHONY: all dependencies dependencies-python dependencies-with-test configure configure-with-system configure-with-test build build-with-system build-with-test compile-commands example test test-only test-api-codegen install install-with-system install-only api-update api-generate \
	docker-image docker-test-image docker-test docker-example-image docker-compose-run-examples docker-push docker-run-example \
	docker-run-example-webhook docs docs-publish list-includes list-srcs \
	format format-cpp format-python lint lint-cpp lint-python

all: build

dependencies:
	conan profile detect --exist-ok
	conan install . $(CONAN_BUILD_ARGS) -s build_type=$(BUILD_TYPE)

dependencies-python:
	poetry install --no-interaction

dependencies-with-test: dependencies-python
	conan profile detect --exist-ok
	conan install . $(CONAN_BUILD_ARGS) -s build_type=$(BUILD_TYPE) -o '&:with_tests=True'

configure: dependencies
	cmake -S . -B $(BUILD_DIR) \
		-DCMAKE_TOOLCHAIN_FILE=$(abspath $(BUILD_DIR)/generators/conan_toolchain.cmake) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DENABLE_TESTS=OFF

configure-with-system:
	cmake -S . -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DENABLE_TESTS=OFF

configure-with-test: dependencies-with-test
	cmake -S . -B $(BUILD_DIR) \
		-DCMAKE_TOOLCHAIN_FILE=$(abspath $(BUILD_DIR)/generators/conan_toolchain.cmake) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DENABLE_TESTS=ON

build: configure
	cmake --build $(BUILD_DIR) --parallel $(NPROC)

build-with-system: configure-with-system
	cmake --build $(BUILD_DIR) --parallel $(NPROC)

build-with-test: configure-with-test
	cmake --build $(BUILD_DIR) --parallel $(NPROC)

compile-commands: configure-with-test
	cmake -E copy_if_different $(BUILD_DIR)/compile_commands.json compile_commands.json

example:
	cmake -S examples/$(EXAMPLE) -B $(BUILD_DIR)/examples/$(EXAMPLE) \
		-DCMAKE_TOOLCHAIN_FILE=$(abspath $(BUILD_DIR)/generators/conan_toolchain.cmake) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DENABLE_TESTS=OFF \
		$(EXAMPLE_CMAKE_ARGS)
	cmake --build $(BUILD_DIR)/examples/$(EXAMPLE) --parallel $(NPROC)

test: build-with-test
	$(MAKE) test-only
	$(MAKE) test-api-codegen

test-only:
	ctest --test-dir $(BUILD_DIR) --output-on-failure

test-api-codegen:
	poetry run pytest -q api_codegen/tests

install: build
	$(MAKE) install-only

install-with-system: build-with-system
	$(MAKE) install-only

install-only:
	cmake --install $(BUILD_DIR) $(INSTALL_PREFIX_ARG)

api-update: dependencies-python
	poetry run python -m api_codegen.main update

api-generate: dependencies-python
	poetry run python -m api_codegen.main generate
	$(MAKE) format-cpp

format: format-cpp format-python

format-cpp:
	clang-format -i $(CPP_FILES)

format-python:
	poetry run ruff check --fix $(PYTHON_FILES)
	poetry run ruff format $(PYTHON_FILES)

lint: lint-cpp lint-python

lint-cpp:
	clang-format --dry-run --Werror $(CPP_FILES)

lint-python:
	poetry run ruff check $(PYTHON_FILES)
	poetry run ruff format --check $(PYTHON_FILES)

docker-image:
	docker build --platform=$(DOCKER_PLATFORM) -t $(DOCKER_IMAGE) -f Dockerfile .

docker-test-image:
	docker build --platform=$(DOCKER_PLATFORM) -t $(DOCKER_TEST_IMAGE) -f Dockerfile_test .

docker-test: docker-test-image
	docker run --rm $(DOCKER_TEST_IMAGE)

docker-push: docker-image
	docker push $(DOCKER_IMAGE)

docker-example-image: docker-image
	docker build --platform=$(DOCKER_PLATFORM) \
		--build-arg TGBOT_CPP_IMAGE=$(DOCKER_IMAGE) \
		-t $(EXAMPLE_IMAGE) \
		-f examples/$(EXAMPLE)/Dockerfile .

docker-run-example: docker-example-image
	@test -n "$$TOKEN" || (echo "TOKEN is required" >&2; exit 2)
	docker run --rm -it -e TOKEN $(EXAMPLE_IMAGE)

docker-run-example-webhook: docker-example-image
	@test -n "$$TOKEN" || (echo "TOKEN is required" >&2; exit 2)
	@test -n "$$WEBHOOK_URL" || (echo "WEBHOOK_URL is required" >&2; exit 2)
	docker run --rm -it -e TOKEN -e WEBHOOK_URL -p $(PORT):8080 $(EXAMPLE_IMAGE)

docker-compose-run-examples: docker-image
	TGBOT_CPP_IMAGE=$(DOCKER_IMAGE) \
		docker compose --env-file env -f docker-compose.test.yaml up --build

docs:
	rm -rf -- doc docs
	doxygen
	mv doc/html docs
	touch docs/.nojekyll

docs-publish: docs
	git fetch origin gh-pages
	git worktree add --detach $(DOCS_WORKTREE) origin/gh-pages
	find $(DOCS_WORKTREE) -mindepth 1 -maxdepth 1 ! -name .git -exec rm -rf -- {} +
	cp -R docs/. $(DOCS_WORKTREE)/
	git -C $(DOCS_WORKTREE) add -A
	git -C $(DOCS_WORKTREE) diff --cached --quiet || \
		git -C $(DOCS_WORKTREE) commit -m "Updated docs $$(date +%Y-%m-%d)"
	git -C $(DOCS_WORKTREE) push origin HEAD:gh-pages
	git worktree remove $(DOCS_WORKTREE)

list-includes:
	@find include -type f -name '*.h' -print | sort | \
		sed 's|^include/|#include "|; s|$$|"|'

list-srcs:
	@find src -type f -name '*.cpp' -print | sort
