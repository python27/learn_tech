def average(values):
    """Compute the average arithmetic mean of a list numbers.

    >>> print average([20,30,70])
    40.0
    """
    return sum (values,0.0) / len(values)

if __name__ == "__main__":
    import doctest
    doctest.testmod()
