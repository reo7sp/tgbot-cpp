BUILD_TYPE ?= Release
BUILD_DIR ?= build/$(BUILD_TYPE)
TOOLCHAIN_FILE ?=
INSTALL_PREFIX ?=
TGBOT_CPP_SOURCE_DIR ?= ../..
NPROC ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)

.PHONY: all configure build install

all: build

configure:
	cmake -S . -B $(BUILD_DIR) \
		$(if $(TOOLCHAIN_FILE),-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE),) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DENABLE_TESTS=OFF \
		-DTGBOT_CPP_SOURCE_DIR=$(abspath $(TGBOT_CPP_SOURCE_DIR)) \
		$(if $(INSTALL_PREFIX),-DCMAKE_PREFIX_PATH=$(INSTALL_PREFIX),)

build: configure
	cmake --build $(BUILD_DIR) --parallel $(NPROC)

install: build
	cmake --install $(BUILD_DIR) $(if $(INSTALL_PREFIX),--prefix $(INSTALL_PREFIX),)
