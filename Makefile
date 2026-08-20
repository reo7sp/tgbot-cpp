BUILD_TYPE ?= Release
BUILD_DIR ?= build/$(BUILD_TYPE)
NPROC ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)
CONAN_BUILD_ARGS ?= --build=missing
CONAN_VERBOSITY ?= quiet
CONAN_RECIPE_VERSION ?= $(shell git describe --tags --abbrev=0 --match 'v*' 2>/dev/null | sed 's/^v//')
CONAN_RECIPE_ARGS ?=
CMAKE_LOG_LEVEL ?= STATUS
CMAKE_INSTALL_MESSAGE ?= ALWAYS
CMAKE_BUILD_ARGS ?=
ENABLE_SANITIZERS ?= OFF
ENABLE_COVERAGE ?= OFF
POETRY_INSTALL_ARGS ?= --no-interaction --quiet
INSTALL_PREFIX ?=
API_METHODS_CPP = src/ApiMethods.cpp
API_METHODS_INC = include/tgbot/ApiMethods.inc.h
API_METHODS_CLANG_FORMAT_CONFIG = api_codegen/clang-format-api-methods.yaml
CPP_FILES = $(shell find include src tests examples -type f \( -name '*.h' -o -name '*.cpp' \) ! -name '*.inc.h' ! -path '$(API_METHODS_CPP)' | sort)
PYTHON_FILES = conanfile.py coverage_summary.py api_codegen
DOCKER_IMAGE ?= reo7sp/tgbot-cpp
DOCKER_TEST_IMAGE ?= reo7sp/tgbot-cpp-test
DOCKER_PLATFORM ?= linux/amd64
EXAMPLE ?= echobot
EXAMPLES := $(sort $(notdir $(patsubst %/,%,$(dir $(wildcard examples/*/CMakeLists.txt)))))
EXAMPLE_IMAGE ?= tgbot-cpp-example-$(EXAMPLE)
PORT ?= 8080
DOCS_WORKTREE := $(abspath build/gh-pages)
COVERAGE_REPORT_DIR ?= $(BUILD_DIR)/coverage

ifeq ($(OS),Windows_NT)
export CMAKE_GENERATOR ?= Ninja
CONAN_BUILD_ARGS += -c tools.cmake.cmaketoolchain:generator=Ninja
endif

.PHONY: \
	all \
	dependencies \
	dependencies-python \
	dependencies-with-test \
	configure \
	configure-with-system \
	configure-with-test \
	build \
	build-with-system \
	build-with-test \
	compile-commands \
	example \
	examples \
	test \
	test-only \
	test-api-codegen \
	coverage \
	coverage-python \
	install \
	install-with-system \
	install-only \
	api-update \
	api-generate \
	format \
	format-cpp \
	format-python \
	lint \
	lint-cpp \
	lint-python \
	lint-ci \
	docker-image \
	docker-test-image \
	docker-test \
	docker-test-only \
	docker-test-api-codegen \
	docker-push \
	docker-example-image \
	docker-run-example \
	docker-run-example-webhook \
	docker-compose-run-examples \
	docker-compose-stop-examples \
	docs \
	docs-publish \
	test-conan-recipe \
	conan-publish \
	list-includes \
	list-srcs

all: build

dependencies:
	conan profile detect --exist-ok -v$(CONAN_VERBOSITY)
	conan install . $(CONAN_BUILD_ARGS) -v$(CONAN_VERBOSITY) -s build_type=$(BUILD_TYPE) -s compiler.cppstd=20

dependencies-python:
	poetry install $(POETRY_INSTALL_ARGS)

dependencies-with-test: dependencies-python
	conan profile detect --exist-ok -v$(CONAN_VERBOSITY)
	conan install . $(CONAN_BUILD_ARGS) -v$(CONAN_VERBOSITY) -s build_type=$(BUILD_TYPE) -s compiler.cppstd=20 -o '&:with_tests=True'

configure: dependencies
	cmake --log-level=$(CMAKE_LOG_LEVEL) -S . -B $(BUILD_DIR) \
		-DCMAKE_TOOLCHAIN_FILE=$(abspath $(BUILD_DIR)/generators/conan_toolchain.cmake) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_INSTALL_MESSAGE=$(CMAKE_INSTALL_MESSAGE) \
		-DENABLE_SANITIZERS=$(ENABLE_SANITIZERS) \
		-DENABLE_COVERAGE=$(ENABLE_COVERAGE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DENABLE_TESTS=OFF

configure-with-system:
	cmake --log-level=$(CMAKE_LOG_LEVEL) -S . -B $(BUILD_DIR) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_INSTALL_MESSAGE=$(CMAKE_INSTALL_MESSAGE) \
		-DENABLE_SANITIZERS=$(ENABLE_SANITIZERS) \
		-DENABLE_COVERAGE=$(ENABLE_COVERAGE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DENABLE_TESTS=OFF

configure-with-test: dependencies-with-test
	cmake --log-level=$(CMAKE_LOG_LEVEL) -S . -B $(BUILD_DIR) \
		-DCMAKE_TOOLCHAIN_FILE=$(abspath $(BUILD_DIR)/generators/conan_toolchain.cmake) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_INSTALL_MESSAGE=$(CMAKE_INSTALL_MESSAGE) \
		-DENABLE_SANITIZERS=$(ENABLE_SANITIZERS) \
		-DENABLE_COVERAGE=$(ENABLE_COVERAGE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DENABLE_TESTS=ON

build: configure
	cmake --build $(BUILD_DIR) --parallel $(NPROC) $(CMAKE_BUILD_ARGS)

build-with-system: configure-with-system
	cmake --build $(BUILD_DIR) --parallel $(NPROC) $(CMAKE_BUILD_ARGS)

build-with-test: configure-with-test
	cmake --build $(BUILD_DIR) --parallel $(NPROC) $(CMAKE_BUILD_ARGS)

compile-commands: configure-with-test
	cmake -E copy_if_different $(BUILD_DIR)/compile_commands.json compile_commands.json

example:
	$(MAKE) -C examples/$(EXAMPLE) \
		BUILD_TYPE=$(BUILD_TYPE) \
		BUILD_DIR=$(abspath $(BUILD_DIR)/examples/$(EXAMPLE)) \
		TOOLCHAIN_FILE=$(abspath $(BUILD_DIR)/generators/conan_toolchain.cmake) \
		INSTALL_PREFIX=$(if $(INSTALL_PREFIX),$(abspath $(INSTALL_PREFIX)),) \
		NPROC=$(NPROC)

examples:
	@set -e; for example in $(EXAMPLES); do \
		$(MAKE) example EXAMPLE=$$example; \
	done

test: build-with-test
	$(MAKE) test-only
	$(MAKE) test-api-codegen

test-only:
	ctest --test-dir $(BUILD_DIR) --output-on-failure

test-api-codegen:
	poetry run pytest api_codegen/tests

coverage:
	cmake -E make_directory $(COVERAGE_REPORT_DIR)
	gcovr $(BUILD_DIR) \
		--root . \
		--filter 'include/tgbot/' \
		--filter 'src/' \
		--gcov-ignore-parse-errors=negative_hits.warn_once_per_file \
		--exclude-throw-branches \
		--exclude-unreachable-branches \
		--html-details $(COVERAGE_REPORT_DIR)/coverage.html
	gcovr $(BUILD_DIR) \
		--root . \
		--filter 'include/tgbot/' \
		--filter 'src/' \
		--exclude 'src/ApiMethods\.cpp' \
		--exclude 'src/Types\.cpp' \
		--gcov-ignore-parse-errors=negative_hits.warn_once_per_file \
		--exclude-throw-branches \
		--exclude-unreachable-branches \
		--coveralls $(COVERAGE_REPORT_DIR)/coveralls.json \
		--lcov $(COVERAGE_REPORT_DIR)/lcov.info
	python3 coverage_summary.py $(COVERAGE_REPORT_DIR)/coveralls.json

coverage-python:
	cmake -E make_directory $(BUILD_DIR)
	COVERAGE_FILE=$(BUILD_DIR)/.coverage-python poetry run pytest api_codegen/tests \
		--cov=api_codegen \
		--cov-report=term-missing

install: build
	$(MAKE) install-only

install-with-system: build-with-system
	$(MAKE) install-only

install-only:
	cmake --install $(BUILD_DIR) $(if $(INSTALL_PREFIX),--prefix $(abspath $(INSTALL_PREFIX)),)

api-update: dependencies-python
	poetry run python -m api_codegen.main update

api-generate: dependencies-python
	poetry run python -m api_codegen.main generate
	$(MAKE) format-cpp

format: format-cpp format-python

format-cpp:
	clang-format -i $(CPP_FILES)
	clang-format -i --style='file:$(API_METHODS_CLANG_FORMAT_CONFIG)' $(API_METHODS_CPP)
	sh api_codegen/format-api-methods-inc.sh --write $(API_METHODS_INC) $(API_METHODS_CLANG_FORMAT_CONFIG)

format-python:
	poetry run ruff check --fix $(PYTHON_FILES)
	poetry run ruff format $(PYTHON_FILES)

lint: lint-cpp lint-python

lint-cpp:
	clang-format --dry-run --Werror $(CPP_FILES)
	clang-format --dry-run --Werror --style='file:$(API_METHODS_CLANG_FORMAT_CONFIG)' $(API_METHODS_CPP)
	sh api_codegen/format-api-methods-inc.sh --check $(API_METHODS_INC) $(API_METHODS_CLANG_FORMAT_CONFIG)

lint-python:
	poetry run ruff check $(PYTHON_FILES)
	poetry run ruff format --check $(PYTHON_FILES)

lint-ci:
	go run github.com/rhysd/actionlint/cmd/actionlint@v1.7.12

docker-image:
	docker build --platform=$(DOCKER_PLATFORM) -t $(DOCKER_IMAGE) -f Dockerfile .

docker-test-image:
	docker build --platform=$(DOCKER_PLATFORM) -t $(DOCKER_TEST_IMAGE) -f Dockerfile_test .

docker-test: docker-test-image
	$(MAKE) docker-test-only
	$(MAKE) docker-test-api-codegen

docker-test-only:
	docker run --rm -t --platform=$(DOCKER_PLATFORM) -e MAKEFLAGS $(DOCKER_TEST_IMAGE) make test-only

docker-test-api-codegen:
	docker run --rm -t --platform=$(DOCKER_PLATFORM) -e MAKEFLAGS $(DOCKER_TEST_IMAGE) make test-api-codegen

docker-push:
	@set -eu; \
		version=$$(git describe --tags --exact-match --match 'v*' 2>/dev/null | sed 's/^v//'); \
		test -n "$$version" || { echo "Run this target on a v* release tag" >&2; exit 2; }; \
		$(MAKE) docker-image; \
		docker tag "$(DOCKER_IMAGE)" "$(DOCKER_IMAGE):$$version"; \
		docker push "$(DOCKER_IMAGE)"; \
		docker push "$(DOCKER_IMAGE):$$version"

docker-example-image: docker-image
	docker build --platform=$(DOCKER_PLATFORM) \
		--build-arg TGBOT_CPP_IMAGE=$(DOCKER_IMAGE) \
		-t $(EXAMPLE_IMAGE) \
		-f examples/$(EXAMPLE)/Dockerfile \
		$(if $(filter echobot-submodule,$(EXAMPLE)),.,examples/$(EXAMPLE))

docker-run-example: docker-example-image
	@test -n "$$TOKEN" || (echo "TOKEN is required" >&2; exit 2)
	docker run --rm -it --init --platform=$(DOCKER_PLATFORM) -e TOKEN $(EXAMPLE_IMAGE)

docker-run-example-webhook: docker-example-image
	@test -n "$$TOKEN" || (echo "TOKEN is required" >&2; exit 2)
	@test -n "$$WEBHOOK_URL" || (echo "WEBHOOK_URL is required" >&2; exit 2)
	docker run --rm -it --init --platform=$(DOCKER_PLATFORM) -e TOKEN -e WEBHOOK_URL -p $(PORT):8080 $(EXAMPLE_IMAGE)

docker-compose-run-examples: docker-image
	DOCKER_PLATFORM=$(DOCKER_PLATFORM) TGBOT_CPP_IMAGE=$(DOCKER_IMAGE) docker compose --env-file env -f docker-compose.test.yaml up --build

docker-compose-stop-examples:
	docker compose --env-file env -f docker-compose.test.yaml down

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

test-conan-recipe:
	@test -n "$(CONAN_RECIPE_VERSION)" || { echo "CONAN_RECIPE_VERSION is required" >&2; exit 2; }
	@set -eu; \
		recipe=$$(mktemp -d); \
		archive=$$(mktemp); \
		trap 'rm -rf "$$recipe"; rm -f "$$archive"' EXIT; \
		url="https://github.com/reo7sp/tgbot-cpp/archive/v$(CONAN_RECIPE_VERSION).tar.gz"; \
		curl -fL "$$url" -o "$$archive"; \
		sha256=$$(shasum -a 256 "$$archive" | cut -d ' ' -f 1); \
		cp -R conan-center/. "$$recipe/"; \
		printf 'sources:\n  "%s":\n    url: "%s"\n    sha256: "%s"\n' \
			"$(CONAN_RECIPE_VERSION)" "$$url" "$$sha256" > "$$recipe/conandata.yml"; \
		conan profile detect --exist-ok; \
		conan create "$$recipe" --version="$(CONAN_RECIPE_VERSION)" \
			--build='tgbot/*' $(CONAN_BUILD_ARGS) \
			-s build_type=Release -s compiler.cppstd=20 \
			$(CONAN_RECIPE_ARGS); \
		conan create "$$recipe" --version="$(CONAN_RECIPE_VERSION)" \
			--build='tgbot/*' $(CONAN_BUILD_ARGS) \
			-s build_type=Debug -s compiler.cppstd=20 \
			-o '*/*:shared=True' \
			$(CONAN_RECIPE_ARGS)

conan-publish: test-conan-recipe
	@command -v gh >/dev/null || (echo "gh is required to create the Conan Center pull request" >&2; exit 2)
	@set -eu; \
		version=$$(git describe --tags --exact-match --match 'v*' 2>/dev/null | sed 's/^v//'); \
		test -n "$$version" || { echo "Run this target on a v* release tag" >&2; exit 2; }; \
		index="$(abspath build/conan-center-index)"; \
		branch="package/tgbot-$$version"; \
		title="tgbot: add version $$version"; \
		body=$$(printf '%s\n' \
			'### Summary' \
			"Changes to recipe: **tgbot/$$version**" \
			'' \
			'#### Motivation' \
			"Add tgbot-cpp $$version to Conan Center." \
			'' \
			'#### Details' \
			"Add version $$version with its source checksum and the corresponding recipe and test package." \
			'' \
			'---' \
			'- [x] Read the [contributing guidelines](https://github.com/conan-io/conan-center-index/blob/master/CONTRIBUTING.md)' \
			'- [x] Checked that this PR is not a duplicate: [list of PRs by recipe](https://github.com/conan-io/conan-center-index/discussions/24240)' \
			'- [ ] If this is a bug fix, please link related issue or provide bug details' \
			'- [x] Tested locally with at least one configuration using a recent version of Conan' \
			'' \
			'---' \
			'Add a :+1: reaction to pull requests you find [important](https://github.com/conan-io/conan-center-index/pulls?q=is%3Aopen+sort%3Areactions-%2B1-desc) to help the team prioritize, thanks!'); \
		owner=$$(gh api user --jq .login); \
		if test ! -d "$$index/.git"; then \
			gh repo view "$$owner/conan-center-index" >/dev/null 2>&1 || \
				gh repo fork conan-io/conan-center-index --clone=false; \
			gh repo clone "$$owner/conan-center-index" "$$index" -- --filter=blob:none --sparse; \
		fi; \
		git -C "$$index" sparse-checkout set recipes/tgbot; \
		git -C "$$index" remote get-url upstream >/dev/null 2>&1 || \
			git -C "$$index" remote add upstream https://github.com/conan-io/conan-center-index.git; \
		test -z "$$(git -C "$$index" status --porcelain)" || \
			{ echo "The conan-center-index checkout must be clean" >&2; exit 2; }; \
		git -C "$$index" fetch upstream master; \
		git -C "$$index" switch -c "$$branch" upstream/master; \
		recipe="$$index/recipes/tgbot"; \
		tag="v$$version"; \
		url="https://github.com/reo7sp/tgbot-cpp/archive/$$tag.tar.gz"; \
		archive=$$(mktemp); \
		trap 'rm -f "$$archive"' EXIT; \
		grep -q "\"$$version\"" "$$recipe/config.yml" && \
			{ echo "tgbot/$$version already exists in Conan Center index" >&2; exit 2; }; \
		curl -fL "$$url" -o "$$archive"; \
		sha256=$$(shasum -a 256 "$$archive" | cut -d ' ' -f 1); \
		cp -R conan-center/. "$$recipe/all/"; \
		printf '  "%s":\n    folder: all\n' "$$version" >> "$$recipe/config.yml"; \
		printf '  "%s":\n    url: "%s"\n    sha256: "%s"\n' "$$version" "$$url" "$$sha256" >> "$$recipe/all/conandata.yml"; \
		git -C "$$index" add recipes/tgbot; \
		git -C "$$index" commit -m "$$title"; \
		git -C "$$index" push -u origin "$$branch"; \
		gh pr create --repo conan-io/conan-center-index \
			--head "$$owner:$$branch" \
			--title "$$title" \
			--body "$$body" \
			--draft

list-includes:
	@find include -type f -name '*.h' -print | sort | sed 's|^include/|#include "|; s|$$|"|'

list-srcs:
	@find src -type f -name '*.cpp' -print | sort
