import sys
from pathlib import Path

from api_codegen import main


def test_main_routes_generate_command(monkeypatch, tmp_path: Path) -> None:
    schema_path = tmp_path / "schema.yaml"
    invocation = {}
    monkeypatch.setattr(
        main.generate,
        "run",
        lambda schema, root: invocation.update(schema=schema, root=root),
    )
    monkeypatch.setattr(
        sys,
        "argv",
        ["api-codegen", "generate", "--schema", str(schema_path)],
    )

    main.main()

    assert invocation == {"schema": schema_path, "root": main.ROOT}


def test_main_routes_update_command(monkeypatch, tmp_path: Path) -> None:
    output_path = tmp_path / "schema.yaml"
    invocation = {}
    monkeypatch.setattr(
        main.update,
        "run",
        lambda output: invocation.update(output=output),
    )
    monkeypatch.setattr(
        sys,
        "argv",
        ["api-codegen", "update", "--output", str(output_path)],
    )

    main.main()

    assert invocation == {"output": output_path}
