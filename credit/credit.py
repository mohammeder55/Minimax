from sys import argv
import ctypes as ct

companies = ["AMEX", "MASTERCARD", "VISA", "INVALID"]

j = ct.CDLL(argv[1])

a = int(argv[2])


print(
    companies[j.credit(
        ct.c_long(a)
    )]
)
