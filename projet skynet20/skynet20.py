#!/usr/bin/python3.5.2
# coding: utf-8

from Sources.python.RNL_type import RNL

print("Version pre Alpha 0.0.0\n")

reseau1=RNL()

if reseau1._import("rnl.data.bin"):
	print ("in: ",reseau1.rnl_data)
	for I in reseau1.rnl_data[-1]:
		print ("out: ",I)
	reseau1._export("rnl2.data.bin")
	print ("size: ",reseau1.size())
