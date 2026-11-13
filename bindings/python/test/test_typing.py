# Apache License 2.0

"""Calls that the bindings accept, and that the generated type stubs must accept too.

The bindings convert some Python values implicitly, for example a `str` where a `String`
is declared. Each test makes such a call. `test_stubs_accept_these_calls` type-checks this
file with mypy against the generated stubs, so a stub that rejects one of these calls fails.
"""

from pathlib import Path

import pytest

import ostk.core
from ostk.core.type import Integer
from ostk.core.type import Real
from ostk.core.type import String


def test_string_parameter_accepts_str() -> None:
    replicated: String = String.replicate("ab", 3)

    assert replicated == "ababab"


def test_integer_parameter_accepts_int() -> None:
    assert Integer(1) < 2


def test_real_parameter_accepts_float() -> None:
    assert Real(1.0).is_near(1.0, 0.1)


def test_stubs_accept_these_calls(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    mypy_api = pytest.importorskip("mypy.api")

    # In the CMake build tree, the package is a directory next to `test`, not an installed
    # distribution: mypy only finds it through MYPYPATH.
    package_root: Path = Path(ostk.core.__file__).resolve().parents[2]

    if package_root.name != "site-packages":
        monkeypatch.setenv("MYPYPATH", str(package_root))

    # Report the errors in the calls of this file only: the stubs themselves are not checked,
    # as for an installed package.
    config: Path = tmp_path / "mypy.ini"
    config.write_text("[mypy]\n[mypy-ostk.*]\nignore_errors = True\n")

    stdout, stderr, exit_status = mypy_api.run(
        [
            __file__,
            "--config-file",
            str(config),
            "--cache-dir",
            str(tmp_path / "mypy_cache"),
        ]
    )

    assert exit_status == 0, stdout + stderr
