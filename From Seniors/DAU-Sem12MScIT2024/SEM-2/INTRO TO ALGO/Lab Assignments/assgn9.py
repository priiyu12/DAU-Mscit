import time
import matplotlib.pyplot as plt

# Naive string matching algorithm
def naive_string_match(text, pattern):
    n = len(text)
    m = len(pattern)
    occurrences = []

    for i in range(n - m + 1):
        match = True
        for j in range(m):
            if text[i + j] != pattern[j]:
                match = False
                break
        if match:
            occurrences.append(i)

    return occurrences

with open("D:\DAIICT\SEM-2\INTRO TO ALGO\Lab Assignments\\assignment9.txt", 'r', encoding='utf-8') as f:
    text = f.read()



# Patterns
patterns = [
    "the",  
    "Sherlock",  
    "Elephant42",
    "Mr. Sherlock Holmes, I believe?",  
    "was a man of untidy habits",  
    "Holmes never drank pineapple juice",
    "sdfghjkiuytredfvbnmuytrdfghjkmnbfdxcvbnmk uytrfertyuioiuygfdsertyhjmkiuygfdertyu jhgyujklkijuhgf",
    "“What a woman—oh, what a woman!” cried the King of Bohemia, when we had all three read this epistle. “Did I not tell you how quick and resolute she was? Would she not have made an admirable queen? Is it not a pity that she was not on my level?”"   
]


results = []
times = []

for pattern in patterns:
    start_time = time.time()
    occurrences = naive_string_match(text, pattern)
    elapsed_time = time.time() - start_time
    times.append(elapsed_time)
    results.append((pattern, len(pattern), len(occurrences), elapsed_time))


print(f"{'Pattern':<40} {'m':<5} {'Matches':<10} {'Time (s)':<10}")
print("-" * 70)
for pattern, m, count, elapsed in results:
    print(f"{pattern[:35]:<40} {m:<5} {count:<10} {elapsed:<10.6f}")


pattern_lengths = [len(p) for p in patterns]
plt.figure(figsize=(10, 6))
plt.plot(pattern_lengths, times, marker='o', linestyle='-', color='b')
plt.title("Naive String Matching: Pattern Length vs Running Time")
plt.xlabel("Pattern Length (m)")
plt.ylabel("Running Time (seconds)")
plt.grid(True)
plt.show()
