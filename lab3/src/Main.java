import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        var scanner = new Scanner(System.in);
        while (true) {
            System.out.print("Enter file tag of \"exit\": ");
            String command = scanner.nextLine();

            if (command.equals("exit")) {
                break;
            }
            var graph = GraphIO.readGraph(command);
            if (graph == null) {
                System.out.println("Graph could not be read");
                continue;
            }
            Graph.CheckResult result = graph.checkTreeProperties();
            if (!GraphIO.writeResult(command, result)) {
                System.out.println("Result could not be written");
            }
        }
    }
}
