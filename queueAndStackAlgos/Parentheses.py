def check(string):
    stack = []
    for char in string:
        if char == ')' and not stack:
            return False
        elif char == '(':
            stack.append(")")
        elif stack and char == stack[-1]:
            stack.pop()
    
    return not stack
        

if __name__ == "__main__":
    import sys

    dictionary = dict()
    sentences = list()
    count = 1
    print("Enter the strings: ")
    go = True
    while go:
        line = input()
        if line == "Done":
            go = False
        else:
            sentences.append(line)
    
    for string in sentences:
        if check(string):
            dictionary[count] = string
            count += 1
    print("Solution:")
    print(dictionary)
    
