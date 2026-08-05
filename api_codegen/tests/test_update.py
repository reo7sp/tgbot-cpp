from pathlib import Path
from subprocess import CompletedProcess

from api_codegen import update


def test_run_invokes_tgbotspec_with_resolved_output_in_temporary_directory(
    tmp_path: Path, monkeypatch
) -> None:
    output_path = tmp_path / "api" / "telegram-bot-api.yaml"
    invocation = {}

    def run(command, *, cwd, check):
        invocation["command"] = command
        invocation["cwd"] = Path(cwd)
        invocation["cwd_existed"] = Path(cwd).is_dir()
        invocation["check"] = check

        return CompletedProcess(command, 0)

    monkeypatch.setattr(update.subprocess, "run", run)

    update.run(output_path)

    assert invocation["command"] == [
        "tgbotspec",
        "--output",
        str(output_path.resolve()),
    ]
    assert invocation["cwd_existed"] is True
    assert invocation["check"] is True
    assert not invocation["cwd"].exists()
    assert output_path.parent.is_dir()
