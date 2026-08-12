import os

from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, rmdir

required_conan_version = ">=2.28"


class TgBotCppConan(ConanFile):
    name = "tgbot-cpp"
    package_type = "library"
    license = "MIT"
    url = "https://github.com/reo7sp/tgbot-cpp"
    description = "C++ library for the Telegram Bot API"

    settings = "os", "arch", "compiler", "build_type"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_tests": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "with_tests": False,
    }

    exports_sources = (
        "CMakeLists.txt",
        "LICENSE",
        "cmake/*",
        "include/*",
        "src/*",
        "tests/*",
    )

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def requirements(self):
        self.requires("boost/1.91.0", options={"header_only": True}, transitive_headers=True)
        self.requires("libcurl/8.21.0", transitive_headers=True, transitive_libs=True)
        self.requires("nlohmann_json/3.12.0", transitive_headers=True)

    def build_requirements(self):
        if self.options.with_tests:
            self.test_requires("gtest/1.17.0")

    def validate(self):
        check_min_cppstd(self, 20)

    def layout(self):
        cmake_layout(self)

    def generate(self):
        dependencies = CMakeDeps(self)
        dependencies.generate()

        toolchain = CMakeToolchain(self)
        toolchain.variables["ENABLE_TESTS"] = bool(self.options.with_tests)
        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if self.options.with_tests:
            cmake.ctest(cli_args=["--output-on-failure"])

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(
            self,
            "LICENSE",
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "licenses"),
        )
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))

    def package_info(self):
        self.cpp_info.libs = ["TgBot"]
        if self.options.shared:
            self.cpp_info.defines.append("TGBOT_DLL")
        if self.settings.os == "Windows":
            self.cpp_info.defines.extend(["_WIN32_WINNT=0x0601", "WIN32_LEAN_AND_MEAN", "NOMINMAX"])
            if not self.options.shared:
                self.cpp_info.system_libs.append("ws2_32")
        self.cpp_info.set_property("cmake_file_name", "TgBot")
        self.cpp_info.set_property("cmake_target_name", "TgBot::TgBot")
