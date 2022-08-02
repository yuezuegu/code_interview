


# S=x^0 + x + x^2 + x^3 + x^4 + ... + x^N


# (x^2 + x + 1) = x^3 - 1 / (x - 1)

# x^(N+1) - 1

#x^4 = x^2 * x^2
#x^6 = x^4 * x^2
#





def power(x, N):
    if N < 1:
        return 1

    if N%2 == 0:
        return power(x*x, N/2)
    else:
        return power(x*x, (N-1)/2)*x

def func1(x, N):
    if x == 1:
        return N+1
    return (power(x, (N+1)) - 1) / (x - 1)



def func2(x, N):
    # N > 1

    #init s = 1
    s = 1

    #init interval = 1
    midval = 1

    #loop from 1 to N
    for i in range(1, N+1):
        #interval *= x
        midval = midval * x

        #Update sum
        s += midval

    return s

#print(power(3,3))


x = 3
N = 3

print(func1(x, N))