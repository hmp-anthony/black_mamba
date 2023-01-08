import black_mamba as bm
from black_mamba import Var, gradient


# Exponentiation
x = Var(2)
y = Var(5)

ln_ = bm.ln() 

z_1 = ln_(x)

print(z_1)
print(gradient(z_1, x))

log_b_ = bm.log(5) 

z_2 = log_b_(y)

print(z_2)
print(gradient(z_2, y))
