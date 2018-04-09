#!/usr/bin/python3.5.2
# coding: utf-8

def Factorielle(I=int):
	if I > 0:
		return float(I) * Factorielle(I-1)
	else:
		return 1.0

def Puissance(x=float,N=int):
	if N > 0:
		return x * Puissance(x,N-1)
	else:
		return 1.0

def Exp_(I=int,x=float):
	if I>=0:
		return Exp_(I-1,x) + Puissance(x,I) / Factorielle(I)
	else:
		return 0.0

def Exponentielle(x=float,N=int):
	if x < 0.0:
		return 1.0/Exp_(N,-x) 
	else:
		return Exp_(N,x)


if __name__ == '__main__':
	print("exponnatiel<1,10>: ",Exponentielle(1,10))
	print("pow<2,10>: ",Puissance(2,10))
	print("factoriel<6>: ",Factorielle(6))

