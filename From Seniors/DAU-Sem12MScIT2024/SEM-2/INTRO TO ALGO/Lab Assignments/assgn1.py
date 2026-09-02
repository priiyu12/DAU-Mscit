import random
import time
import matplotlib.pyplot as plt

# Generate Random No.
def generate_random_numbers(filename, N):
    with open(filename, "w") as f:
        for _ in range(N):
            f.write(f"{random.randint(1, 10**30)}\n")

# Read Nos
def read_numbers_from_file(filename):
    with open(filename, "r") as f:
        return [int(line.strip()) for line in f]

#Write Nos
def write_numbers_to_file(filename, numbers):
    with open(filename, "w") as f:
        for number in numbers:
            f.write(f"{number}\n")

# Insertion Sort
def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

# Merge Sort
def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]

        merge_sort(L)
        merge_sort(R)

        i = j = k = 0

        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

# Runtime Calculation
def measure_runtime(sort_function, arr):
    start_time = time.time()
    sort_function(arr)
    end_time = time.time()
    return end_time - start_time

# Main script
Ns = [100, 1000, 2000, 5000, 10000, 20000]  # Sizes of input
insertion_sort_times = []
merge_sort_times = []

for N in Ns:
    input_file = f"input_{N}.txt"
    output_file_insertion = f"output_insertion_{N}.txt"
    output_file_merge = f"output_merge_{N}.txt"

    generate_random_numbers(input_file, N)

    numbers = read_numbers_from_file(input_file)

    numbers_copy = numbers[:]
    time_taken = measure_runtime(insertion_sort, numbers_copy)
    insertion_sort_times.append(time_taken)
    write_numbers_to_file(output_file_insertion, numbers_copy)

    numbers_copy = numbers[:]
    time_taken = measure_runtime(merge_sort, numbers_copy)
    merge_sort_times.append(time_taken)
    write_numbers_to_file(output_file_merge, numbers_copy)

# Plotting of graph
plt.figure(figsize=(10, 6))
plt.plot(Ns, insertion_sort_times, label="Insertion Sort", marker="o")
plt.plot(Ns, merge_sort_times, label="Merge Sort", marker="s")
plt.xlabel("Input Size (N)")
plt.ylabel("Runtime (seconds)")
plt.title("Comparison of Insertion Sort and Merge Sort")
plt.legend()
plt.grid(True)
plt.show()
