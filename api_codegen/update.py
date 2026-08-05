from __future__ import annotations

import subprocess
import tempfile
from pathlib import Path


def run(output_path: Path) -> None:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="tgbot-cpp-api-") as directory:
        subprocess.run(
            ["tgbotspec", "--output", str(output_path.resolve())],
            cwd=directory,
            check=True,
        )
