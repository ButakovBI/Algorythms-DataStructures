import math


def round_up(value: float, precision: int = 0) -> float:
    """
    Округляет значение вверх до заданного количества значащих цифр.
    Пример: round_up(123.123, 2) -> 123.13

    :param value: Значение, которое нужно округлить.
    :param precision: Количество значащих цифр для округления.
                      Если precision отрицательный, округление производится
                      на заданное количество разрядов влево
                      от десятичной точки. Если precision > 0 и
                      превышает длину числа, значение возвращается
                      без изменений. Если precision < 0 и превышает длину
                      числа, возвращается 0.
                      Реализация аналогична round из стандартной библиотеки.

    :return: Значение, округленное вверх до указанного
             количества значащих цифр.
    """
    integer_part = str(value).split('.')[0]
    current_precision = len(integer_part)

    if precision < 0 and abs(precision) > current_precision:
        res = 0.0
    elif precision > 0 and precision > current_precision:
        res = value
    else:
        res = math.ceil(value * (10 ** precision)) / (10 ** precision)

    return res
