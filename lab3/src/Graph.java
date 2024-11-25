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
        if (vertices.length == 0) {
            return true;
        }
        var traverseStack = new Stack<Integer>();
        HashSet<Integer> nonVisitedVertices = HashSet.newHashSet(vertices.length);
        for (int i = 0; i < vertices.length; i++) {
            nonVisitedVertices.add(i);
        }

        while (true) {
            while (!traverseStack.isEmpty()) {
                Integer vertex = traverseStack.pop();
                if (!nonVisitedVertices.contains(vertex)) {
                    return false;
                }
                nonVisitedVertices.remove(vertex);

                for (int adjVertex : vertices[vertex]) {
                    traverseStack.push(adjVertex);
                }
            }

            if (nonVisitedVertices.isEmpty()) {
                break;
            }

            traverseStack.push(nonVisitedVertices.stream().findAny().get());
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
