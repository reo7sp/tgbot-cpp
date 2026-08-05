from __future__ import annotations

import argparse
from pathlib import Path

from api_codegen import generate, update

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SCHEMA = ROOT / "api" / "telegram-bot-api.yaml"


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)
    update_parser = subparsers.add_parser("update", help="download Telegram Bot API docs and create OpenAPI schema")
    update_parser.add_argument("--output", type=Path, default=DEFAULT_SCHEMA)
    generate_parser = subparsers.add_parser("generate", help="generate C++ types, API methods and JSON codecs")
    generate_parser.add_argument("--schema", type=Path, default=DEFAULT_SCHEMA)
    args = parser.parse_args()

    if args.command == "update":
        update.run(args.output)
        return

    generate.run(args.schema, ROOT)


if __name__ == "__main__":
    main()
