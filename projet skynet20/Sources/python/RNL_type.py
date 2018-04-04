#!/usr/bin/python3.5.2
# coding: utf-8

import struct
import sys

class RNL:
	def __init__(self):
		self.rnl_data=[]

	def push_back_layer(self,layer=list):
		self.rnl_data.append(layer)

	def size(self):
		return self.rnl_data.__len__()

	def clear(self):
		self.rnl_data.clear();

	def _export(self,file=str):
		try:
			with  open(file, "wb") as If:

				s = struct.Struct("<i")
				size_int=[int(len(self.rnl_data))]
				size_network = s.pack(*size_int)
				If.write(size_network)

				for dat in self.rnl_data:
					s = struct.Struct("<i")
					size_int=[int(len(dat))]
					size_network = s.pack(*size_int)
					If.write(size_network)

					s = struct.Struct("<"+"f"*int(len(dat)))
					layer = s.pack(*dat)
					If.write(layer)
			return 1
		except IOError as e:
			print("IOError({0}): {1}".format(e.errno, e.strerror))
			return 0
		except ValueError:
			print ("Could not convert data")
			return 0
		except:
			print ("Unexpected error:", sys.exc_info())
			return 0
		return 0

	def _import(self,file=str):
		self.clear();

		try:
			with  open(file, "rb") as Of:
				s = struct.Struct("<i")
				value_int=Of.read(4)
				size_network = int(s.unpack(value_int)[0])

				i=0
				while i<size_network:
					s = struct.Struct("<i")
					value_int=Of.read(4)
					size_layer = int(s.unpack(value_int)[0])

					s = struct.Struct("<"+"f"*size_layer)
					value_data=Of.read(4*size_layer)
					self.rnl_data.append(list(s.unpack(value_data)))
					i+=1
			return 1
		except IOError as e:
			print("IOError({0}): {1}".format(e.errno, e.strerror))
			return 0
		except ValueError:
			print ("Could not convert data")
			return 0
		except:
			print ("Unexpected error:", sys.exc_info())
			return 0
		return 0

