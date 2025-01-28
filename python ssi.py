import math

def read_coordinates(filepath):
    """
    Reads a set of 2D coordinates from a text file where each line contains:
        x_coordinate,y_coordinate
    Returns:
        A list of (x, y) tuples.
    """
    coords = []
    with open(filepath, 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            x_str, y_str = line.split(',')
            x, y = float(x_str), float(y_str)
            coords.append((x, y))
    return coords

def build_distance_matrix(coords):
    """
    Given a list of (x, y) coordinate tuples, returns the distance matrix
    dist[i][j] = Euclidean distance between coords[i] and coords[j].
    """
    n = len(coords)
    dist_matrix = [[0.0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if i == j:
                dist_matrix[i][j] = 0.0
            else:
                dx = coords[i][0] - coords[j][0]
                dy = coords[i][1] - coords[j][1]
                dist_matrix[i][j] = math.sqrt(dx*dx + dy*dy)
    return dist_matrix

def smallest_sum_insertion(dist_matrix):
    """
    Implements the Smallest Sum Insertion heuristic for the TSP.
    Steps:
        1. Start with the lowest-index vertex in the tour.
        2. Find an unvisited vertex that has the minimal sum of distances
           to all vertices in the partial tour.
        3. Insert that vertex into the best position in the tour, i.e., the
           position yielding the minimal increase in tour cost.
        4. Repeat until all vertices are visited.

    Returns:
        A list of vertices representing the tour in visiting order.
    """
    n = len(dist_matrix)
    
    # 1. Initialize partial tour with vertex 0.
    partial_tour = [0]
    visited = set([0])
    
    # 2. While there are unvisited vertices, select the one with smallest sum of distances to partial tour.
    while len(visited) < n:
        best_vertex = None
        best_sum = float('inf')
        
        # Find the vertex with the minimal sum of distances to the partial tour
        for v in range(n):
            if v not in visited:
                sum_dist = sum(dist_matrix[t][v] for t in partial_tour)
                if sum_dist < best_sum:
                    best_sum = sum_dist
                    best_vertex = v
        
        # 3. Determine the best insertion position for 'best_vertex'
        best_insertion_cost = float('inf')
        best_position = None
        
        # Treat the partial tour as a cycle: 
        #   for index i, consider inserting best_vertex between partial_tour[i] and partial_tour[(i+1) % length].
        for i in range(len(partial_tour)):
            curr_v = partial_tour[i]
            next_v = partial_tour[(i + 1) % len(partial_tour)]
            # Insertion cost Δ = dist[curr_v][best_vertex] + dist[best_vertex][next_v] - dist[curr_v][next_v]
            insertion_cost = (dist_matrix[curr_v][best_vertex]
                              + dist_matrix[best_vertex][next_v]
                              - dist_matrix[curr_v][next_v])
            if insertion_cost < best_insertion_cost:
                best_insertion_cost = insertion_cost
                best_position = i + 1
        
        # Insert the new vertex in the position that yields the minimal insertion cost
        partial_tour.insert(best_position, best_vertex)
        visited.add(best_vertex)
    
    return partial_tour

def compute_tour_length(tour, dist_matrix):
    """
    Computes the total distance of the tour (in cycle form).
    That is, sums dist[i][i+1] for i from 0 to len(tour)-1,
    plus dist[last_vertex][first_vertex].
    """
    length = 0.0
    for i in range(len(tour)):
        j = (i + 1) % len(tour)
        length += dist_matrix[tour[i]][tour[j]]
    return length

def main():
    # Example usage:
    filepath = 'coordinates.txt'  # Replace with the path to your coordinate file
    coords = read_coordinates(filepath)
    
    # Build distance matrix
    dist_matrix = build_distance_matrix(coords)
    
    # Solve TSP using Smallest Sum Insertion
    tour = smallest_sum_insertion(dist_matrix)
    
    # Compute and display the total tour length
    length = compute_tour_length(tour, dist_matrix)
    
    print("Tour:", tour)
    print("Total distance:", length)

if __name__ == "__main__":
    main()

