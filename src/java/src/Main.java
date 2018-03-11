import BlockChain.MerkleRoot;

public class Main {

    public static void main(String[] args) {
        String t[] = {"Source-Destination:72",
                "Source-Destination:57",
                "Source-Destination:69",
                "Source-Destination:42"
        };
        String m = new MerkleRoot(t).getRoot();
        System.out.println(m + "\n" + "c076662f457fddff160e42bdc0b2bc199ca6c6e5064c4b133216393592a3d2aa");
    }
}
