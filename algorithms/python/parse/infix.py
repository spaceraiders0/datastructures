#!/usr/bin/env python

"""This is an Infix parser implemented in Python.

Infix is our standard mathematical notation. For example:
1 + 2 * (9 / 3)

In this equation, the expressions in the () would go first, and everything
else would be evaluated.
"""

import re

operators = {
    "*": lambda l, r: l * r,
    "/": lambda l, r: l / r,
    "+": lambda l, r: l + r,
    "-": lambda l, r: l - r,
}


def collect(expression: str, pair_a: str, pair_b: str) -> list:
    unmatched_pairs = []
    matched = []

    for index in range(len(expression)):
        character = expression[index]

        if character == pair_a:
            unmatched_pairs.insert(0, index)
        elif character == pair_b:
            matched.append((unmatched_pairs.pop(0), index))

    return matched


def get_operands(expression: str, index: int) -> [tuple, tuple]:
    left_operand = ""
    right_operand = ""
    last_character = ""

    for char_index, character in enumerate(expression):
        if character == "-":
            # If this new character is an operator, and - , that means that the
            # following number is a negative number.
            if last_character in operators:
                # Decide which operand this should be in.
                if char_index < index:
                    left_operand += "-"
                elif char_index > index:
                    right_operand += "-"
        else:
            # Reset left_operand unless the index is the operand we
            # are looking for.
            if character in operators:
                print(left_operand)
                if char_index != index:
                    left_operand = ""
            else:
                if char_index < index:
                    left_operand += character
                elif char_index > index:
                    right_operand += character

        print(f"Left Operand: {left_operand}")
        print(f"Right Operand: {right_operand}\n")

        last_character = char_index

    return left_operand, right_operand

def parse_expression(expression: str) -> float:
    expression = re.sub("\s*", "", expression)
    parenthesis = collect(expression, "(", ")")

    # Parses parenthesis
    while len(parenthesis) > 0:
        # This handles any sub-parenthesis inside these parenthesis.
        parenthesis_start, parenthesis_end = parenthesis.pop(0)
        inner_expression = expression[parenthesis_start + 1:parenthesis_end]
        inner_result = parse_expression(inner_expression)

        # Get the left and right sides of the expression in parenthesis
        # so the result can be replaced in between them.
        full_left_side = expression[:parenthesis_start]
        full_right_side = expression[parenthesis_end + 1:]

        # Builds the final evaluated parenthesis-less expression
        expression = full_left_side + str(inner_result) + full_right_side
        parenthesis = collect(expression, "(", ")")

    # Parses operators until there exists no more of a specific operator.
    for operator, behavior in operators.items():
        operator_index = expression.find(operator)

        while operator_index >= 0:
            # Handles negative numbers since expressions (even sub-expressions)
            # should not have a leading operator of any kind.
            if expression.startswith("-") is True:
                break

            left, right, start, stop = get_operands(expression, operator_index)
            left_side, right_side = expression[:start], expression[stop:]
            result = str(behavior(left, right))
            expression = left_side + result + right_side

            operator_index = expression.find(operator)

    return int(expression)


if __name__ == "__main__":
    # expression = "((1 + 5 * (5 + 2))) + 58 * (43 * 2)"
    expression = "1+-1-2"
    # result = parse_expression(expression)

    # print(f"The result of {expression} is {result}.")
    print(get_operands("14232+-1-2", 1))
