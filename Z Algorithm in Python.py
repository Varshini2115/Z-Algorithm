def get_Z_array(string):
    n = len(string)
    Z = [0] * n
    L = R = 0
    for i in range(1, n):
        if i > R:
            L = R = i
            while R < n and string[R - L] == string[R]:
                R += 1
            Z[i] = R - L
            R -= 1
        else:
            k = i - L
            if Z[k] < R - i + 1:
                Z[i] = Z[k]
            else:
                L = i
                while R < n and string[R - L] == string[R]:
                    R += 1
                Z[i] = R - L
                R -= 1
    return Z

def search(text, pattern):
    concat = pattern + "$" + text
    Z = get_Z_array(concat)
    pattern_len = len(pattern)
    for i in range(len(Z)):
        if Z[i] == pattern_len:
            print("Pattern found at index", i - pattern_len - 1)

def main():
    with open("text.txt", "r") as text_file, open("pattern.txt", "r") as pattern_file:
        text = text_file.readline().rstrip("\n")
        pattern = pattern_file.readline().rstrip("\n")
        search(text, pattern)

if __name__ == "__main__":
    main()
