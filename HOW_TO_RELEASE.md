# Instructions for publishing release

1. Create release on GitHub. Name git tag like "v1.x".
2. Run `git pull --tags`.
3. Run `make docs-publish`.
4. Run `make docker-push`.
5. Run `make conan-publish`.
