from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout


class TgBotCppConan(ConanFile):
    required_conan_version = ">=2.0"
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
        self.requires("boost/1.91.0", options={"header_only": True})
        self.requires("nlohmann_json/3.12.0")
        self.requires("libcurl/8.21.0")
        if self.options.with_tests:
            self.requires("gtest/1.17.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        dependencies = CMakeDeps(self)
        dependencies.generate()

        toolchain = CMakeToolchain(self)
        toolchain.variables["BUILD_SHARED_LIBS"] = bool(self.options.shared)
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

    def package_info(self):
        self.cpp_info.libs = ["TgBot"]
        if self.options.shared:
            self.cpp_info.defines.append("TGBOT_DLL")
        self.cpp_info.set_property("cmake_file_name", "TgBot")
        self.cpp_info.set_property("cmake_target_name", "TgBot::TgBot")
