
def isvalid(string, pattern):
    i, j = 0, 0

    while i < len(string) and j < len(pattern):
        if pattern[j] == '*':
            return isvalid(string[i:], pattern[j+1:]) or isvalid(string[i+1:], pattern[j:])

        if pattern[j] == '?' or pattern[j] == string[i]:
            i += 1
            j += 1
        else:
            return False

    if i < len(string):
        return False

    while j < len(pattern):
        if pattern[j] == '*':
            j += 1
        else:
            return False 
    return True 


tests = {
    ("aabbc","*b?c"): True,
    ("aabbc","*"): True,    
    ("aabbc","abc"): False,
    ("aabbc","***a"): False,
    ("","*"): True,
    ("aabbc","aabbc*"): True,
    ("aabbc",""): False,
    ("aabbc","abbc*"): False,
}

for (string, pattern), res in tests.items():
    print(isvalid(string, pattern))
    assert isvalid(string, pattern) == res