
#!/usr/bin/env python
# -*- coding: utf-8 -*-

from conans import ConanFile, CMake, tools
import os
import shutil


class TgbotConan(ConanFile):
    name = "tgbot_cpp"
    version = "b35438d"
    description = "C++ library for Telegram bot API"
    url = "https://github.com/reo7sp/tgbot-cpp"
    homepage = "http://reo7sp.github.io/tgbot-cpp"
    license = "MIT"

    exports_sources = ["LICENSE", ]
    scm = {"type": "git",
           "url": "auto",
           "revision": "auto"}

    generators = "cmake"
    settings = "os", "arch", "compiler", "build_type"
    options = {"fPIC": [True, False],
               "shared": [True, False]}
    default_options = {"fPIC": True, "shared": True}

    boost_version = "1.68.0"
    requires = (
        "boost/{}@conan/stable".format(boost_version),
        "OpenSSL/[>=1.0,<1.1]@conan/stable",
        "libcurl/7.56.1@bincrafters/stable"
    )

    def source(self):
        tools.replace_in_file(os.path.join(self.source_folder, "CMakeLists.txt"),
                              "find_package(Boost 1.59.0 COMPONENTS system REQUIRED)",
                              "find_package(Boost {} COMPONENTS system REQUIRED)".format(
                                  self.boost_version))
        tools.replace_in_file(os.path.join(self.source_folder, "CMakeLists.txt"),
                              "set(LIB_LIST", "set(LIB_LIST z")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["ENABLE_TESTS"] = False
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        self.copy(pattern="LICENSE", dst="licenses")
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ['TgBot']
