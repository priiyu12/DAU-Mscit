import random
import time
import matplotlib.pyplot as plt


#Random Weighted Directed Graph
def generate_graph(n, edge_probability=0.2, max_weight=10):
    graph = [[0 for _ in range(n)] for _ in range(n)]

    for i in range(n):
        for j in range(n):
            if i != j and random.random() < edge_probability:
                graph[i][j] = random.randint(1, max_weight)

    return graph


# Dijkstra's Algorithm
def dijkstra(graph, src):
    n = len(graph)
    dist = [float('inf')] * n
    visited = [False] * n
    dist[src] = 0

    for _ in range(n):
        # Finding unvisited node 
        min_dist = float('inf')
        u = -1
        for v in range(n):
            if not visited[v] and dist[v] < min_dist:
                min_dist = dist[v]
                u = v

        if u == -1:
            break  # unreachable nodes

        visited[u] = True

        # Updating the distance of adjacent vertices
        for v in range(n):
            if graph[u][v] != 0 and not visited[v]:
                if dist[v] > dist[u] + graph[u][v]:
                    dist[v] = dist[u] + graph[u][v]

    return dist


#Running Time for Different Graph Sizes
def main():
    sizes = [10, 50, 100, 200, 300, 400, 500]
    times = []

    for n in sizes:
        graph = generate_graph(n, edge_probability=0.1)
        start_time = time.time()
        dijkstra(graph, 0)
        end_time = time.time()

        elapsed_time = end_time - start_time
        times.append(elapsed_time)
        print(f"Graph with {n} nodes took {elapsed_time:.5f} seconds")

    # Plot Graph
    plt.plot(sizes, times, marker='o')
    plt.xlabel("Number of Nodes")
    plt.ylabel("Time Taken (seconds)")
    plt.title("Dijkstra's Algorithm Running Time")
    plt.grid(True)
    plt.show()


# Driver Code
if __name__ == "__main__":
    main()
