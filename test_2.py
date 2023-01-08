import black_mamba as bm
from black_mamba import Var, gradient


# Exponentiation
x = Var(2)
y = Var(5)


sin_ = bm.sin() 
cos_ = bm.cos()

z_1 = sin_(x*y) ;

print(z_1)		
print(gradient(z_1, x))	
print(gradient(z_1, y))	


z_2 = cos_(x*y) ;

print(z_2)			
print(gradient(z_2, x))	
print(gradient(z_2, y))






