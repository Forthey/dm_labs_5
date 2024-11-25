import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

public class GraphIO {
    public static Graph readGraph(String fileTag) {
        try {
            Path filePath = Paths.get(fileTag + ".graph");
            var scanner = new Scanner(filePath);

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
                vertices[vertex] = new int[edgeCount];
                for (int j = 0; j < edgeCount; j++) {
                    if (!scanner.hasNextInt()) {
                        return null;
                    }
                    vertices[i][j] = scanner.nextInt();
                }
            }

            return new Graph(vertices);
        } catch (IOException e) {
            return null;
        }
    }

    public static boolean writeResult(String fileTag, Graph.CheckResult checkResult) {
        try (var fileWriter = new FileWriter(fileTag + ".out")) {
            String formattedResult = String.format(
                    "Связный: %s\n" +
                            "Ацикличый: %s\n" +
                            "Древочисленный: %s\n",
                    checkResult.isConnected,
                    checkResult.isAcyclic,
                    checkResult.isTreeLike
            );

            System.out.println(formattedResult);
            fileWriter.write(formattedResult);
            return true;
        } catch (IOException e) {
            return false;
        }
    }
}
