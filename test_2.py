import black_mamba as bm
from black_mamba import Var, gradient


# Exponentiation
x = Var(2)
y = Var(5)

z = x ** y

print(z)			# 32
print(gradient(z, x))	# 80
print(gradient(z, y))	# 22.18070977791825
