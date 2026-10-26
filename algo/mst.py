import matplotlib.pyplot as plt
import networkx as nx
import heapq


def draw_graph(graph, mst_edges=None):
    G = nx.Graph()

    for u in graph:
        for v, w in graph[u]:
            G.add_edge(u, v, weight=w)

    pos = nx.spring_layout(G, seed=42)

    plt.figure(figsize=(8, 6))

    nx.draw(
        G, pos,
        with_labels=True,
        node_color="lightblue",
        node_size=2000,
        font_size=12,
        font_weight="bold",
        edge_color="gray"
    )

    edge_labels = nx.get_edge_attributes(G, "weight")
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

    if mst_edges:
        mst_edge_list = [(u, v) for u, v, w in mst_edges]
        nx.draw_networkx_edges(
            G, pos,
            edgelist=mst_edge_list,
            edge_color="red",
            width=3
        )

    plt.title("Graph")
    plt.show()

def prims(graph,start):
    visited=set()
    min_heap = [(0,start,None)]
    mst=[]
    cost = 0
    
    while min_heap and len(visited) < len(graph):
        weight, node, parent = heapq.heappop(min_heap)
        
        if node in visited: 
            continue
        
        visited.add(node)
        cost+=weight
        
        if parent is not None:
            mst.append((parent,node,weight))
        
        
        for neighbor, edge_weight in graph[node]:
            if neighbor not in visited:
                heapq.heappush(min_heap,(edge_weight,neighbor,node))
    
    return mst,cost

graph = {
    'A': [('B', 4), ('C', 3), ('D', 7)],
    'B': [('A', 4), ('C', 1), ('E', 5), ('F', 8)],
    'C': [('A', 3), ('B', 1), ('D', 2), ('F', 6)],
    'D': [('A', 7), ('C', 2), ('G', 3)],
    'E': [('B', 5), ('F', 2), ('H', 7)],
    'F': [('B', 8), ('C', 6), ('E', 2), ('G', 4), ('I', 5)],
    'G': [('D', 3), ('F', 4), ('I', 6), ('J', 8)],
    'H': [('E', 7), ('I', 1)],
    'I': [('F', 5), ('G', 6), ('H', 1), ('J', 2)],
    'J': [('G', 8), ('I', 2)]
}

mst,cost = prims(graph, 'A')

    
draw_graph(graph)
draw_graph(graph,mst)