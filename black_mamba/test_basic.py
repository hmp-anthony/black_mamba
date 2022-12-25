import black_mamba as bm
from black_mamba import Var, gradient


# Sigmoid
def sigmoid(x):
	exp_ = bm.exp()
	return 1 / (1 + exp_(-x))

x = Var(0.5)
z = sigmoid(x)

def test_gradient_1():
    assert gradient(z,x) == -0.6065306597126334
