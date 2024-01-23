# Apache License 2.0

import pytest

from ostk.core.type import Sign


def test_sign_enum():
    sign_pos = Sign.Positive
    sign_neg = Sign.Negative
    sign_undef = Sign.Undefined
    sign_no = Sign.NoSign

    enum_members = Sign.__members__
    assert list(enum_members.keys()) == ["Undefined", "Positive", "Negative", "NoSign"]
    assert list(enum_members.values()) == [
        Sign.Undefined,
        Sign.Positive,
        Sign.Negative,
        Sign.NoSign,
    ]
