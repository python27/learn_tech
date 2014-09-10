###########################################
# Lispy: Scheme Lisp Interpreter in Python
# (C) python27, 2010
###########################################
from __future__ import division

########## Symbol, Env classes ###########
Symbol = str
isa = isinstance

class Env(dict):
    "An environment: a dict of {var:var} pairs, with an outer Env"
    def __init__(self, parms=(), args=(), outer=None):
        self.update(zip(parms, args))
        self.outer = outer
    def find(self, var):
        return self if var in self else self.outer.find(var)

def add_globals(env):
    "Add some Scheme standard procedures to an environment"
    import math, operator as op
    env.update(vars(math)) # sin sqrt ...
    env.update(
            {'+':op.add, '-':op.sub, '*':op.mul, '/':op.div, 'not':op.not_,
             '>':op.gt, '<':op.lt, '>=':op.ge, '<=':op.le, '=':op.eq,
             'equal?':op.eq, 'eq?':op.is_, 'length':len, 'cons':lambda x,y:[x]+y,
             'car':lambda x:x[0], 'cdr':lambda x:x[1:], 'append':op.add,
             'list':lambda *x:list(x), 'list?':lambda x:isa(x, list),
             'null?':lambda x:x==[], 'symbol?':lambda x:isa(x, Symbol)})
    return env

global_env = add_globals(Env())

########## Parse ##########
def tokenize(s):
    "covert a string to a list of tokens"
    return s.replace('(', ' ( ').replace(')', ' ) ').split()

def atom(token):
    "Numbers become numbers, every other token is a symbol" 
    try: return int(token)
    except ValueError:
        try: return float(token)
        except ValueError:
            return str(token)

def read_from(tokens):
    "Read an expression from a sequence of tokens"
    if len(tokens) == 0:
        raise SyntaxError("Unexpected EOF while reading")
    token = tokens.pop(0)
    if token == '(':
        L = []
        while tokens[0] != ')':
            L.append(read_from(tokens))
        tokens.pop(0)
        return L
    elif token == ')':
        raise SyntaxError("Unexpected )")
    else:
        return atom(token)

def read(s):
    "Read a Scheme expression from a string"
    return read_from(tokenize(s))

def to_string(exp):
    "Covert a Python object back to a lisp-readable string"
    return '(' + ' '.join(map(to_string, exp))+')' if isa(exp, list) else str(exp)

parse = read

########## eval ##########
def eval(x, env=global_env):
    "evaluate an expression in an environment"
    if isa(x, Symbol):      # variable reference
        return env.find(x)[x]
    elif not isa(x, list):  # constant literal
        return x
    elif x[0] == 'quote':   # (quote exp)
        (_, exp) = x
        return exp
    elif x[0] == 'if':      # (if test conseq alt)
        (_, test, conseq, alt) = x
        return eval((conseq if eval(test, env) else alt), env)
    elif x[0] == 'set!':    #(set! var exp)
        (_, var, exp) = x
        env.find(var)[var] = eval(exp, env)
    elif x[0] == 'define':  #(define var exp)
        (_, var, exp) = x
        env[var] = eval(exp, env)
    elif x[0] == 'lambda':  #(lambda (var*) exp)
        (_, myvars, exp) = x
        return lambda *args: eval(exp, Env(myvars, args, env))
    elif x[0] == 'begin':   #(begin exp*)
        for exp in x[1:]:
            var = eval(exp, env)
        return var
    else:                   #(proc exp*)
        exps = [eval(exp, env) for exp in x]
        proc = exps.pop(0)
        return proc(*exps)


######### user interface #########
def repl(prompt='lis.py> '):
    "A prompt-read-eval-print loop"
    while True:
        var = eval(parse(raw_input(prompt)))
        if var is not None: print to_string(var)
