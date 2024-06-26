
def connected(line_1, line_2):
    return line_1[0] == line_2[0] or line_1[0] == line_2[1] or line_1[1] == line_2[0] or line_1[1] == line_2[1]

#current and start strat off as the same
def search(connections, start, current, count, parent):
    if current == start and count > 2:
        return count
    elif len(connections[current]) <= 1:
        return -1
    
    #count+=1
    for child in connections[current]:
        if child != parent:
            ans = search(connections, start, child, count + 1, current)
            if ans != -1:
                return ans            
    return -1

def closed_search(connections):
    seen = set()
    track = dict()
    potential_starts = []
    start = False
    
    #check if closed is possible

    if has_start(connections, potential_starts) == False:
        return -1
    
    # find the start, and a closed shape, all points will have 2 paths
    for key, list in connections.items():
        if list and len(list) > 1:
            start = key
    
    ans = -1
    for key in potential_starts:
        ans = search(connections, start, start, 0, None) 
        if ans != -1:
            return ans
        
    return -1

# has to be more than 2 points with two lines connected to it to have a closed shape (check)
def has_start(connections, potential_starts):
    count = 0
    for key, list in connections.items():
        if list and len(list) > 1:
            count+=1
            potential_starts.append(key)
    
    return count > 2  

def build_dictionary(connections, lines):
    connected_to = list()
    for line in lines:
        u, v = line
        if u not in connections:
            connections[u] = list()
        if v not in connections: 
            connections[v] = list()  

        connections[v].append(u)
        connections[u].append(v)



if __name__ == "__main__":
    import queue

    lines = list()
    connections = dict(list())

    num_lines = int(input("Enter the number of lines: "))
    print("Enter the lines: ")

    for i in range(0,num_lines):
        line = input()
        line = line.replace('[', '')
        line = line.replace(']', '')
        line = line.split(',')
        tuple1 = tuple(line[:2])  # First two numbers
        tuple2 = tuple(line[2:])  # Last two numbers
        line   = [tuple1, tuple2]
        lines.append(line)
        
    
    build_dictionary(connections, lines)

    sides = closed_search(connections)
    if sides != -1:
        print("The lines form a closed figure with ", sides, " sides.")
    else:
        print("The lines do not form a closed figure")

    
    
    
    