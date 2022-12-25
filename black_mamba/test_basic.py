import black_mamba as bm
from black_mamba import Var, gradient


def sigmoid(x):
	exp_ = bm.exp()
	return 1 / (1 + exp_(-x))

def exp2(x):
    exp_ = bm.exp()
    return exp_(2*x)

x = Var(0.5)
z1 = sigmoid(x)
z2 = exp2(x)

def test_gradient():
    assert gradient(z1,x) == -0.6065306597126334
    assert gradient(z2,x) == 5.43656365691809 
