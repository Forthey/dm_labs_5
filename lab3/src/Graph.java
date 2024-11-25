import java.util.Arrays;
import java.util.HashSet;
import java.util.Stack;

public class Graph {
    private final int[][] vertices;

    public Graph(int[][] vertices) {
        this.vertices = vertices;
    }

    private boolean checkIfConnected() {
        if (vertices.length == 0) {
            return true;
        }

        int traversedVerticesCnt = 0;
        var traverseStack = new Stack<Integer>();
        var visited = new boolean[vertices.length];

        Arrays.fill(visited, false);
        traverseStack.push(0);

        while (!traverseStack.isEmpty()) {
            int vertex = traverseStack.pop();

            if (visited[vertex]) {
                continue;
            }
            visited[vertex] = true;
            traversedVerticesCnt++;

            for (int adjVertex : vertices[vertex]) {
                traverseStack.push(adjVertex);
            }
        }

        return traversedVerticesCnt == vertices.length;
    }

    private boolean checkIfAcyclic() {
        class TraversePair {
            public final int vertex;
            public final int parent;

            public TraversePair(int vertex, int parent) {
                this.vertex = vertex;
                this.parent = parent;
            }
        }

        if (vertices.length == 0) {
            return true;
        }

        var traverseStack = new Stack<TraversePair>();
        HashSet<Integer> nonVisitedVertices = HashSet.newHashSet(vertices.length);
        for (int i = 0; i < vertices.length; i++) {
            nonVisitedVertices.add(i);
        }
        traverseStack.push(new TraversePair(0, -1));

        while (true) {
            while (!traverseStack.isEmpty()) {
                TraversePair pair = traverseStack.pop();
                if (!nonVisitedVertices.contains(pair.vertex)) {
                    return false;
                }
                nonVisitedVertices.remove(pair.vertex);

                for (int adjVertex : vertices[pair.vertex]) {
                    if (pair.parent == adjVertex) {
                        continue;
                    }
                    traverseStack.push(new TraversePair(adjVertex, pair.vertex));
                }
            }

            if (nonVisitedVertices.isEmpty()) {
                break;
            }

            traverseStack.push(new TraversePair(nonVisitedVertices.stream().findAny().get(), -1));
        }

        return true;
    }

    private boolean checkIfTreeLike() {
        int edgesCnt = 0;
        for (int[] adjVertices : vertices) {
            edgesCnt += adjVertices.length;
        }
        return edgesCnt / 2 == vertices.length - 1;
    }

    /**
     * Класс возвращаемого значения проверки графа
     */
    static public class CheckResult {
        public boolean isConnected; // Связность
        public boolean isAcyclic;   // Ацикличность
        public boolean isTreeLike;  // Древочисленность
    }

    public CheckResult checkTreeProperties() {
        var result = new CheckResult();

        result.isConnected = checkIfConnected();
        result.isAcyclic = checkIfAcyclic();
        result.isTreeLike = checkIfTreeLike();

        return result;
    }
}
