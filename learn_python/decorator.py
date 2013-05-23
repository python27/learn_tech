def foo():
    print("I am foo function")

def decorator(func):
    print func.__name__
    return func

foo = decorator(foo)
