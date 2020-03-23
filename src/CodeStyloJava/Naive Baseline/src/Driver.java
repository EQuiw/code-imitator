public class Driver {

    /**
     * Dependencies: Apache Commons IO, Util.java, ARFFFactory*.java, everything
     * else in the Naive-Baseline package
     */
    public static void main(String args[]) {
        if (args.length != 2) {
            System.err
                    .println("Usage: <root directory of all test files> <target ARFF file>");
            System.exit(1);
        }

        (new ARFFFactory4()).makeARFF(args[0], args[1]);

//        String[] argss = new String[2];
//        argss[0] = "/path/to/dataset_2017/dataset_2017_8_formatted";
//        argss[1] = "/path/to/data/output_2017_8_formatted.arff";
//        (new ARFFFactory4()).makeARFF(argss[0], argss[1]);

    }
}