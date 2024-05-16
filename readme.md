# OpenSBI Artifact

This repository automates the build of [OpenSBI](https://github.com/riscv-software-src/opensbi/) for the purpose of generating artifacts that can be use for integration tests in the Mirage project.

## How to release new artifacts

Create a new tag and push it to upstream, e.g.:

```sh
git tag v0.1.0
git push origin v0.1.0
```

