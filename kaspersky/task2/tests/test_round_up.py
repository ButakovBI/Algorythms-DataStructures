from helpers import round_up


def test_round_up_int_positive_or_zero_basic():
    assert round_up(0, 0) == 0
    assert round_up(0, 3) == 0
    assert round_up(12345, 0) == 12345
    assert round_up(12345, 3) == 12345


def test_round_up_int_negative_basic():
    assert round_up(-12345, 0) == -12345
    assert round_up(-12345, 3) == -12345


def test_round_up_positive_or_zero_int_negative_precision():
    assert round_up(0, -3) == 0
    assert round_up(12345, -1) == 12350
    assert round_up(12345, -2) == 12400
    assert round_up(12345, -4) == 20000
    assert abs(round_up(12345, -5) - 100000) < 1e-6


def test_round_up_negative_int_negative_precision():
    assert round_up(-12345, -1) == -12340
    assert round_up(-12345, -2) == -12300
    assert round_up(-12345, -4) == -10000
    assert abs(round_up(-12345, -5) - 0) < 1e-6


def test_round_up_negative_int_positive_precision():
    assert round_up(0, 3) == 0
    assert round_up(-12345, 1) == -12345
    assert round_up(-12345, 2) == -12345
    assert round_up(-12345, 5) == -12345


def test_round_up_positive_float_positive_precision():
    assert abs(round_up(12.345, 0) - 13) < 1e-6
    assert abs(round_up(12.345, 1) - 12.4) < 1e-6
    assert abs(round_up(12.345, 2) - 12.35) < 1e-6
    assert abs(round_up(12.345, 3) - 12.345) < 1e-6
    assert abs(round_up(12.345, 4) - 12.345) < 1e-6
    assert abs(round_up(12.345, 15) - 12.345) < 1e-6
    assert abs(round_up(12.345, 1514124) - 12.345) < 1e-6


def test_round_up_negative_float_positive_precision():
    assert abs(round_up(-12.345, 0) - (-12)) < 1e-6
    assert abs(round_up(-12.345, 1) - (-12.3)) < 1e-6
    assert abs(round_up(-12.345, 2) - (-12.34)) < 1e-6
    assert abs(round_up(-12.345, 3) - (-12.345)) < 1e-6
    assert abs(round_up(-12.345, 4) - (-12.345)) < 1e-6
    assert abs(round_up(-12.345, 15) - (-12.345)) < 1e-6
    assert abs(round_up(-12.345, 1514124) - (-12.345)) < 1e-6


def test_round_up_positive_float_negative_precision():
    assert abs(round_up(123.45, -1) - 130) < 1e-6
    assert abs(round_up(123.45, -2) - 200) < 1e-6
    assert abs(round_up(123.45, -3) - 1000) < 1e-6
    assert abs(round_up(123.45, -4) - 0) < 1e-6
    assert abs(round_up(123.45, -15) - 0) < 1e-6
    assert abs(round_up(123.45, -1213425) - 0) < 1e-6


def test_round_up_negative_float_negative_precision():
    assert abs(round_up(-123.45, -1) - (-120)) < 1e-6
    assert abs(round_up(-123.45, -2) - (-100)) < 1e-6
    assert abs(round_up(-123.45, -3) - 0) < 1e-6
    assert abs(round_up(-123.45, -4) - 0) < 1e-6
    assert abs(round_up(-123.45, -15) - 0) < 1e-6
    assert abs(round_up(-123.45, -1514124) - 0) < 1e-6


def test_default_precision():
    assert abs(round_up(-123.45) - (-123)) < 1e-6
    assert abs(round_up(123.45) - 124) < 1e-6
    assert abs(round_up(123) - 123) < 1e-6
