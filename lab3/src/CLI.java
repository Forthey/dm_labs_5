import java.util.Map;
import java.util.Scanner;

public class CLI {
    private static final String testFolder = "examples";
    private static final Map<String, String> tagToFolder = Map.of(
            "ca", "connected_acyclic",
            "cc", "connected_cyclic",
            "da", "disconnected_acyclic",
            "dc", "disconnected_cyclic"
    );

    private String argsToPath(String[] args) {
        if (args.length != 2 || !tagToFolder.containsKey(args[0])) {
            return null;
        }
        return String.format("%s/%s/%s", testFolder, tagToFolder.get(args[0]), args[1]);
    }

    public void startInteraction() {
        var scanner = new Scanner(System.in);
        var graphIO = new GraphIO();

        System.out.println("Test tags:");
        System.out.println("\tca - connected and acyclic examples");
        System.out.println("\tcc - connected and cyclic examples");
        System.out.println("\tda - disconnected and acyclic examples");
        System.out.println("\tdc - disconnected and cyclic examples");
        System.out.println("\trd - random graph");

        while (true) {
            System.out.print("Enter test tag and test name separated by space (\"exit\" to quit): ");
            String command = scanner.nextLine();

            if (command.equals("exit")) {
                break;
            }
            String[] args = command.split(" ");
            if (args.length == 0) {
                continue;
            }

            Graph graph;
            String path;
            if (args[0].equals("rd")) {
                if (args.length != 3) {
                    System.out.println("Wrong number of arguments");
                    continue;
                }
                int vertexCount;
                int edgeCount;
                try {
                    vertexCount = Integer.parseInt(args[1]);
                    edgeCount = Integer.parseInt(args[2]);
                } catch (NumberFormatException e) {
                    System.out.println("Wrong arguments");
                    continue;
                }
                graph = graphIO.createRandomGraph(vertexCount, edgeCount);
                path = null;
            } else {
                path = argsToPath(args);
                if (path == null) {
                    System.out.printf("Unknown command: %s, or path could not be found%n", command);
                    continue;
                }
                graph = graphIO.readGraph(path);
            }
            if (graph == null) {
                System.out.println("Graph could not be read");
                continue;
            }
            Graph.CheckResult result = graph.checkTreeProperties();
            if (!graphIO.writeResult(path, result)) {
                System.out.println("Result could not be written");
            }
        }
    }
}
