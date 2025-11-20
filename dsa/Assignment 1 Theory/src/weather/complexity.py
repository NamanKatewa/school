from typing import Dict


def complexity_summary(mode: str, Y: int, C: int, N: int) -> Dict[str, str]:
    """
    Returns a dictionary with the complexity analysis for the given mode.

    Args:
        mode: The storage mode (dense or sparse).
        Y: The number of years.
        C: The number of cities.
        N: The number of records.

    Returns:
        A dictionary with the complexity analysis.
    """
    if mode == "dense":
        return {
            "insert": "O(1)",
            "delete": "O(1)",
            "retrieve": "O(1)",
            "space": f"O({Y} * {C})",
            "row_major_access": f"O({Y} * {C})",
            "column_major_access": f"O({Y} * {C})",
        }
    elif mode == "sparse":
        return {
            "insert": "O(1)",
            "delete": "O(1)",
            "retrieve": "O(1)",
            "space": f"O({N})",
            "row_major_access": f"O({Y} * {C})",
            "column_major_access": f"O({Y} * {C})",
        }
    else:
        raise ValueError(f"Unknown mode: {mode}")
