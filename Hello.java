class Hello {
    public static void main(String[] args) throws Exception {
        for (int i = 0; i < 100000; i++) hello();
    }

    public static void hello() throws Exception {
        Thread.sleep(5000);
    }
}
