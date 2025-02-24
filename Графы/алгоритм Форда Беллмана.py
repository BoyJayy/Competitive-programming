def main():
    input_file = open("input.txt", "r")
    output_file = open("output.txt", "w")
    line = input_file.readline().split()
    n, m = int(line[0]), int(line[1])
    f = []
    s = []
    w = []
    distances = []
    INF = 10 ** 100
    for i in range (m):
        line = input_file.readline().split()
        f.append(int(line[0]))
        s.append(int(line[1]))
        w.append(int(line[2]))
 
    print(f)
    print(s)
    print(w)
 
    for i in range(n):
        distances.append(INF)
 
    distances[0] = 0
    print(distances)
 
    for i in range(n-1):
        for j in range(m):
            if distances[s[j]-1] > distances[f[j]-1] + w[j] and distances[f[j]-1] != INF:
                distances[s[j]-1] = distances[f[j]-1] + w[j]
        print(distances)
 
    for i in range(n):
        if distances[i] == INF:
            distances[i] = 30000
 
    print(distances)
 
    output_file.write(str(' '.join([str(x) for x in distances])) + "\n")
    input_file.close()
    output_file.close()
 
if __name__ == "__main__":
    main()