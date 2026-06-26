# ACPICA Getting Started

This guide helps both humans and AI agents get productive quickly.

## What ACPICA provides

1. ACPICA is an open-source ACPI implementation in C.
2. It includes the iASL compiler and related ACPI tools.
3. Source packages are provided for Windows and UNIX environments.

For project overview and downloads, see `https://www.acpica.org`.

## Prerequisites

Install these core tools first:

1. `git`
2. A C compiler (`gcc`, `clang`, or MSVC)
3. Build tools (`make`; optional `cmake` for related workflows)
4. `flex`
5. `bison`

Recommended account/tooling:

1. A GitHub account
2. Optional: GitHub CLI (`gh`) for PR/issue workflows
3. Optional: VS Code with GitHub Copilot

## Environment setup examples

Choose your preferred environment and install equivalent packages.

### Ubuntu or Debian

```bash
sudo apt update
sudo apt install -y git build-essential bison flex cmake
```

### Fedora

```bash
sudo dnf install -y git gcc gcc-c++ make bison flex cmake
```

### Arch Linux

```bash
sudo pacman -S --needed git base-devel bison flex cmake
```

### macOS (Homebrew)

```bash
brew install git bison flex cmake
```

### Windows

Use one of these approaches:

1. Visual Studio toolchain and project files under `generate/msvc*`.
2. WSL for Linux-like build flow.
3. MSYS2 or similar Unix-like shell environment for Make-based builds.

## Clone and build

```bash
git clone https://github.com/acpica/acpica.git
cd acpica
make -j"$(nproc)"
```

If `nproc` is not available, use a fixed parallel value such as `-j8`.

Typical binaries are created under `generate/unix/bin`.

## Basic validation

1. Ensure build completes without new errors.
2. For table compiler/disassembler changes, run template round trip:
   ASL to AML to DSL to AML.
3. Compare output binaries and include results in PR notes.

See `docs/testing.md` for additional guidance.

## Reporting issues

Use GitHub Issues:

1. `https://github.com/acpica/acpica/issues`
2. Include environment, commit SHA, reproducer, and expected behavior.
3. Include logs and table artifacts when relevant.

## Submitting pull requests

1. Create a topic branch from `master`.
2. Keep changes focused and minimal.
3. Build and run relevant validation.
4. Write clear commit messages with verification notes.
5. Open a PR against `master`.

See `CONTRIBUTING.md` and `docs/pr-workflow.md`.

## Discussions and project links

1. ACPICA discussions: `https://github.com/acpica/acpica/discussions`
2. ACPICA homepage and downloads: `https://www.acpica.org`

## GitHub Copilot usage

Copilot access depends on your account and organization policy.

1. Install VS Code and GitHub Copilot extension.
2. Sign in with your GitHub account.
3. Open this repository in VS Code.
4. Follow repository docs for style, validation, and workflow.

Note: Some users may see organization-provided Copilot access messaging on
GitHub. Availability is account and org-policy dependent.
