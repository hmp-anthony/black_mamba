import black_mamba as bm
from black_mamba import Var, gradient


# Exponentiation
x = Var(2)
y = Var(5)

z = x ** y

print(z)			# 32
print(gradient(z, x))	# 80
print(gradient(z, y))	# 22.18070977791825

# Sigmoid
def sigmoid(x):
	exp_ = bm.exp()
	return 1 / (1 + exp_(-x))

x = Var(0.5)
z = sigmoid(x)
print(z)				# 1.6065306597126334
print(gradient(z, x))	# -0.6065306597126334
