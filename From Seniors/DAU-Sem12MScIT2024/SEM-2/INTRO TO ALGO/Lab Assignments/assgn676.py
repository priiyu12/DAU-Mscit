import mysql.connector
import random
import time
import matplotlib.pyplot as plt
import heapq

DB_CONFIG = {
    "host": "localhost",
    "user": "root",
    "password": "harsh1910",
    "database": "graphs",
    "port": 3307,
}

def connect_db():
    return mysql.connector.connect(**DB_CONFIG)

def create_tables():
    conn = connect_db()
    cursor = conn.cursor()
    
    # Drop tables to clean up old data
    cursor.execute("DROP TABLE IF EXISTS EDGES")
    cursor.execute("DROP TABLE IF EXISTS VERTICES")

    cursor.execute("CREATE TABLE VERTICES (VERTEX_NUMBER INT PRIMARY KEY)")
    cursor.execute("""
        CREATE TABLE EDGES (
            FROM_V INT,
            TO_V INT,
            PRIMARY KEY (FROM_V, TO_V),
            INDEX idx_from_v (FROM_V),   
            INDEX idx_to_v (TO_V)       
        )
    """)

    conn.commit()
    cursor.close()
    conn.close()
    print("Tables created successfully!")

def generate_random_graph(n, probability=0.3):
    #Random Graph
    conn = connect_db()
    cursor = conn.cursor()

    cursor.execute("DELETE FROM EDGES")
    cursor.execute("DELETE FROM VERTICES")

    # Insert vertices
    cursor.executemany("INSERT INTO VERTICES (VERTEX_NUMBER) VALUES (%s)", [(i,) for i in range(1, n + 1)])

    # Generate edges
    edges = [(j, k) for j in range(1, n + 1) for k in range(1, n + 1) if j != k and random.random() < probability]

    
    cursor.executemany("INSERT INTO EDGES (FROM_V, TO_V) VALUES (%s, %s)", edges)
    
    conn.commit()
    cursor.close()
    conn.close()
    print(f"Generated random directed graph with {n} vertices and {len(edges)} edges.")

def fetch_graph_from_db():
    
    conn = connect_db()
    cursor = conn.cursor()

    cursor.execute("SELECT FROM_V, TO_V FROM EDGES")
    edges = cursor.fetchall()

    graph = {}
    for u, v in edges:
        if u not in graph:
            graph[u] = []
        graph[u].append(v)

    cursor.close()
    conn.close()
    return graph

def depth_first_search(graph, start):
    
    visited = set()
    stack = [start]

    while stack:
        node = stack.pop()
        if node not in visited:
            visited.add(node)
            stack.extend(graph.get(node, []))

    return visited

def fetch_weighted_graph_from_db():
    conn = connect_db()
    cursor = conn.cursor()

    cursor.execute("SELECT FROM_V, TO_V FROM EDGES")
    edges = cursor.fetchall()

    graph = {}
    for u, v in edges:
        weight = random.randint(1, 100)
        if u not in graph:
            graph[u] = []
        if v not in graph:
            graph[v] = []
        graph[u].append((v, weight))
        graph[v].append((u, weight))  # Undirected graph for Prim’s Algorithm

    cursor.close()
    conn.close()
    return graph

def prims_algorithm(graph, start):
    mst = []
    visited = set([start])
    min_heap = []

    for to, cost in graph.get(start, []):
        heapq.heappush(min_heap, (cost, start, to))

    while min_heap:
        cost, frm, to = heapq.heappop(min_heap)
        if to not in visited:
            visited.add(to)
            mst.append((frm, to, cost))

            for next_to, next_cost in graph.get(to, []):
                if next_to not in visited:
                    heapq.heappush(min_heap, (next_cost, to, next_to))

    return mst

def compare_algorithms():
    sizes = [10, 50, 100, 500, 1000]
    dfs_times = []
    prims_times = []

    for n in sizes:
        generate_random_graph(n)

        graph = fetch_graph_from_db()

        # Measure DFS execution time
        start_time = time.time()
        depth_first_search(graph, 1)
        dfs_times.append(time.time() - start_time)

        # Fetch graph for Prim’s Algorithm
        weighted_graph = fetch_weighted_graph_from_db()

        # Measure Prim’s execution time
        start_time = time.time()
        prims_algorithm(weighted_graph, 1)
        prims_times.append(time.time() - start_time)

    # Plotting of graph
    plt.figure(figsize=(10, 6))
    plt.plot(sizes, dfs_times, marker='o', linestyle='-', color='red', label="DFS")
    plt.plot(sizes, prims_times, marker='s', linestyle='--', color='blue', label="Prim's Algorithm")

    plt.xlabel("Number of Vertices")
    plt.ylabel("Execution Time (s)")
    plt.title("Performance Comparison: DFS vs Prim's Algorithm ")
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    create_tables()
    compare_algorithms()
