public class test {
  static {
    System.loadLibrary("openpad");
  }

  public static void main(String argv[]) {
  		System.out.println("working");
  		Server s = new Server(new ServerHandler());
  		s.start();
  }
}