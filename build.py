#!/usr/bin/env python
# -*- coding: utf-8 -*-
from cpt.packager import ConanMultiPackager


if __name__ == "__main__":
    builder = ConanMultiPackager(
        username="reo7sp",
        login_username="reo7sp",
        upload="https://api.bintray.com/conan/reo7sp/tgbot-cpp", 
        channel="ci",
        stable_branch_pattern="release/*",
        upload_only_when_stable=True,  # Will only upload when the branch matches "release/*"
        docker_32_images=True
    )
    builder.add_common_builds()
    builder.run()
