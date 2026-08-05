# Instructions for publishing release

1. Create release on GitHub. Name git tag like "v1.x".
2. Run `make docs-publish`.
3. Run `make docker-push`.
4. Run `make conan-publish`.
