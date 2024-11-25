import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Map;
import java.util.Scanner;

public class GraphIO {
    private int vertexToIndex(int v) {
        return v - 1;
    }

    public Graph readGraph(String fileTag) {
        try {
            Path filePath = Paths.get(fileTag + ".graph");
            var scanner = new Scanner(filePath);

            if (!scanner.hasNextInt()) {
                return null;
            }
            int vertexCount = scanner.nextInt();

            int[][] vertices = new int[vertexCount][];
            for (int i = 0; i < vertexCount; i++) {
                if (!scanner.hasNextInt()) {
                    return null;
                }
                int vertex = scanner.nextInt();
                if (!scanner.hasNextInt()) {
                    return null;
                }
                int edgeCount = scanner.nextInt();
                vertices[vertexToIndex(vertex)] = new int[edgeCount];
                for (int j = 0; j < edgeCount; j++) {
                    if (!scanner.hasNextInt()) {
                        return null;
                    }
                    vertices[vertexToIndex(vertex)][j] = vertexToIndex(scanner.nextInt());
                }
            }

            return new Graph(vertices);
        } catch (IOException e) {
            return null;
        }
    }

    public boolean writeResult(String fileTag, Graph.CheckResult checkResult) {
        String formattedResult = String.format(
                "Связный: %s\n" +
                        "Ацикличый: %s\n" +
                        "Древочисленный: %s\n",
                checkResult.isConnected,
                checkResult.isAcyclic,
                checkResult.isTreeLike
        );
        System.out.println(formattedResult);
        if (fileTag != null) {
            try (var fileWriter = new FileWriter(fileTag + ".out")) {

                fileWriter.write(formattedResult);
            } catch (IOException e) {
                return false;
            }
        }
        return true;
    }

    public Graph createRandomGraph(int vertexCount, int edgeCount) {
        if (vertexCount <= 0 || edgeCount < 0) {
            return null;
        }
        var vertices = new ArrayList<ArrayList<Integer>>(vertexCount);
        for (int i = 0; i < vertexCount; i++) {
            vertices.add(new ArrayList<>());
        }
        for (int i = 0; i < edgeCount; i++){
            int u = (int)(Math.random() * vertexCount);
            int v = (int)(Math.random() * vertexCount);

            vertices.get(u).add(v);
            vertices.get(v).add(u);
        }

        int[][] arrayVertices = new int[vertexCount][];
        for (int i = 0; i < vertexCount; i++) {
            arrayVertices[i] = new int[vertices.get(i).size()];
            for (int j = 0; j < arrayVertices[i].length; j++) {
                arrayVertices[i][j] = vertices.get(i).get(j);
            }
        }

        return new Graph(arrayVertices);
    }
}
